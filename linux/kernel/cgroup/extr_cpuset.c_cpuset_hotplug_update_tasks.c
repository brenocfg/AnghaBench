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
struct cpuset {scalar_t__ attach_in_progress; scalar_t__ partition_root_state; int /*<<< orphan*/  effective_mems; int /*<<< orphan*/  effective_cpus; int /*<<< orphan*/  subparts_cpus; scalar_t__ nr_subparts_cpus; int /*<<< orphan*/  mems_allowed; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 scalar_t__ PRS_ERROR ; 
 int /*<<< orphan*/  compute_effective_cpumask (int /*<<< orphan*/ *,struct cpuset*,struct cpuset*) ; 
 int /*<<< orphan*/  cpumask_andnot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_intersects (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuset_attach_wq ; 
 int /*<<< orphan*/  cpuset_force_rebuild () ; 
 int /*<<< orphan*/  cpuset_rwsem ; 
 int /*<<< orphan*/  hotplug_update_tasks (struct cpuset*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  hotplug_update_tasks_legacy (struct cpuset*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ is_in_v2_mode () ; 
 scalar_t__ is_partition_root (struct cpuset*) ; 
 int /*<<< orphan*/  nodes_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodes_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cpuset* parent_cs (struct cpuset*) ; 
 int /*<<< orphan*/  partcmd_disable ; 
 int /*<<< orphan*/  partcmd_update ; 
 int /*<<< orphan*/  percpu_down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_up_write (int /*<<< orphan*/ *) ; 
 scalar_t__ update_parent_subparts_cpumask (struct cpuset*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tmpmasks*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cpuset_hotplug_update_tasks(struct cpuset *cs, struct tmpmasks *tmp)
{
	static cpumask_t new_cpus;
	static nodemask_t new_mems;
	bool cpus_updated;
	bool mems_updated;
	struct cpuset *parent;
retry:
	wait_event(cpuset_attach_wq, cs->attach_in_progress == 0);

	percpu_down_write(&cpuset_rwsem);

	/*
	 * We have raced with task attaching. We wait until attaching
	 * is finished, so we won't attach a task to an empty cpuset.
	 */
	if (cs->attach_in_progress) {
		percpu_up_write(&cpuset_rwsem);
		goto retry;
	}

	parent =  parent_cs(cs);
	compute_effective_cpumask(&new_cpus, cs, parent);
	nodes_and(new_mems, cs->mems_allowed, parent->effective_mems);

	if (cs->nr_subparts_cpus)
		/*
		 * Make sure that CPUs allocated to child partitions
		 * do not show up in effective_cpus.
		 */
		cpumask_andnot(&new_cpus, &new_cpus, cs->subparts_cpus);

	if (!tmp || !cs->partition_root_state)
		goto update_tasks;

	/*
	 * In the unlikely event that a partition root has empty
	 * effective_cpus or its parent becomes erroneous, we have to
	 * transition it to the erroneous state.
	 */
	if (is_partition_root(cs) && (cpumask_empty(&new_cpus) ||
	   (parent->partition_root_state == PRS_ERROR))) {
		if (cs->nr_subparts_cpus) {
			cs->nr_subparts_cpus = 0;
			cpumask_clear(cs->subparts_cpus);
			compute_effective_cpumask(&new_cpus, cs, parent);
		}

		/*
		 * If the effective_cpus is empty because the child
		 * partitions take away all the CPUs, we can keep
		 * the current partition and let the child partitions
		 * fight for available CPUs.
		 */
		if ((parent->partition_root_state == PRS_ERROR) ||
		     cpumask_empty(&new_cpus)) {
			update_parent_subparts_cpumask(cs, partcmd_disable,
						       NULL, tmp);
			cs->partition_root_state = PRS_ERROR;
		}
		cpuset_force_rebuild();
	}

	/*
	 * On the other hand, an erroneous partition root may be transitioned
	 * back to a regular one or a partition root with no CPU allocated
	 * from the parent may change to erroneous.
	 */
	if (is_partition_root(parent) &&
	   ((cs->partition_root_state == PRS_ERROR) ||
	    !cpumask_intersects(&new_cpus, parent->subparts_cpus)) &&
	     update_parent_subparts_cpumask(cs, partcmd_update, NULL, tmp))
		cpuset_force_rebuild();

update_tasks:
	cpus_updated = !cpumask_equal(&new_cpus, cs->effective_cpus);
	mems_updated = !nodes_equal(new_mems, cs->effective_mems);

	if (is_in_v2_mode())
		hotplug_update_tasks(cs, &new_cpus, &new_mems,
				     cpus_updated, mems_updated);
	else
		hotplug_update_tasks_legacy(cs, &new_cpus, &new_mems,
					    cpus_updated, mems_updated);

	percpu_up_write(&cpuset_rwsem);
}