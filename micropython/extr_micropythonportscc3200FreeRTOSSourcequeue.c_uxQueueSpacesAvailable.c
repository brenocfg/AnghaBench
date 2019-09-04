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
struct TYPE_3__ {scalar_t__ uxMessagesWaiting; scalar_t__ uxLength; } ;
typedef  TYPE_1__ Queue_t ;
typedef  scalar_t__ QueueHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  taskENTER_CRITICAL () ; 
 int /*<<< orphan*/  taskEXIT_CRITICAL () ; 

UBaseType_t uxQueueSpacesAvailable( const QueueHandle_t xQueue )
{
UBaseType_t uxReturn;
Queue_t *pxQueue;

	pxQueue = ( Queue_t * ) xQueue;
	configASSERT( pxQueue );

	taskENTER_CRITICAL();
	{
		uxReturn = pxQueue->uxLength - pxQueue->uxMessagesWaiting;
	}
	taskEXIT_CRITICAL();

	return uxReturn;
}