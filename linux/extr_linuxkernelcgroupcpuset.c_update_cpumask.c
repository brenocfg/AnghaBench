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
struct cpuset {int /*<<< orphan*/  cpus_allowed; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int /*<<< orphan*/  callback_lock ; 
 int cpulist_parse (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_subset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct cpuset top_cpuset ; 
 int /*<<< orphan*/  update_cpumasks_hier (struct cpuset*,int /*<<< orphan*/ ) ; 
 int validate_change (struct cpuset*,struct cpuset*) ; 

__attribute__((used)) static int update_cpumask(struct cpuset *cs, struct cpuset *trialcs,
			  const char *buf)
{
	int retval;

	/* top_cpuset.cpus_allowed tracks cpu_online_mask; it's read-only */
	if (cs == &top_cpuset)
		return -EACCES;

	/*
	 * An empty cpus_allowed is ok only if the cpuset has no tasks.
	 * Since cpulist_parse() fails on an empty mask, we special case
	 * that parsing.  The validate_change() call ensures that cpusets
	 * with tasks have cpus.
	 */
	if (!*buf) {
		cpumask_clear(trialcs->cpus_allowed);
	} else {
		retval = cpulist_parse(buf, trialcs->cpus_allowed);
		if (retval < 0)
			return retval;

		if (!cpumask_subset(trialcs->cpus_allowed,
				    top_cpuset.cpus_allowed))
			return -EINVAL;
	}

	/* Nothing to do if the cpus didn't change */
	if (cpumask_equal(cs->cpus_allowed, trialcs->cpus_allowed))
		return 0;

	retval = validate_change(cs, trialcs);
	if (retval < 0)
		return retval;

	spin_lock_irq(&callback_lock);
	cpumask_copy(cs->cpus_allowed, trialcs->cpus_allowed);
	spin_unlock_irq(&callback_lock);

	/* use trialcs->cpus_allowed as a temp variable */
	update_cpumasks_hier(cs, trialcs->cpus_allowed);
	return 0;
}