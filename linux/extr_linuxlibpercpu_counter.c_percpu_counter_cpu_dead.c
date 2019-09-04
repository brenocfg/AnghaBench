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

__attribute__((used)) static int percpu_counter_cpu_dead(unsigned int cpu)
{
#ifdef CONFIG_HOTPLUG_CPU
	struct percpu_counter *fbc;

	compute_batch_value(cpu);

	spin_lock_irq(&percpu_counters_lock);
	list_for_each_entry(fbc, &percpu_counters, list) {
		s32 *pcount;

		raw_spin_lock(&fbc->lock);
		pcount = per_cpu_ptr(fbc->counters, cpu);
		fbc->count += *pcount;
		*pcount = 0;
		raw_spin_unlock(&fbc->lock);
	}
	spin_unlock_irq(&percpu_counters_lock);
#endif
	return 0;
}