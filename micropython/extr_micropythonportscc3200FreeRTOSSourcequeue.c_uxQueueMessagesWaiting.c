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
typedef  int /*<<< orphan*/  UBaseType_t ;
struct TYPE_2__ {int /*<<< orphan*/  uxMessagesWaiting; } ;
typedef  TYPE_1__ Queue_t ;
typedef  scalar_t__ QueueHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  configASSERT (scalar_t__ const) ; 
 int /*<<< orphan*/  taskENTER_CRITICAL () ; 
 int /*<<< orphan*/  taskEXIT_CRITICAL () ; 

UBaseType_t uxQueueMessagesWaiting( const QueueHandle_t xQueue )
{
UBaseType_t uxReturn;

	configASSERT( xQueue );

	taskENTER_CRITICAL();
	{
		uxReturn = ( ( Queue_t * ) xQueue )->uxMessagesWaiting;
	}
	taskEXIT_CRITICAL();

	return uxReturn;
}