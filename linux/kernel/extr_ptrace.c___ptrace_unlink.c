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
struct task_struct {int flags; int jobctl; TYPE_2__* sighand; TYPE_1__* signal; scalar_t__ ptrace; struct cred* ptracer_cred; int /*<<< orphan*/  ptrace_entry; int /*<<< orphan*/  real_parent; int /*<<< orphan*/  parent; } ;
struct cred {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_3__ {int flags; scalar_t__ group_stop_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int JOBCTL_STOP_PENDING ; 
 int JOBCTL_STOP_SIGMASK ; 
 int /*<<< orphan*/  JOBCTL_TRAP_MASK ; 
 int PF_EXITING ; 
 int SIGNAL_STOP_STOPPED ; 
 int SIGSTOP ; 
 int /*<<< orphan*/  TIF_SYSCALL_EMU ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptrace_signal_wake_up (struct task_struct*,int) ; 
 int /*<<< orphan*/  put_cred (struct cred const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_clear_jobctl_pending (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_clear_jobctl_trapping (struct task_struct*) ; 
 scalar_t__ task_is_traced (struct task_struct*) ; 

void __ptrace_unlink(struct task_struct *child)
{
	const struct cred *old_cred;
	BUG_ON(!child->ptrace);

	clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
#ifdef TIF_SYSCALL_EMU
	clear_tsk_thread_flag(child, TIF_SYSCALL_EMU);
#endif

	child->parent = child->real_parent;
	list_del_init(&child->ptrace_entry);
	old_cred = child->ptracer_cred;
	child->ptracer_cred = NULL;
	put_cred(old_cred);

	spin_lock(&child->sighand->siglock);
	child->ptrace = 0;
	/*
	 * Clear all pending traps and TRAPPING.  TRAPPING should be
	 * cleared regardless of JOBCTL_STOP_PENDING.  Do it explicitly.
	 */
	task_clear_jobctl_pending(child, JOBCTL_TRAP_MASK);
	task_clear_jobctl_trapping(child);

	/*
	 * Reinstate JOBCTL_STOP_PENDING if group stop is in effect and
	 * @child isn't dead.
	 */
	if (!(child->flags & PF_EXITING) &&
	    (child->signal->flags & SIGNAL_STOP_STOPPED ||
	     child->signal->group_stop_count)) {
		child->jobctl |= JOBCTL_STOP_PENDING;

		/*
		 * This is only possible if this thread was cloned by the
		 * traced task running in the stopped group, set the signal
		 * for the future reports.
		 * FIXME: we should change ptrace_init_task() to handle this
		 * case.
		 */
		if (!(child->jobctl & JOBCTL_STOP_SIGMASK))
			child->jobctl |= SIGSTOP;
	}

	/*
	 * If transition to TASK_STOPPED is pending or in TASK_TRACED, kick
	 * @child in the butt.  Note that @resume should be used iff @child
	 * is in TASK_TRACED; otherwise, we might unduly disrupt
	 * TASK_KILLABLE sleeps.
	 */
	if (child->jobctl & JOBCTL_STOP_PENDING || task_is_traced(child))
		ptrace_signal_wake_up(child, true);

	spin_unlock(&child->sighand->siglock);
}