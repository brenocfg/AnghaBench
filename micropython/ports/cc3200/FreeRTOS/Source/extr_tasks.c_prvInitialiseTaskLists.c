#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t UBaseType_t ;

/* Variables and functions */
 scalar_t__ configMAX_PRIORITIES ; 
 int /*<<< orphan*/ * pxDelayedTaskList ; 
 int /*<<< orphan*/ * pxOverflowDelayedTaskList ; 
 int /*<<< orphan*/ * pxReadyTasksLists ; 
 int /*<<< orphan*/  vListInitialise (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xDelayedTaskList1 ; 
 int /*<<< orphan*/  xDelayedTaskList2 ; 
 int /*<<< orphan*/  xPendingReadyList ; 
 int /*<<< orphan*/  xSuspendedTaskList ; 
 int /*<<< orphan*/  xTasksWaitingTermination ; 

__attribute__((used)) static void prvInitialiseTaskLists( void )
{
UBaseType_t uxPriority;

	for( uxPriority = ( UBaseType_t ) 0U; uxPriority < ( UBaseType_t ) configMAX_PRIORITIES; uxPriority++ )
	{
		vListInitialise( &( pxReadyTasksLists[ uxPriority ] ) );
	}

	vListInitialise( &xDelayedTaskList1 );
	vListInitialise( &xDelayedTaskList2 );
	vListInitialise( &xPendingReadyList );

	#if ( INCLUDE_vTaskDelete == 1 )
	{
		vListInitialise( &xTasksWaitingTermination );
	}
	#endif /* INCLUDE_vTaskDelete */

	#if ( INCLUDE_vTaskSuspend == 1 )
	{
		vListInitialise( &xSuspendedTaskList );
	}
	#endif /* INCLUDE_vTaskSuspend */

	/* Start with pxDelayedTaskList using list1 and the pxOverflowDelayedTaskList
	using list2. */
	pxDelayedTaskList = &xDelayedTaskList1;
	pxOverflowDelayedTaskList = &xDelayedTaskList2;
}