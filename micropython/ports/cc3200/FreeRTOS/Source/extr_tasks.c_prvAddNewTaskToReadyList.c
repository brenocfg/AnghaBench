#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UBaseType_t ;
struct TYPE_7__ {scalar_t__ uxPriority; scalar_t__ uxTCBNumber; } ;
typedef  TYPE_1__ TCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  mtCOVERAGE_TEST_MARKER () ; 
 scalar_t__ pdFALSE ; 
 int /*<<< orphan*/  portSETUP_TCB (TYPE_1__*) ; 
 int /*<<< orphan*/  prvAddTaskToReadyList (TYPE_1__*) ; 
 int /*<<< orphan*/  prvInitialiseTaskLists () ; 
 TYPE_1__* pxCurrentTCB ; 
 int /*<<< orphan*/  taskENTER_CRITICAL () ; 
 int /*<<< orphan*/  taskEXIT_CRITICAL () ; 
 int /*<<< orphan*/  taskYIELD_IF_USING_PREEMPTION () ; 
 int /*<<< orphan*/  traceTASK_CREATE (TYPE_1__*) ; 
 scalar_t__ uxCurrentNumberOfTasks ; 
 scalar_t__ uxTaskNumber ; 
 scalar_t__ xSchedulerRunning ; 

__attribute__((used)) static void prvAddNewTaskToReadyList( TCB_t *pxNewTCB )
{
	/* Ensure interrupts don't access the task lists while the lists are being
	updated. */
	taskENTER_CRITICAL();
	{
		uxCurrentNumberOfTasks++;
		if( pxCurrentTCB == NULL )
		{
			/* There are no other tasks, or all the other tasks are in
			the suspended state - make this the current task. */
			pxCurrentTCB = pxNewTCB;

			if( uxCurrentNumberOfTasks == ( UBaseType_t ) 1 )
			{
				/* This is the first task to be created so do the preliminary
				initialisation required.  We will not recover if this call
				fails, but we will report the failure. */
				prvInitialiseTaskLists();
			}
			else
			{
				mtCOVERAGE_TEST_MARKER();
			}
		}
		else
		{
			/* If the scheduler is not already running, make this task the
			current task if it is the highest priority task to be created
			so far. */
			if( xSchedulerRunning == pdFALSE )
			{
				if( pxCurrentTCB->uxPriority <= pxNewTCB->uxPriority )
				{
					pxCurrentTCB = pxNewTCB;
				}
				else
				{
					mtCOVERAGE_TEST_MARKER();
				}
			}
			else
			{
				mtCOVERAGE_TEST_MARKER();
			}
		}

		uxTaskNumber++;

		#if ( configUSE_TRACE_FACILITY == 1 )
		{
			/* Add a counter into the TCB for tracing only. */
			pxNewTCB->uxTCBNumber = uxTaskNumber;
		}
		#endif /* configUSE_TRACE_FACILITY */
		traceTASK_CREATE( pxNewTCB );

		prvAddTaskToReadyList( pxNewTCB );

		portSETUP_TCB( pxNewTCB );
	}
	taskEXIT_CRITICAL();

	if( xSchedulerRunning != pdFALSE )
	{
		/* If the created task is of a higher priority than the current task
		then it should run now. */
		if( pxCurrentTCB->uxPriority < pxNewTCB->uxPriority )
		{
			taskYIELD_IF_USING_PREEMPTION();
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}
	else
	{
		mtCOVERAGE_TEST_MARKER();
	}
}