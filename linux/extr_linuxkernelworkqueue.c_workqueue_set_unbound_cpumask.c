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
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  apply_wqattrs_lock () ; 
 int /*<<< orphan*/  apply_wqattrs_unlock () ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  cpumask_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int workqueue_apply_unbound_cpumask () ; 
 int /*<<< orphan*/  wq_unbound_cpumask ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int workqueue_set_unbound_cpumask(cpumask_var_t cpumask)
{
	int ret = -EINVAL;
	cpumask_var_t saved_cpumask;

	if (!zalloc_cpumask_var(&saved_cpumask, GFP_KERNEL))
		return -ENOMEM;

	/*
	 * Not excluding isolated cpus on purpose.
	 * If the user wishes to include them, we allow that.
	 */
	cpumask_and(cpumask, cpumask, cpu_possible_mask);
	if (!cpumask_empty(cpumask)) {
		apply_wqattrs_lock();

		/* save the old wq_unbound_cpumask. */
		cpumask_copy(saved_cpumask, wq_unbound_cpumask);

		/* update wq_unbound_cpumask at first and apply it to wqs. */
		cpumask_copy(wq_unbound_cpumask, cpumask);
		ret = workqueue_apply_unbound_cpumask();

		/* restore the wq_unbound_cpumask when failed. */
		if (ret < 0)
			cpumask_copy(wq_unbound_cpumask, saved_cpumask);

		apply_wqattrs_unlock();
	}

	free_cpumask_var(saved_cpumask);
	return ret;
}