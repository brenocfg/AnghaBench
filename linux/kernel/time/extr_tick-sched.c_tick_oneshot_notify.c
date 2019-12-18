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
struct tick_sched {int /*<<< orphan*/  check_clocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tick_sched* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tick_cpu_sched ; 

void tick_oneshot_notify(void)
{
	struct tick_sched *ts = this_cpu_ptr(&tick_cpu_sched);

	set_bit(0, &ts->check_clocks);
}