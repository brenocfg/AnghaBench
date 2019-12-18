#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UBaseType_t ;
struct TYPE_5__ {scalar_t__ uxPriority; } ;
struct TYPE_4__ {scalar_t__ uxPriority; int /*<<< orphan*/  xStateListItem; int /*<<< orphan*/  xEventListItem; } ;
typedef  TYPE_1__ TCB_t ;
typedef  void* BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (scalar_t__) ; 
 scalar_t__ listGET_OWNER_OF_HEAD_ENTRY (int /*<<< orphan*/ *) ; 
 scalar_t__ listLIST_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtCOVERAGE_TEST_MARKER () ; 
 scalar_t__ pdFALSE ; 
 void* pdTRUE ; 
 int /*<<< orphan*/  prvAddTaskToReadyList (TYPE_1__*) ; 
 int /*<<< orphan*/  prvResetNextTaskUnblockTime () ; 
 TYPE_2__* pxCurrentTCB ; 
 int /*<<< orphan*/  taskENTER_CRITICAL () ; 
 int /*<<< orphan*/  taskEXIT_CRITICAL () ; 
 int /*<<< orphan*/  taskYIELD_IF_USING_PREEMPTION () ; 
 scalar_t__ uxCurrentNumberOfTasks ; 
 int /*<<< orphan*/  uxListRemove (int /*<<< orphan*/ *) ; 
 scalar_t__ uxPendedTicks ; 
 scalar_t__ uxSchedulerSuspended ; 
 int /*<<< orphan*/  xPendingReadyList ; 
 scalar_t__ xTaskIncrementTick () ; 
 scalar_t__ xYieldPending ; 

BaseType_t xTaskResumeAll( void )
{
TCB_t *pxTCB = NULL;
BaseType_t xAlreadyYielded = pdFALSE;

	/* If uxSchedulerSuspended is zero then this function does not match a
	previous call to vTaskSuspendAll(). */
	configASSERT( uxSchedulerSuspended );

	/* It is possible that an ISR caused a task to be removed from an event
	list while the scheduler was suspended.  If this was the case then the
	removed task will have been added to the xPendingReadyList.  Once the
	scheduler has been resumed it is safe to move all the pending ready
	tasks from this list into their appropriate ready list. */
	taskENTER_CRITICAL();
	{
		--uxSchedulerSuspended;

		if( uxSchedulerSuspended == ( UBaseType_t ) pdFALSE )
		{
			if( uxCurrentNumberOfTasks > ( UBaseType_t ) 0U )
			{
				/* Move any readied tasks from the pending list into the
				appropriate ready list. */
				while( listLIST_IS_EMPTY( &xPendingReadyList ) == pdFALSE )
				{
					pxTCB = ( TCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( ( &xPendingReadyList ) );
					( void ) uxListRemove( &( pxTCB->xEventListItem ) );
					( void ) uxListRemove( &( pxTCB->xStateListItem ) );
					prvAddTaskToReadyList( pxTCB );

					/* If the moved task has a priority higher than the current
					task then a yield must be performed. */
					if( pxTCB->uxPriority >= pxCurrentTCB->uxPriority )
					{
						xYieldPending = pdTRUE;
					}
					else
					{
						mtCOVERAGE_TEST_MARKER();
					}
				}

				if( pxTCB != NULL )
				{
					/* A task was unblocked while the scheduler was suspended,
					which may have prevented the next unblock time from being
					re-calculated, in which case re-calculate it now.  Mainly
					important for low power tickless implementations, where
					this can prevent an unnecessary exit from low power
					state. */
					prvResetNextTaskUnblockTime();
				}

				/* If any ticks occurred while the scheduler was suspended then
				they should be processed now.  This ensures the tick count does
				not	slip, and that any delayed tasks are resumed at the correct
				time. */
				{
					UBaseType_t uxPendedCounts = uxPendedTicks; /* Non-volatile copy. */

					if( uxPendedCounts > ( UBaseType_t ) 0U )
					{
						do
						{
							if( xTaskIncrementTick() != pdFALSE )
							{
								xYieldPending = pdTRUE;
							}
							else
							{
								mtCOVERAGE_TEST_MARKER();
							}
							--uxPendedCounts;
						} while( uxPendedCounts > ( UBaseType_t ) 0U );

						uxPendedTicks = 0;
					}
					else
					{
						mtCOVERAGE_TEST_MARKER();
					}
				}

				if( xYieldPending != pdFALSE )
				{
					#if( configUSE_PREEMPTION != 0 )
					{
						xAlreadyYielded = pdTRUE;
					}
					#endif
					taskYIELD_IF_USING_PREEMPTION();
				}
				else
				{
					mtCOVERAGE_TEST_MARKER();
				}
			}
		}
		else
		{
			mtCOVERAGE_TEST_MARKER();
		}
	}
	taskEXIT_CRITICAL();

	return xAlreadyYielded;
}