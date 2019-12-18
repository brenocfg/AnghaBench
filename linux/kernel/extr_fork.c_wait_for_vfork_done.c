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
struct task_struct {int /*<<< orphan*/ * vfork_done; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_enter_frozen () ; 
 int /*<<< orphan*/  cgroup_leave_frozen (int) ; 
 int /*<<< orphan*/  freezer_count () ; 
 int /*<<< orphan*/  freezer_do_not_count () ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 int wait_for_completion_killable (struct completion*) ; 

__attribute__((used)) static int wait_for_vfork_done(struct task_struct *child,
				struct completion *vfork)
{
	int killed;

	freezer_do_not_count();
	cgroup_enter_frozen();
	killed = wait_for_completion_killable(vfork);
	cgroup_leave_frozen(false);
	freezer_count();

	if (killed) {
		task_lock(child);
		child->vfork_done = NULL;
		task_unlock(child);
	}

	put_task_struct(child);
	return killed;
}