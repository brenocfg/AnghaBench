#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct linux_binprm {int /*<<< orphan*/  per_clear; int /*<<< orphan*/ * mm; int /*<<< orphan*/  file; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  files; int /*<<< orphan*/  personality; } ;

/* Variables and functions */
 int PF_FORKNOEXEC ; 
 int PF_KTHREAD ; 
 int PF_NOFREEZE ; 
 int PF_NO_SETAFFINITY ; 
 int PF_RANDOMIZE ; 
 int /*<<< orphan*/  USER_DS ; 
 int /*<<< orphan*/  acct_arg_size (struct linux_binprm*,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int de_thread (TYPE_1__*) ; 
 int /*<<< orphan*/  do_close_on_exec (int /*<<< orphan*/ ) ; 
 int exec_mmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_thread () ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mm_exe_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int flush_old_exec(struct linux_binprm * bprm)
{
	int retval;

	/*
	 * Make sure we have a private signal table and that
	 * we are unassociated from the previous thread group.
	 */
	retval = de_thread(current);
	if (retval)
		goto out;

	/*
	 * Must be called _before_ exec_mmap() as bprm->mm is
	 * not visibile until then. This also enables the update
	 * to be lockless.
	 */
	set_mm_exe_file(bprm->mm, bprm->file);

	/*
	 * Release all of the old mmap stuff
	 */
	acct_arg_size(bprm, 0);
	retval = exec_mmap(bprm->mm);
	if (retval)
		goto out;

	/*
	 * After clearing bprm->mm (to mark that current is using the
	 * prepared mm now), we have nothing left of the original
	 * process. If anything from here on returns an error, the check
	 * in search_binary_handler() will SEGV current.
	 */
	bprm->mm = NULL;

	set_fs(USER_DS);
	current->flags &= ~(PF_RANDOMIZE | PF_FORKNOEXEC | PF_KTHREAD |
					PF_NOFREEZE | PF_NO_SETAFFINITY);
	flush_thread();
	current->personality &= ~bprm->per_clear;

	/*
	 * We have to apply CLOEXEC before we change whether the process is
	 * dumpable (in setup_new_exec) to avoid a race with a process in userspace
	 * trying to access the should-be-closed file descriptors of a process
	 * undergoing exec(2).
	 */
	do_close_on_exec(current->files);
	return 0;

out:
	return retval;
}