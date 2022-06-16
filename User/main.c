/*
 * main.c
 *
 *	FreeRTOS系统移植程序
 *
 *  Created on: 2022-6-15
 *      Author: tly
 */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "user_led.h"
#include "FreeRTOS.h"
#include "task.h"
/*****************************************************************************
Function Name        :: void Delay(u32 count)
Function Description :: 延时函数
Input Parameters     :: No
Return Value         :: No
Condition            :: No
Tips                 :: 
Function called	-

Last Chang Date      : 2022/06/15		
*****************************************************************************/

//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

//任务优先级
#define LED0_TASK_PRIO		2
//任务堆栈大小	
#define LED0_STK_SIZE 		50  
//任务句柄
TaskHandle_t LED0Task_Handler;
//任务函数
void led0_task(void *pvParameters);

//任务优先级
#define LED1_TASK_PRIO		3
//任务堆栈大小	
#define LED1_STK_SIZE 		50  
//任务句柄
TaskHandle_t LED1Task_Handler;
//任务函数
void led1_task(void *pvParameters);

//任务优先级
#define FLOAT_TASK_PRIO		4
//任务堆栈大小	
#define FLOAT_STK_SIZE 		50  
//任务句柄
TaskHandle_t FLOAT_Task_Handler;
//任务函数
void float_task(void *pvParameters);


 
 /*****************************************************************************
Function Name        :: int main(void)
Function Description :: 主函数
Input Parameters     :: No
Return Value         :: No
Condition            :: No
Tips                 :: 
Function called	-

Last Chang Date      : 2022/06/15		
*****************************************************************************/
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4	 
	delay_init();	    				//延时函数初始化	  
	uart_init(115200);					//初始化串口
	LED_Init();		  					//初始化LED
	 
	//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度
}

 
 
 /*****************************************************************************
Function Name        :: void start_task(void *pvParameters)
Function Description :: 开始任务
Input Parameters     :: No
Return Value         :: No
Condition            :: No
Tips                 :: 
Function called	-

Last Chang Date      : 2022/06/15		
*****************************************************************************/
//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
    //创建LED0任务
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);   
    //创建LED1任务
    xTaskCreate((TaskFunction_t )led1_task,     
                (const char*    )"led1_task",   
                (uint16_t       )LED1_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED1_TASK_PRIO,
                (TaskHandle_t*  )&LED1Task_Handler); 
    //创建FLOAT任务
    xTaskCreate((TaskFunction_t )float_task,     
                (const char*    )"float_task",   
                (uint16_t       )FLOAT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )FLOAT_TASK_PRIO,
                (TaskHandle_t*  )&FLOAT_Task_Handler);								
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

 
 
 /*****************************************************************************
Function Name        :: void led0_task(void *pvParameters)
Function Description :: 任务内容
Input Parameters     :: No
Return Value         :: No
Condition            :: No
Tips                 :: 
Function called	-

Last Chang Date      : 2022/06/15		
*****************************************************************************/
//LED0任务函数 
void led0_task(void *pvParameters)
{
    while(1)
    {
        LED0_ON;
        vTaskDelay(200);
        LED0_OFF;
        vTaskDelay(800);
    }
}   

 
 
 /*****************************************************************************
Function Name        :: void led1_task(void *pvParameters)
Function Description :: 任务内容
Input Parameters     :: No
Return Value         :: No
Condition            :: No
Tips                 :: 
Function called	-

Last Chang Date      : 2022/06/15		
*****************************************************************************/
//LED1任务函数
void led1_task(void *pvParameters)
{
    while(1)
    {
        LED1_ON;
        vTaskDelay(200);
        LED1_OFF;
        vTaskDelay(800);
    }
}

 
 
 /*****************************************************************************
Function Name        :: void float_task(void *pvParameters)
Function Description :: 任务内容
Input Parameters     :: No
Return Value         :: No
Condition            :: No
Tips                 :: 
Function called	-

Last Chang Date      : 2022/06/15		
*****************************************************************************/
//FLOAT任务函数 
void float_task(void *pvParameters)
{
    static float float_num=0.01;
    while(1)
    {
        float_num+=0.01f;
        taskENTER_CRITICAL();           //进入临界区
        printf("float_num的值为: %.4f\r\n",float_num);   /*串口打印结果*/
        taskEXIT_CRITICAL();            //退出临界区
        vTaskDelay(1000);
    }
}   
