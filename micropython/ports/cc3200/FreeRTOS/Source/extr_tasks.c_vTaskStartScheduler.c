#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ TickType_t ;
struct TYPE_2__ {int /*<<< orphan*/  xNewLib_reent; } ;
typedef  int /*<<< orphan*/  StaticTask_t ;
typedef  int /*<<< orphan*/  StackType_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/ * _impure_ptr ; 
 int /*<<< orphan*/  configASSERT (int) ; 
 int /*<<< orphan*/  configMINIMAL_STACK_SIZE ; 
 scalar_t__ errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY ; 
 int /*<<< orphan*/  mtCOVERAGE_TEST_MARKER () ; 
 scalar_t__ pdFAIL ; 
 scalar_t__ pdFALSE ; 
 scalar_t__ pdPASS ; 
 int /*<<< orphan*/  pdTRUE ; 
 int /*<<< orphan*/  portCONFIGURE_TIMER_FOR_RUN_TIME_STATS () ; 
 int /*<<< orphan*/  portDISABLE_INTERRUPTS () ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int portPRIVILEGE_BIT ; 
 int /*<<< orphan*/  prvIdleTask ; 
 TYPE_1__* pxCurrentTCB ; 
 int tskIDLE_PRIORITY ; 
 int /*<<< orphan*/  vApplicationGetIdleTaskMemory (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xIdleTaskHandle ; 
 int /*<<< orphan*/  xNextTaskUnblockTime ; 
 scalar_t__ xPortStartScheduler () ; 
 int /*<<< orphan*/  xSchedulerRunning ; 
 scalar_t__ xTaskCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * xTaskCreateStatic (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xTickCount ; 
 scalar_t__ xTimerCreateTimerTask () ; 

void vTaskStartScheduler( void )
{
BaseType_t xReturn;

	/* Add the idle task at the lowest priority. */
	#if( configSUPPORT_STATIC_ALLOCATION == 1 )
	{
		StaticTask_t *pxIdleTaskTCBBuffer = NULL;
		StackType_t *pxIdleTaskStackBuffer = NULL;
		uint32_t ulIdleTaskStackSize;

		/* The Idle task is created using user provided RAM - obtain the
		address of the RAM then create the idle task. */
		vApplicationGetIdleTaskMemory( &pxIdleTaskTCBBuffer, &pxIdleTaskStackBuffer, &ulIdleTaskStackSize );
		xIdleTaskHandle = xTaskCreateStatic(	prvIdleTask,
												"IDLE",
												ulIdleTaskStackSize,
												( void * ) NULL,
												( tskIDLE_PRIORITY | portPRIVILEGE_BIT ),
												pxIdleTaskStackBuffer,
												pxIdleTaskTCBBuffer ); /*lint !e961 MISRA exception, justified as it is not a redundant explicit cast to all supported compilers. */

		if( xIdleTaskHandle != NULL )
		{
			xReturn = pdPASS;
		}
		else
		{
			xReturn = pdFAIL;
		}
	}
	#else
	{
		/* The Idle task is being created using dynamically allocated RAM. */
		xReturn = xTaskCreate(	prvIdleTask,
								"IDLE", configMINIMAL_STACK_SIZE,
								( void * ) NULL,
								( tskIDLE_PRIORITY | portPRIVILEGE_BIT ),
								&xIdleTaskHandle ); /*lint !e961 MISRA exception, justified as it is not a redundant explicit cast to all supported compilers. */
	}
	#endif /* configSUPPORT_STATIC_ALLOCATION */

	#if ( configUSE_TIMERS == 1 )
	{
		if( xReturn == pdPASS )
		{
			xReturn = xTimerCreateTimerTask();
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}
	#endif /* configUSE_TIMERS */

	if( xReturn == pdPASS )
	{
		/* Interrupts are turned off here, to ensure a tick does not occur
		before or during the call to xPortStartScheduler().  The stacks of
		the created tasks contain a status word with interrupts switched on
		so interrupts will automatically get re-enabled when the first task
		starts to run. */
		portDISABLE_INTERRUPTS();

		#if ( configUSE_NEWLIB_REENTRANT == 1 )
		{
			/* Switch Newlib's _impure_ptr variable to point to the _reent
			structure specific to the task that will run first. */
			_impure_ptr = &( pxCurrentTCB->xNewLib_reent );
		}
		#endif /* configUSE_NEWLIB_REENTRANT */

		xNextTaskUnblockTime = portMAX_DELAY;
		xSchedulerRunning = pdTRUE;
		xTickCount = ( TickType_t ) 0U;

		/* If configGENERATE_RUN_TIME_STATS is defined then the following
		macro must be defined to configure the timer/counter used to generate
		the run time counter time base. */
		portCONFIGURE_TIMER_FOR_RUN_TIME_STATS();

		/* Setting up the timer tick is hardware specific and thus in the
		portable interface. */
		if( xPortStartScheduler() != pdFALSE )
		{
			/* Should not reach here as if the scheduler is running the
			function will not return. */
		}
		else
		{
			/* Should only reach here if a task calls xTaskEndScheduler(). */
		}
	}
	else
	{
		/* This line will only be reached if the kernel could not be started,
		because there was not enough FreeRTOS heap to create the idle task
		or the timer task. */
		configASSERT( xReturn != errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY );
	}

	/* Prevent compiler warnings if INCLUDE_xTaskGetIdleTaskHandle is set to 0,
	meaning xIdleTaskHandle is not used anywhere else. */
	( void ) xIdleTaskHandle;
}