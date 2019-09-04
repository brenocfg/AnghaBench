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
 int /*<<< orphan*/  LTIMER_CLR ; 
 int /*<<< orphan*/  LTIMER_CLR_ACK ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  put32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void handle_local_timer_irq( void ) 
{
	printf("Timer interrupt received\n\r");
	put32(LTIMER_CLR, LTIMER_CLR_ACK);
}