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
struct tick_sched {scalar_t__ nohz_mode; int /*<<< orphan*/  check_clocks; } ;

/* Variables and functions */
 scalar_t__ NOHZ_MODE_INACTIVE ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tick_sched* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tick_cpu_sched ; 
 int /*<<< orphan*/  tick_is_oneshot_available () ; 
 int /*<<< orphan*/  tick_nohz_switch_to_nohz () ; 
 int /*<<< orphan*/  timekeeping_valid_for_hres () ; 

int tick_check_oneshot_change(int allow_nohz)
{
	struct tick_sched *ts = this_cpu_ptr(&tick_cpu_sched);

	if (!test_and_clear_bit(0, &ts->check_clocks))
		return 0;

	if (ts->nohz_mode != NOHZ_MODE_INACTIVE)
		return 0;

	if (!timekeeping_valid_for_hres() || !tick_is_oneshot_available())
		return 0;

	if (!allow_nohz)
		return 1;

	tick_nohz_switch_to_nohz();
	return 0;
}