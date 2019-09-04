#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ TickType_t ;
struct TYPE_10__ {scalar_t__ xItemValue; void* pvContainer; struct TYPE_10__* pxNext; struct TYPE_10__* pxPrevious; } ;
struct TYPE_8__ {TYPE_3__* pxPrevious; } ;
struct TYPE_9__ {int /*<<< orphan*/  uxNumberOfItems; TYPE_1__ xListEnd; } ;
typedef  TYPE_2__ List_t ;
typedef  TYPE_3__ ListItem_t ;

/* Variables and functions */
 int /*<<< orphan*/  listTEST_LIST_INTEGRITY (TYPE_2__* const) ; 
 int /*<<< orphan*/  listTEST_LIST_ITEM_INTEGRITY (TYPE_3__* const) ; 
 scalar_t__ const portMAX_DELAY ; 

void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem )
{
ListItem_t *pxIterator;
const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;

	/* Only effective when configASSERT() is also defined, these tests may catch
	the list data structures being overwritten in memory.  They will not catch
	data errors caused by incorrect configuration or use of FreeRTOS. */
	listTEST_LIST_INTEGRITY( pxList );
	listTEST_LIST_ITEM_INTEGRITY( pxNewListItem );

	/* Insert the new list item into the list, sorted in xItemValue order.

	If the list already contains a list item with the same item value then the
	new list item should be placed after it.  This ensures that TCB's which are
	stored in ready lists (all of which have the same xItemValue value) get a
	share of the CPU.  However, if the xItemValue is the same as the back marker
	the iteration loop below will not end.  Therefore the value is checked
	first, and the algorithm slightly modified if necessary. */
	if( xValueOfInsertion == portMAX_DELAY )
	{
		pxIterator = pxList->xListEnd.pxPrevious;
	}
	else
	{
		/* *** NOTE ***********************************************************
		If you find your application is crashing here then likely causes are
		listed below.  In addition see http://www.freertos.org/FAQHelp.html for
		more tips, and ensure configASSERT() is defined!
		http://www.freertos.org/a00110.html#configASSERT

			1) Stack overflow -
			   see http://www.freertos.org/Stacks-and-stack-overflow-checking.html
			2) Incorrect interrupt priority assignment, especially on Cortex-M
			   parts where numerically high priority values denote low actual
			   interrupt priorities, which can seem counter intuitive.  See
			   http://www.freertos.org/RTOS-Cortex-M3-M4.html and the definition
			   of configMAX_SYSCALL_INTERRUPT_PRIORITY on
			   http://www.freertos.org/a00110.html
			3) Calling an API function from within a critical section or when
			   the scheduler is suspended, or calling an API function that does
			   not end in "FromISR" from an interrupt.
			4) Using a queue or semaphore before it has been initialised or
			   before the scheduler has been started (are interrupts firing
			   before vTaskStartScheduler() has been called?).
		**********************************************************************/

		for( pxIterator = ( ListItem_t * ) &( pxList->xListEnd ); pxIterator->pxNext->xItemValue <= xValueOfInsertion; pxIterator = pxIterator->pxNext ) /*lint !e826 !e740 The mini list structure is used as the list end to save RAM.  This is checked and valid. */
		{
			/* There is nothing to do here, just iterating to the wanted
			insertion position. */
		}
	}

	pxNewListItem->pxNext = pxIterator->pxNext;
	pxNewListItem->pxNext->pxPrevious = pxNewListItem;
	pxNewListItem->pxPrevious = pxIterator;
	pxIterator->pxNext = pxNewListItem;

	/* Remember which list the item is in.  This allows fast removal of the
	item later. */
	pxNewListItem->pvContainer = ( void * ) pxList;

	( pxList->uxNumberOfItems )++;
}