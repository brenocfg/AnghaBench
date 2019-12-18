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
 int /*<<< orphan*/  EXP_1 ; 
 int /*<<< orphan*/  EXP_15 ; 
 int /*<<< orphan*/  EXP_5 ; 
 long FIXED_1 ; 
 scalar_t__ LOAD_FREQ ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  atomic_long_add (long,int /*<<< orphan*/ *) ; 
 long atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avenrun ; 
 int /*<<< orphan*/  calc_global_nohz () ; 
 int /*<<< orphan*/  calc_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 long calc_load_nohz_fold () ; 
 int /*<<< orphan*/  calc_load_tasks ; 
 int /*<<< orphan*/  calc_load_update ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,unsigned long) ; 

void calc_global_load(unsigned long ticks)
{
	unsigned long sample_window;
	long active, delta;

	sample_window = READ_ONCE(calc_load_update);
	if (time_before(jiffies, sample_window + 10))
		return;

	/*
	 * Fold the 'old' NO_HZ-delta to include all NO_HZ CPUs.
	 */
	delta = calc_load_nohz_fold();
	if (delta)
		atomic_long_add(delta, &calc_load_tasks);

	active = atomic_long_read(&calc_load_tasks);
	active = active > 0 ? active * FIXED_1 : 0;

	avenrun[0] = calc_load(avenrun[0], EXP_1, active);
	avenrun[1] = calc_load(avenrun[1], EXP_5, active);
	avenrun[2] = calc_load(avenrun[2], EXP_15, active);

	WRITE_ONCE(calc_load_update, sample_window + LOAD_FREQ);

	/*
	 * In case we went to NO_HZ for multiple LOAD_FREQ intervals
	 * catch up in bulk.
	 */
	calc_global_nohz();
}