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
typedef  int TickType_t ;
struct TYPE_2__ {int /*<<< orphan*/  xEventListItem; } ;
typedef  int /*<<< orphan*/  List_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (int) ; 
 int /*<<< orphan*/  listSET_LIST_ITEM_VALUE (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  pdTRUE ; 
 int /*<<< orphan*/  prvAddCurrentTaskToDelayedList (int const,int /*<<< orphan*/ ) ; 
 TYPE_1__* pxCurrentTCB ; 
 int const taskEVENT_LIST_ITEM_VALUE_IN_USE ; 
 scalar_t__ uxSchedulerSuspended ; 
 int /*<<< orphan*/  vListInsertEnd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void vTaskPlaceOnUnorderedEventList( List_t * pxEventList, const TickType_t xItemValue, const TickType_t xTicksToWait )
{
	configASSERT( pxEventList );

	/* THIS FUNCTION MUST BE CALLED WITH THE SCHEDULER SUSPENDED.  It is used by
	the event groups implementation. */
	configASSERT( uxSchedulerSuspended != 0 );

	/* Store the item value in the event list item.  It is safe to access the
	event list item here as interrupts won't access the event list item of a
	task that is not in the Blocked state. */
	listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xEventListItem ), xItemValue | taskEVENT_LIST_ITEM_VALUE_IN_USE );

	/* Place the event list item of the TCB at the end of the appropriate event
	list.  It is safe to access the event list here because it is part of an
	event group implementation - and interrupts don't access event groups
	directly (instead they access them indirectly by pending function calls to
	the task level). */
	vListInsertEnd( pxEventList, &( pxCurrentTCB->xEventListItem ) );

	prvAddCurrentTaskToDelayedList( xTicksToWait, pdTRUE );
}