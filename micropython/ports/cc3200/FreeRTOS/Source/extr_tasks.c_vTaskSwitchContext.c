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
typedef  scalar_t__ UBaseType_t ;
struct TYPE_2__ {int /*<<< orphan*/  xNewLib_reent; int /*<<< orphan*/  ulRunTimeCounter; } ;

/* Variables and functions */
 int /*<<< orphan*/ * _impure_ptr ; 
 int /*<<< orphan*/  mtCOVERAGE_TEST_MARKER () ; 
 scalar_t__ pdFALSE ; 
 scalar_t__ pdTRUE ; 
 int /*<<< orphan*/  portALT_GET_RUN_TIME_COUNTER_VALUE (scalar_t__) ; 
 scalar_t__ portGET_RUN_TIME_COUNTER_VALUE () ; 
 TYPE_1__* pxCurrentTCB ; 
 int /*<<< orphan*/  taskCHECK_FOR_STACK_OVERFLOW () ; 
 int /*<<< orphan*/  taskSELECT_HIGHEST_PRIORITY_TASK () ; 
 int /*<<< orphan*/  traceTASK_SWITCHED_IN () ; 
 int /*<<< orphan*/  traceTASK_SWITCHED_OUT () ; 
 scalar_t__ ulTaskSwitchedInTime ; 
 scalar_t__ ulTotalRunTime ; 
 scalar_t__ uxSchedulerSuspended ; 
 scalar_t__ xYieldPending ; 

void vTaskSwitchContext( void )
{
	if( uxSchedulerSuspended != ( UBaseType_t ) pdFALSE )
	{
		/* The scheduler is currently suspended - do not allow a context
		switch. */
		xYieldPending = pdTRUE;
	}
	else
	{
		xYieldPending = pdFALSE;
		traceTASK_SWITCHED_OUT();

		#if ( configGENERATE_RUN_TIME_STATS == 1 )
		{
				#ifdef portALT_GET_RUN_TIME_COUNTER_VALUE
					portALT_GET_RUN_TIME_COUNTER_VALUE( ulTotalRunTime );
				#else
					ulTotalRunTime = portGET_RUN_TIME_COUNTER_VALUE();
				#endif

				/* Add the amount of time the task has been running to the
				accumulated time so far.  The time the task started running was
				stored in ulTaskSwitchedInTime.  Note that there is no overflow
				protection here so count values are only valid until the timer
				overflows.  The guard against negative values is to protect
				against suspect run time stat counter implementations - which
				are provided by the application, not the kernel. */
				if( ulTotalRunTime > ulTaskSwitchedInTime )
				{
					pxCurrentTCB->ulRunTimeCounter += ( ulTotalRunTime - ulTaskSwitchedInTime );
				}
				else
				{
					mtCOVERAGE_TEST_MARKER();
				}
				ulTaskSwitchedInTime = ulTotalRunTime;
		}
		#endif /* configGENERATE_RUN_TIME_STATS */

		/* Check for stack overflow, if configured. */
		taskCHECK_FOR_STACK_OVERFLOW();

		/* Select a new task to run using either the generic C or port
		optimised asm code. */
		taskSELECT_HIGHEST_PRIORITY_TASK();
		traceTASK_SWITCHED_IN();

		#if ( configUSE_NEWLIB_REENTRANT == 1 )
		{
			/* Switch Newlib's _impure_ptr variable to point to the _reent
			structure specific to this task. */
			_impure_ptr = &( pxCurrentTCB->xNewLib_reent );
		}
		#endif /* configUSE_NEWLIB_REENTRANT */
	}
}