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
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  retrigger_next_event ; 
 int /*<<< orphan*/  timerfd_clock_was_set () ; 

void clock_was_set(void)
{
#ifdef CONFIG_HIGH_RES_TIMERS
	/* Retrigger the CPU local events everywhere */
	on_each_cpu(retrigger_next_event, NULL, 1);
#endif
	timerfd_clock_was_set();
}