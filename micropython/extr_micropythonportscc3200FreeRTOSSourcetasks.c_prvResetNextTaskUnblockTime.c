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
struct TYPE_2__ {int /*<<< orphan*/  xStateListItem; } ;
typedef  TYPE_1__ TCB_t ;

/* Variables and functions */
 int /*<<< orphan*/  listGET_LIST_ITEM_VALUE (int /*<<< orphan*/ *) ; 
 scalar_t__ listGET_OWNER_OF_HEAD_ENTRY (int /*<<< orphan*/ ) ; 
 scalar_t__ listLIST_IS_EMPTY (int /*<<< orphan*/ ) ; 
 scalar_t__ pdFALSE ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  pxDelayedTaskList ; 
 int /*<<< orphan*/  xNextTaskUnblockTime ; 

__attribute__((used)) static void prvResetNextTaskUnblockTime( void )
{
TCB_t *pxTCB;

	if( listLIST_IS_EMPTY( pxDelayedTaskList ) != pdFALSE )
	{
		/* The new current delayed list is empty.  Set xNextTaskUnblockTime to
		the maximum possible value so it is	extremely unlikely that the
		if( xTickCount >= xNextTaskUnblockTime ) test will pass until
		there is an item in the delayed list. */
		xNextTaskUnblockTime = portMAX_DELAY;
	}
	else
	{
		/* The new current delayed list is not empty, get the value of
		the item at the head of the delayed list.  This is the time at
		which the task at the head of the delayed list should be removed
		from the Blocked state. */
		( pxTCB ) = ( TCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( pxDelayedTaskList );
		xNextTaskUnblockTime = listGET_LIST_ITEM_VALUE( &( ( pxTCB )->xStateListItem ) );
	}
}