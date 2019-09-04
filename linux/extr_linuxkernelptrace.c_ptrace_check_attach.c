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
struct task_struct {scalar_t__ parent; scalar_t__ state; scalar_t__ ptrace; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ __TASK_TRACED ; 
 scalar_t__ current ; 
 scalar_t__ ptrace_freeze_traced (struct task_struct*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  wait_task_inactive (struct task_struct*,scalar_t__) ; 

__attribute__((used)) static int ptrace_check_attach(struct task_struct *child, bool ignore_state)
{
	int ret = -ESRCH;

	/*
	 * We take the read lock around doing both checks to close a
	 * possible race where someone else was tracing our child and
	 * detached between these two checks.  After this locked check,
	 * we are sure that this is our traced child and that can only
	 * be changed by us so it's not changing right after this.
	 */
	read_lock(&tasklist_lock);
	if (child->ptrace && child->parent == current) {
		WARN_ON(child->state == __TASK_TRACED);
		/*
		 * child->sighand can't be NULL, release_task()
		 * does ptrace_unlink() before __exit_signal().
		 */
		if (ignore_state || ptrace_freeze_traced(child))
			ret = 0;
	}
	read_unlock(&tasklist_lock);

	if (!ret && !ignore_state) {
		if (!wait_task_inactive(child, __TASK_TRACED)) {
			/*
			 * This can only happen if may_ptrace_stop() fails and
			 * ptrace_stop() changes ->state back to TASK_RUNNING,
			 * so we should not worry about leaking __TASK_TRACED.
			 */
			WARN_ON(child->state == __TASK_TRACED);
			ret = -ESRCH;
		}
	}

	return ret;
}