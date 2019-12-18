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
struct tmpmasks {int /*<<< orphan*/  new_cpus; int /*<<< orphan*/  delmask; int /*<<< orphan*/  addmask; } ;
struct cpuset {scalar_t__ child_ecpus_count; scalar_t__ partition_root_state; int /*<<< orphan*/  subparts_cpus; scalar_t__ nr_subparts_cpus; int /*<<< orphan*/  cpus_allowed; int /*<<< orphan*/  effective_cpus; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int /*<<< orphan*/  callback_lock ; 
 int cpulist_parse (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_subset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_weight (int /*<<< orphan*/ ) ; 
 struct cpuset* parent_cs (struct cpuset*) ; 
 int /*<<< orphan*/  partcmd_update ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct cpuset top_cpuset ; 
 int /*<<< orphan*/  update_cpumasks_hier (struct cpuset*,struct tmpmasks*) ; 
 scalar_t__ update_parent_subparts_cpumask (struct cpuset*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tmpmasks*) ; 
 int /*<<< orphan*/  update_sibling_cpumasks (struct cpuset*,struct cpuset*,struct tmpmasks*) ; 
 int validate_change (struct cpuset*,struct cpuset*) ; 

__attribute__((used)) static int update_cpumask(struct cpuset *cs, struct cpuset *trialcs,
			  const char *buf)
{
	int retval;
	struct tmpmasks tmp;

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

#ifdef CONFIG_CPUMASK_OFFSTACK
	/*
	 * Use the cpumasks in trialcs for tmpmasks when they are pointers
	 * to allocated cpumasks.
	 */
	tmp.addmask  = trialcs->subparts_cpus;
	tmp.delmask  = trialcs->effective_cpus;
	tmp.new_cpus = trialcs->cpus_allowed;
#endif

	if (cs->partition_root_state) {
		/* Cpumask of a partition root cannot be empty */
		if (cpumask_empty(trialcs->cpus_allowed))
			return -EINVAL;
		if (update_parent_subparts_cpumask(cs, partcmd_update,
					trialcs->cpus_allowed, &tmp) < 0)
			return -EINVAL;
	}

	spin_lock_irq(&callback_lock);
	cpumask_copy(cs->cpus_allowed, trialcs->cpus_allowed);

	/*
	 * Make sure that subparts_cpus is a subset of cpus_allowed.
	 */
	if (cs->nr_subparts_cpus) {
		cpumask_andnot(cs->subparts_cpus, cs->subparts_cpus,
			       cs->cpus_allowed);
		cs->nr_subparts_cpus = cpumask_weight(cs->subparts_cpus);
	}
	spin_unlock_irq(&callback_lock);

	update_cpumasks_hier(cs, &tmp);

	if (cs->partition_root_state) {
		struct cpuset *parent = parent_cs(cs);

		/*
		 * For partition root, update the cpumasks of sibling
		 * cpusets if they use parent's effective_cpus.
		 */
		if (parent->child_ecpus_count)
			update_sibling_cpumasks(parent, cs, &tmp);
	}
	return 0;
}