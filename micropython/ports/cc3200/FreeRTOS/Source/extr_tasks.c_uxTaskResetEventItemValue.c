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
typedef  scalar_t__ TickType_t ;
struct TYPE_2__ {scalar_t__ uxPriority; int /*<<< orphan*/  xEventListItem; } ;

/* Variables and functions */
 scalar_t__ configMAX_PRIORITIES ; 
 scalar_t__ listGET_LIST_ITEM_VALUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listSET_LIST_ITEM_VALUE (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* pxCurrentTCB ; 

TickType_t uxTaskResetEventItemValue( void )
{
TickType_t uxReturn;

	uxReturn = listGET_LIST_ITEM_VALUE( &( pxCurrentTCB->xEventListItem ) );

	/* Reset the event list item to its normal value - so it can be used with
	queues and semaphores. */
	listSET_LIST_ITEM_VALUE( &( pxCurrentTCB->xEventListItem ), ( ( TickType_t ) configMAX_PRIORITIES - ( TickType_t ) pxCurrentTCB->uxPriority ) ); /*lint !e961 MISRA exception as the casts are only redundant for some ports. */

	return uxReturn;
}