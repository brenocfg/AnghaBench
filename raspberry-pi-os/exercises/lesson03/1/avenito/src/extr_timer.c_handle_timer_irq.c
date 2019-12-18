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

/* Variables and functions */
 int /*<<< orphan*/  TIMER_FLAG ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  put32 (int /*<<< orphan*/ ,int) ; 

void handle_timer_irq( void ) 
{
	printf("Timer interrupt received, Local Timer\n\r");
	put32(TIMER_FLAG, (3<<30));				// clear interrupt flag and reload timer

}