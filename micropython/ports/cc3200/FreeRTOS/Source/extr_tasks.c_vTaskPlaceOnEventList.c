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
typedef  int /*<<< orphan*/  TickType_t ;
struct TYPE_2__ {int /*<<< orphan*/  xEventListItem; } ;
typedef  int /*<<< orphan*/  List_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  pdTRUE ; 
 int /*<<< orphan*/  prvAddCurrentTaskToDelayedList (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 TYPE_1__* pxCurrentTCB ; 
 int /*<<< orphan*/  vListInsert (int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 

void vTaskPlaceOnEventList( List_t * const pxEventList, const TickType_t xTicksToWait )
{
	configASSERT( pxEventList );

	/* THIS FUNCTION MUST BE CALLED WITH EITHER INTERRUPTS DISABLED OR THE
	SCHEDULER SUSPENDED AND THE QUEUE BEING ACCESSED LOCKED. */

	/* Place the event list item of the TCB in the appropriate event list.
	This is placed in the list in priority order so the highest priority task
	is the first to be woken by the event.  The queue that contains the event
	list is locked, preventing simultaneous access from interrupts. */
	vListInsert( pxEventList, &( pxCurrentTCB->xEventListItem ) );

	prvAddCurrentTaskToDelayedList( xTicksToWait, pdTRUE );
}