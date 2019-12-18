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
struct task_struct {int flags; scalar_t__ frozen; } ;
struct cgroup {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGRP_FREEZE ; 
 int PF_KTHREAD ; 
 int /*<<< orphan*/  cgroup_dec_frozen_cnt (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_freeze_task (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_inc_frozen_cnt (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_update_frozen (struct cgroup*) ; 
 int /*<<< orphan*/  css_set_lock ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void cgroup_freezer_migrate_task(struct task_struct *task,
				 struct cgroup *src, struct cgroup *dst)
{
	lockdep_assert_held(&css_set_lock);

	/*
	 * Kernel threads are not supposed to be frozen at all.
	 */
	if (task->flags & PF_KTHREAD)
		return;

	/*
	 * Adjust counters of freezing and frozen tasks.
	 * Note, that if the task is frozen, but the destination cgroup is not
	 * frozen, we bump both counters to keep them balanced.
	 */
	if (task->frozen) {
		cgroup_inc_frozen_cnt(dst);
		cgroup_dec_frozen_cnt(src);
	}
	cgroup_update_frozen(dst);
	cgroup_update_frozen(src);

	/*
	 * Force the task to the desired state.
	 */
	cgroup_freeze_task(task, test_bit(CGRP_FREEZE, &dst->flags));
}