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
struct dlm_ls {int /*<<< orphan*/  ls_in_recovery; int /*<<< orphan*/  ls_flags; int /*<<< orphan*/  ls_recover_lock_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSFL_RECOVER_DOWN ; 
 int /*<<< orphan*/  LSFL_RECOVER_LOCK ; 
 int /*<<< orphan*/  LSFL_RECOVER_WORK ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 struct dlm_ls* dlm_find_lockspace_local (void*) ; 
 int /*<<< orphan*/  dlm_put_lockspace (struct dlm_ls*) ; 
 int /*<<< orphan*/  do_ls_recovery (struct dlm_ls*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  log_print (char*,void*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_recoverd(void *arg)
{
	struct dlm_ls *ls;

	ls = dlm_find_lockspace_local(arg);
	if (!ls) {
		log_print("dlm_recoverd: no lockspace %p", arg);
		return -1;
	}

	down_write(&ls->ls_in_recovery);
	set_bit(LSFL_RECOVER_LOCK, &ls->ls_flags);
	wake_up(&ls->ls_recover_lock_wait);

	while (1) {
		/*
		 * We call kthread_should_stop() after set_current_state().
		 * This is because it works correctly if kthread_stop() is
		 * called just before set_current_state().
		 */
		set_current_state(TASK_INTERRUPTIBLE);
		if (kthread_should_stop()) {
			set_current_state(TASK_RUNNING);
			break;
		}
		if (!test_bit(LSFL_RECOVER_WORK, &ls->ls_flags) &&
		    !test_bit(LSFL_RECOVER_DOWN, &ls->ls_flags)) {
			if (kthread_should_stop())
				break;
			schedule();
		}
		set_current_state(TASK_RUNNING);

		if (test_and_clear_bit(LSFL_RECOVER_DOWN, &ls->ls_flags)) {
			down_write(&ls->ls_in_recovery);
			set_bit(LSFL_RECOVER_LOCK, &ls->ls_flags);
			wake_up(&ls->ls_recover_lock_wait);
		}

		if (test_and_clear_bit(LSFL_RECOVER_WORK, &ls->ls_flags))
			do_ls_recovery(ls);
	}

	if (test_bit(LSFL_RECOVER_LOCK, &ls->ls_flags))
		up_write(&ls->ls_in_recovery);

	dlm_put_lockspace(ls);
	return 0;
}