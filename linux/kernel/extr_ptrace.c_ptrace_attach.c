#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int flags; int exit_state; long ptrace; int /*<<< orphan*/  jobctl; TYPE_2__* signal; TYPE_1__* sighand; } ;
struct TYPE_4__ {int /*<<< orphan*/  cred_guard_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int EIO ; 
 int EPERM ; 
 int ERESTARTNOINTR ; 
 int JOBCTL_TRAPPING ; 
 int /*<<< orphan*/  JOBCTL_TRAPPING_BIT ; 
 int JOBCTL_TRAP_STOP ; 
 int PF_KTHREAD ; 
 int /*<<< orphan*/  PTRACE_ATTACH ; 
 int /*<<< orphan*/  PTRACE_MODE_ATTACH_REALCREDS ; 
 scalar_t__ PTRACE_O_MASK ; 
 long PTRACE_SEIZE ; 
 unsigned long PT_OPT_FLAG_SHIFT ; 
 unsigned long PT_PTRACED ; 
 unsigned long PT_SEIZED ; 
 int /*<<< orphan*/  SEND_SIG_PRIV ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  __TASK_STOPPED ; 
 int __ptrace_may_access (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_ptrace (struct task_struct*) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_ptrace_connector (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptrace_link (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ same_thread_group (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_sig_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  signal_wake_up_state (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ task_is_stopped (struct task_struct*) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 scalar_t__ task_set_jobctl_pending (struct task_struct*,int) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ptrace_attach(struct task_struct *task, long request,
			 unsigned long addr,
			 unsigned long flags)
{
	bool seize = (request == PTRACE_SEIZE);
	int retval;

	retval = -EIO;
	if (seize) {
		if (addr != 0)
			goto out;
		if (flags & ~(unsigned long)PTRACE_O_MASK)
			goto out;
		flags = PT_PTRACED | PT_SEIZED | (flags << PT_OPT_FLAG_SHIFT);
	} else {
		flags = PT_PTRACED;
	}

	audit_ptrace(task);

	retval = -EPERM;
	if (unlikely(task->flags & PF_KTHREAD))
		goto out;
	if (same_thread_group(task, current))
		goto out;

	/*
	 * Protect exec's credential calculations against our interference;
	 * SUID, SGID and LSM creds get determined differently
	 * under ptrace.
	 */
	retval = -ERESTARTNOINTR;
	if (mutex_lock_interruptible(&task->signal->cred_guard_mutex))
		goto out;

	task_lock(task);
	retval = __ptrace_may_access(task, PTRACE_MODE_ATTACH_REALCREDS);
	task_unlock(task);
	if (retval)
		goto unlock_creds;

	write_lock_irq(&tasklist_lock);
	retval = -EPERM;
	if (unlikely(task->exit_state))
		goto unlock_tasklist;
	if (task->ptrace)
		goto unlock_tasklist;

	if (seize)
		flags |= PT_SEIZED;
	task->ptrace = flags;

	ptrace_link(task, current);

	/* SEIZE doesn't trap tracee on attach */
	if (!seize)
		send_sig_info(SIGSTOP, SEND_SIG_PRIV, task);

	spin_lock(&task->sighand->siglock);

	/*
	 * If the task is already STOPPED, set JOBCTL_TRAP_STOP and
	 * TRAPPING, and kick it so that it transits to TRACED.  TRAPPING
	 * will be cleared if the child completes the transition or any
	 * event which clears the group stop states happens.  We'll wait
	 * for the transition to complete before returning from this
	 * function.
	 *
	 * This hides STOPPED -> RUNNING -> TRACED transition from the
	 * attaching thread but a different thread in the same group can
	 * still observe the transient RUNNING state.  IOW, if another
	 * thread's WNOHANG wait(2) on the stopped tracee races against
	 * ATTACH, the wait(2) may fail due to the transient RUNNING.
	 *
	 * The following task_is_stopped() test is safe as both transitions
	 * in and out of STOPPED are protected by siglock.
	 */
	if (task_is_stopped(task) &&
	    task_set_jobctl_pending(task, JOBCTL_TRAP_STOP | JOBCTL_TRAPPING))
		signal_wake_up_state(task, __TASK_STOPPED);

	spin_unlock(&task->sighand->siglock);

	retval = 0;
unlock_tasklist:
	write_unlock_irq(&tasklist_lock);
unlock_creds:
	mutex_unlock(&task->signal->cred_guard_mutex);
out:
	if (!retval) {
		/*
		 * We do not bother to change retval or clear JOBCTL_TRAPPING
		 * if wait_on_bit() was interrupted by SIGKILL. The tracer will
		 * not return to user-mode, it will exit and clear this bit in
		 * __ptrace_unlink() if it wasn't already cleared by the tracee;
		 * and until then nobody can ptrace this task.
		 */
		wait_on_bit(&task->jobctl, JOBCTL_TRAPPING_BIT, TASK_KILLABLE);
		proc_ptrace_connector(task, PTRACE_ATTACH);
	}

	return retval;
}