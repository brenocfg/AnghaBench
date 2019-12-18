#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UBaseType_t ;
struct TYPE_3__ {int /*<<< orphan*/  xStateListItem; } ;
typedef  TYPE_1__ TCB_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 scalar_t__ listGET_OWNER_OF_HEAD_ENTRY (int /*<<< orphan*/ *) ; 
 scalar_t__ listLIST_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtCOVERAGE_TEST_MARKER () ; 
 scalar_t__ pdFALSE ; 
 int /*<<< orphan*/  prvDeleteTCB (TYPE_1__*) ; 
 int /*<<< orphan*/  taskENTER_CRITICAL () ; 
 int /*<<< orphan*/  taskEXIT_CRITICAL () ; 
 int /*<<< orphan*/  uxCurrentNumberOfTasks ; 
 scalar_t__ uxDeletedTasksWaitingCleanUp ; 
 int /*<<< orphan*/  uxListRemove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vTaskSuspendAll () ; 
 int /*<<< orphan*/  xTaskResumeAll () ; 
 int /*<<< orphan*/  xTasksWaitingTermination ; 

__attribute__((used)) static void prvCheckTasksWaitingTermination( void )
{

	/** THIS FUNCTION IS CALLED FROM THE RTOS IDLE TASK **/

	#if ( INCLUDE_vTaskDelete == 1 )
	{
		BaseType_t xListIsEmpty;

		/* ucTasksDeleted is used to prevent vTaskSuspendAll() being called
		too often in the idle task. */
		while( uxDeletedTasksWaitingCleanUp > ( UBaseType_t ) 0U )
		{
			vTaskSuspendAll();
			{
				xListIsEmpty = listLIST_IS_EMPTY( &xTasksWaitingTermination );
			}
			( void ) xTaskResumeAll();

			if( xListIsEmpty == pdFALSE )
			{
				TCB_t *pxTCB;

				taskENTER_CRITICAL();
				{
					pxTCB = ( TCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( ( &xTasksWaitingTermination ) );
					( void ) uxListRemove( &( pxTCB->xStateListItem ) );
					--uxCurrentNumberOfTasks;
					--uxDeletedTasksWaitingCleanUp;
				}
				taskEXIT_CRITICAL();

				prvDeleteTCB( pxTCB );
			}
			else
			{
				mtCOVERAGE_TEST_MARKER();
			}
		}
	}
	#endif /* INCLUDE_vTaskDelete */
}