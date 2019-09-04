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
 int __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ ) ; 
 int cpumask_first_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cpumask_next_and (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wq_debug_force_rr_cpu ; 
 int /*<<< orphan*/  wq_rr_cpu_last ; 
 int /*<<< orphan*/  wq_unbound_cpumask ; 

__attribute__((used)) static int wq_select_unbound_cpu(int cpu)
{
	static bool printed_dbg_warning;
	int new_cpu;

	if (likely(!wq_debug_force_rr_cpu)) {
		if (cpumask_test_cpu(cpu, wq_unbound_cpumask))
			return cpu;
	} else if (!printed_dbg_warning) {
		pr_warn("workqueue: round-robin CPU selection forced, expect performance impact\n");
		printed_dbg_warning = true;
	}

	if (cpumask_empty(wq_unbound_cpumask))
		return cpu;

	new_cpu = __this_cpu_read(wq_rr_cpu_last);
	new_cpu = cpumask_next_and(new_cpu, wq_unbound_cpumask, cpu_online_mask);
	if (unlikely(new_cpu >= nr_cpu_ids)) {
		new_cpu = cpumask_first_and(wq_unbound_cpumask, cpu_online_mask);
		if (unlikely(new_cpu >= nr_cpu_ids))
			return cpu;
	}
	__this_cpu_write(wq_rr_cpu_last, new_cpu);

	return new_cpu;
}