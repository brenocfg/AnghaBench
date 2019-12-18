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
struct task_struct {int flags; } ;
struct css_task_iter {int dummy; } ;
struct TYPE_2__ {scalar_t__ nr_frozen_descendants; } ;
struct cgroup {scalar_t__ nr_descendants; TYPE_1__ freezer; int /*<<< orphan*/  self; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGRP_FREEZE ; 
 int PF_KTHREAD ; 
 int /*<<< orphan*/  TRACE_CGROUP_PATH (int,struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_freeze_task (struct task_struct*,int) ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 int /*<<< orphan*/  cgroup_update_frozen (struct cgroup*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  css_set_lock ; 
 int /*<<< orphan*/  css_task_iter_end (struct css_task_iter*) ; 
 struct task_struct* css_task_iter_next (struct css_task_iter*) ; 
 int /*<<< orphan*/  css_task_iter_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct css_task_iter*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int unfreeze ; 

__attribute__((used)) static void cgroup_do_freeze(struct cgroup *cgrp, bool freeze)
{
	struct css_task_iter it;
	struct task_struct *task;

	lockdep_assert_held(&cgroup_mutex);

	spin_lock_irq(&css_set_lock);
	if (freeze)
		set_bit(CGRP_FREEZE, &cgrp->flags);
	else
		clear_bit(CGRP_FREEZE, &cgrp->flags);
	spin_unlock_irq(&css_set_lock);

	if (freeze)
		TRACE_CGROUP_PATH(freeze, cgrp);
	else
		TRACE_CGROUP_PATH(unfreeze, cgrp);

	css_task_iter_start(&cgrp->self, 0, &it);
	while ((task = css_task_iter_next(&it))) {
		/*
		 * Ignore kernel threads here. Freezing cgroups containing
		 * kthreads isn't supported.
		 */
		if (task->flags & PF_KTHREAD)
			continue;
		cgroup_freeze_task(task, freeze);
	}
	css_task_iter_end(&it);

	/*
	 * Cgroup state should be revisited here to cover empty leaf cgroups
	 * and cgroups which descendants are already in the desired state.
	 */
	spin_lock_irq(&css_set_lock);
	if (cgrp->nr_descendants == cgrp->freezer.nr_frozen_descendants)
		cgroup_update_frozen(cgrp);
	spin_unlock_irq(&css_set_lock);
}