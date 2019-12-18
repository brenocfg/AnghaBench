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
struct tmpmasks {int dummy; } ;
struct cpuset {int partition_root_state; scalar_t__ child_ecpus_count; int /*<<< orphan*/  cpus_allowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_CPU_EXCLUSIVE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int PRS_ENABLED ; 
 int PRS_ERROR ; 
 scalar_t__ alloc_cpumasks (int /*<<< orphan*/ *,struct tmpmasks*) ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumasks (int /*<<< orphan*/ *,struct tmpmasks*) ; 
 struct cpuset* parent_cs (struct cpuset*) ; 
 int /*<<< orphan*/  partcmd_disable ; 
 int /*<<< orphan*/  partcmd_enable ; 
 int /*<<< orphan*/  rebuild_sched_domains_locked () ; 
 struct cpuset top_cpuset ; 
 int update_flag (int /*<<< orphan*/ ,struct cpuset*,int) ; 
 int update_parent_subparts_cpumask (struct cpuset*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tmpmasks*) ; 
 int /*<<< orphan*/  update_sibling_cpumasks (struct cpuset*,struct cpuset*,struct tmpmasks*) ; 
 int /*<<< orphan*/  update_tasks_cpumask (struct cpuset*) ; 

__attribute__((used)) static int update_prstate(struct cpuset *cs, int val)
{
	int err;
	struct cpuset *parent = parent_cs(cs);
	struct tmpmasks tmp;

	if ((val != 0) && (val != 1))
		return -EINVAL;
	if (val == cs->partition_root_state)
		return 0;

	/*
	 * Cannot force a partial or invalid partition root to a full
	 * partition root.
	 */
	if (val && cs->partition_root_state)
		return -EINVAL;

	if (alloc_cpumasks(NULL, &tmp))
		return -ENOMEM;

	err = -EINVAL;
	if (!cs->partition_root_state) {
		/*
		 * Turning on partition root requires setting the
		 * CS_CPU_EXCLUSIVE bit implicitly as well and cpus_allowed
		 * cannot be NULL.
		 */
		if (cpumask_empty(cs->cpus_allowed))
			goto out;

		err = update_flag(CS_CPU_EXCLUSIVE, cs, 1);
		if (err)
			goto out;

		err = update_parent_subparts_cpumask(cs, partcmd_enable,
						     NULL, &tmp);
		if (err) {
			update_flag(CS_CPU_EXCLUSIVE, cs, 0);
			goto out;
		}
		cs->partition_root_state = PRS_ENABLED;
	} else {
		/*
		 * Turning off partition root will clear the
		 * CS_CPU_EXCLUSIVE bit.
		 */
		if (cs->partition_root_state == PRS_ERROR) {
			cs->partition_root_state = 0;
			update_flag(CS_CPU_EXCLUSIVE, cs, 0);
			err = 0;
			goto out;
		}

		err = update_parent_subparts_cpumask(cs, partcmd_disable,
						     NULL, &tmp);
		if (err)
			goto out;

		cs->partition_root_state = 0;

		/* Turning off CS_CPU_EXCLUSIVE will not return error */
		update_flag(CS_CPU_EXCLUSIVE, cs, 0);
	}

	/*
	 * Update cpumask of parent's tasks except when it is the top
	 * cpuset as some system daemons cannot be mapped to other CPUs.
	 */
	if (parent != &top_cpuset)
		update_tasks_cpumask(parent);

	if (parent->child_ecpus_count)
		update_sibling_cpumasks(parent, cs, &tmp);

	rebuild_sched_domains_locked();
out:
	free_cpumasks(NULL, &tmp);
	return err;
}