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

__attribute__((used)) static void account_freq_event_nohz(void)
{
#ifdef CONFIG_NO_HZ_FULL
	/* Lock so we don't race with concurrent unaccount */
	spin_lock(&nr_freq_lock);
	if (atomic_inc_return(&nr_freq_events) == 1)
		tick_nohz_dep_set(TICK_DEP_BIT_PERF_EVENTS);
	spin_unlock(&nr_freq_lock);
#endif
}