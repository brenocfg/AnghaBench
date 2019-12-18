#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cgroup_subsys_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  effective_mems; int /*<<< orphan*/  mems_allowed; int /*<<< orphan*/  effective_cpus; int /*<<< orphan*/  cpus_allowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  callback_lock ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuset_rwsem ; 
 scalar_t__ is_in_v2_mode () ; 
 int /*<<< orphan*/  node_possible_map ; 
 int /*<<< orphan*/  percpu_down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 TYPE_1__ top_cpuset ; 

__attribute__((used)) static void cpuset_bind(struct cgroup_subsys_state *root_css)
{
	percpu_down_write(&cpuset_rwsem);
	spin_lock_irq(&callback_lock);

	if (is_in_v2_mode()) {
		cpumask_copy(top_cpuset.cpus_allowed, cpu_possible_mask);
		top_cpuset.mems_allowed = node_possible_map;
	} else {
		cpumask_copy(top_cpuset.cpus_allowed,
			     top_cpuset.effective_cpus);
		top_cpuset.mems_allowed = top_cpuset.effective_mems;
	}

	spin_unlock_irq(&callback_lock);
	percpu_up_write(&cpuset_rwsem);
}