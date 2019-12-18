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
typedef  scalar_t__ TickType_t ;
struct TYPE_2__ {scalar_t__ ucDelayAborted; int /*<<< orphan*/  xStateListItem; int /*<<< orphan*/  uxPriority; } ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  listSET_LIST_ITEM_VALUE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mtCOVERAGE_TEST_MARKER () ; 
 scalar_t__ const pdFALSE ; 
 scalar_t__ portMAX_DELAY ; 
 int /*<<< orphan*/  portRESET_READY_PRIORITY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* pxCurrentTCB ; 
 int /*<<< orphan*/  pxDelayedTaskList ; 
 int /*<<< orphan*/  pxOverflowDelayedTaskList ; 
 scalar_t__ uxListRemove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uxTopReadyPriority ; 
 int /*<<< orphan*/  vListInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vListInsertEnd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xNextTaskUnblockTime ; 
 int /*<<< orphan*/  xSuspendedTaskList ; 
 scalar_t__ xTickCount ; 

__attribute__((used)) static void prvAddCurrentTaskToDelayedList( TickType_t xTicksToWait, const BaseType_t xCanBlockIndefinitely )
{
TickType_t xTimeToWake;
const TickType_t xConstTickCount = xTickCount;

	#if( INCLUDE_xTaskAbortDelay == 1 )
	{
		/* About to enter a delayed list, so ensure the ucDelayAborted flag is
		reset to pdFALSE so it can be detected as having been set to pdTRUE
		when the task leaves the Blocked state. */
		pxCurrentTCB->ucDelayAborted = pdFALSE;
	}
	#endif

	/* Remove the task from the ready list before adding it to the blocked list
	as the same list item is used for both lists. */
	if( uxListRemove( &( pxCurrentTCB->xStateListItem ) ) == ( UBaseType_t ) 0 )
	{
		/* The current task must be in a ready list, so there is no need to
		check, and the port reset macro can be called directly. */
		portRESET_READY_PRIORITY( pxCurrentTCB->uxPriority, uxTopReadyPriority );
	}
	else
	{
		mtCOVERAGE_TEST_MARKER();
	}

	#if ( INCLUDE_vTaskSuspend == 1 )
	{
		if( ( xTicksToWait == portMAX_DELAY ) && ( xCanBlockIndefinitely != pdFALSE ) )
		{
			/* Add the task to the suspended task list instead of a delayed task
			list to ensure it is not woken by a timing event.  It will block
			indefinitely. */
			vListInsertEnd( &xSuspendedTaskList, &( pxCurrentTCB->xStateListItem ) );
		}
		else
		{
			/* Calculate the time at which the task should be woken if the event
			does not occur.  This may overflow but this doesn't matter, the
			kernel will manage it correctly. */
			xTimeToWake = xConstTickCount + xTicksToWait;

			/* The list item will be inserted in wake time order. */
			listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xStateListItem ), xTimeToWake );

			if( xTimeToWake < xConstTickCount )
			{
				/* Wake time has overflowed.  Place this item in the overflow
				list. */
				vListInsert( pxOverflowDelayedTaskList, &( pxCurrentTCB->xStateListItem ) );
			}
			else
			{
				/* The wake time has not overflowed, so the current block list
				is used. */
				vListInsert( pxDelayedTaskList, &( pxCurrentTCB->xStateListItem ) );

				/* If the task entering the blocked state was placed at the
				head of the list of blocked tasks then xNextTaskUnblockTime
				needs to be updated too. */
				if( xTimeToWake < xNextTaskUnblockTime )
				{
					xNextTaskUnblockTime = xTimeToWake;
				}
				else
				{
					mtCOVERAGE_TEST_MARKER();
				}
			}
		}
	}
	#else /* INCLUDE_vTaskSuspend */
	{
		/* Calculate the time at which the task should be woken if the event
		does not occur.  This may overflow but this doesn't matter, the kernel
		will manage it correctly. */
		xTimeToWake = xConstTickCount + xTicksToWait;

		/* The list item will be inserted in wake time order. */
		listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xStateListItem ), xTimeToWake );

		if( xTimeToWake < xConstTickCount )
		{
			/* Wake time has overflowed.  Place this item in the overflow list. */
			vListInsert( pxOverflowDelayedTaskList, &( pxCurrentTCB->xStateListItem ) );
		}
		else
		{
			/* The wake time has not overflowed, so the current block list is used. */
			vListInsert( pxDelayedTaskList, &( pxCurrentTCB->xStateListItem ) );

			/* If the task entering the blocked state was placed at the head of the
			list of blocked tasks then xNextTaskUnblockTime needs to be updated
			too. */
			if( xTimeToWake < xNextTaskUnblockTime )
			{
				xNextTaskUnblockTime = xTimeToWake;
			}
			else
			{
				mtCOVERAGE_TEST_MARKER();
			}
		}

		/* Avoid compiler warning when INCLUDE_vTaskSuspend is not 1. */
		( void ) xCanBlockIndefinitely;
	}
	#endif /* INCLUDE_vTaskSuspend */
}