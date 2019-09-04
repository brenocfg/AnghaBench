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
typedef  int UBaseType_t ;
struct TYPE_4__ {scalar_t__ pcReadFrom; } ;
struct TYPE_5__ {int uxLength; int uxItemSize; int uxMessagesWaiting; int /*<<< orphan*/  xTasksWaitingToReceive; int /*<<< orphan*/  xTasksWaitingToSend; void* cTxLock; void* cRxLock; scalar_t__ pcHead; TYPE_1__ u; scalar_t__ pcWriteTo; scalar_t__ pcTail; } ;
typedef  TYPE_2__ Queue_t ;
typedef  scalar_t__ QueueHandle_t ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (TYPE_2__* const) ; 
 scalar_t__ listLIST_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtCOVERAGE_TEST_MARKER () ; 
 scalar_t__ pdFALSE ; 
 scalar_t__ pdPASS ; 
 void* queueUNLOCKED ; 
 int /*<<< orphan*/  queueYIELD_IF_USING_PREEMPTION () ; 
 int /*<<< orphan*/  taskENTER_CRITICAL () ; 
 int /*<<< orphan*/  taskEXIT_CRITICAL () ; 
 int /*<<< orphan*/  vListInitialise (int /*<<< orphan*/ *) ; 
 scalar_t__ xTaskRemoveFromEventList (int /*<<< orphan*/ *) ; 

BaseType_t xQueueGenericReset( QueueHandle_t xQueue, BaseType_t xNewQueue )
{
Queue_t * const pxQueue = ( Queue_t * ) xQueue;

	configASSERT( pxQueue );

	taskENTER_CRITICAL();
	{
		pxQueue->pcTail = pxQueue->pcHead + ( pxQueue->uxLength * pxQueue->uxItemSize );
		pxQueue->uxMessagesWaiting = ( UBaseType_t ) 0U;
		pxQueue->pcWriteTo = pxQueue->pcHead;
		pxQueue->u.pcReadFrom = pxQueue->pcHead + ( ( pxQueue->uxLength - ( UBaseType_t ) 1U ) * pxQueue->uxItemSize );
		pxQueue->cRxLock = queueUNLOCKED;
		pxQueue->cTxLock = queueUNLOCKED;

		if( xNewQueue == pdFALSE )
		{
			/* If there are tasks blocked waiting to read from the queue, then
			the tasks will remain blocked as after this function exits the queue
			will still be empty.  If there are tasks blocked waiting to write to
			the queue, then one should be unblocked as after this function exits
			it will be possible to write to it. */
			if( listLIST_IS_EMPTY( &( pxQueue->xTasksWaitingToSend ) ) == pdFALSE )
			{
				if( xTaskRemoveFromEventList( &( pxQueue->xTasksWaitingToSend ) ) != pdFALSE )
				{
					queueYIELD_IF_USING_PREEMPTION();
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
		else
		{
			/* Ensure the event queues start in the correct state. */
			vListInitialise( &( pxQueue->xTasksWaitingToSend ) );
			vListInitialise( &( pxQueue->xTasksWaitingToReceive ) );
		}
	}
	taskEXIT_CRITICAL();

	/* A value is returned for calling semantic consistency with previous
	versions. */
	return pdPASS;
}