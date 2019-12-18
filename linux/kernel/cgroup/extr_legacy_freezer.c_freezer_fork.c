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
struct task_struct {int dummy; } ;
struct freezer {int state; } ;

/* Variables and functions */
 int CGROUP_FREEZING ; 
 int /*<<< orphan*/  freeze_task (struct task_struct*) ; 
 int /*<<< orphan*/  freezer_cgrp_id ; 
 int /*<<< orphan*/  freezer_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ task_css_is_root (struct task_struct*,int /*<<< orphan*/ ) ; 
 struct freezer* task_freezer (struct task_struct*) ; 

__attribute__((used)) static void freezer_fork(struct task_struct *task)
{
	struct freezer *freezer;

	/*
	 * The root cgroup is non-freezable, so we can skip locking the
	 * freezer.  This is safe regardless of race with task migration.
	 * If we didn't race or won, skipping is obviously the right thing
	 * to do.  If we lost and root is the new cgroup, noop is still the
	 * right thing to do.
	 */
	if (task_css_is_root(task, freezer_cgrp_id))
		return;

	mutex_lock(&freezer_mutex);
	rcu_read_lock();

	freezer = task_freezer(task);
	if (freezer->state & CGROUP_FREEZING)
		freeze_task(task);

	rcu_read_unlock();
	mutex_unlock(&freezer_mutex);
}