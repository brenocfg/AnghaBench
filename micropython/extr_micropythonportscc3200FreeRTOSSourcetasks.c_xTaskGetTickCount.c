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
typedef  int /*<<< orphan*/  TickType_t ;

/* Variables and functions */
 int /*<<< orphan*/  portTICK_TYPE_ENTER_CRITICAL () ; 
 int /*<<< orphan*/  portTICK_TYPE_EXIT_CRITICAL () ; 
 int /*<<< orphan*/  xTickCount ; 

TickType_t xTaskGetTickCount( void )
{
TickType_t xTicks;

	/* Critical section required if running on a 16 bit processor. */
	portTICK_TYPE_ENTER_CRITICAL();
	{
		xTicks = xTickCount;
	}
	portTICK_TYPE_EXIT_CRITICAL();

	return xTicks;
}