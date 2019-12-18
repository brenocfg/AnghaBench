#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct task_struct {scalar_t__ parent_exec_id; int exit_code; TYPE_4__* parent; int /*<<< orphan*/  ptrace; TYPE_1__* signal; struct task_struct* group_leader; } ;
struct sighand_struct {int /*<<< orphan*/  siglock; TYPE_3__* action; } ;
struct kernel_siginfo {int si_signo; int si_status; int /*<<< orphan*/  si_code; void* si_stime; void* si_utime; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; scalar_t__ si_errno; } ;
struct TYPE_11__ {scalar_t__ self_exec_id; struct sighand_struct* sighand; } ;
struct TYPE_9__ {scalar_t__ sa_handler; int sa_flags; } ;
struct TYPE_10__ {TYPE_2__ sa; } ;
struct TYPE_8__ {scalar_t__ stime; scalar_t__ utime; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CLD_DUMPED ; 
 int /*<<< orphan*/  CLD_EXITED ; 
 int /*<<< orphan*/  CLD_KILLED ; 
 int SA_NOCLDWAIT ; 
 int SIGCHLD ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  __group_send_sig_info (int,struct kernel_siginfo*,TYPE_4__*) ; 
 int /*<<< orphan*/  __wake_up_parent (struct task_struct*,TYPE_4__*) ; 
 int /*<<< orphan*/  clear_siginfo (struct kernel_siginfo*) ; 
 int /*<<< orphan*/  do_notify_pidfd (struct task_struct*) ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* nsec_to_clock_t (scalar_t__) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  task_active_pid_ns (TYPE_4__*) ; 
 int /*<<< orphan*/  task_cputime (struct task_struct*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  task_cred_xxx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int task_is_stopped_or_traced (struct task_struct*) ; 
 int /*<<< orphan*/  task_pid_nr_ns (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_uid (struct task_struct*) ; 
 int /*<<< orphan*/  thread_group_empty (struct task_struct*) ; 
 int /*<<< orphan*/  user_ns ; 
 scalar_t__ valid_signal (int) ; 

bool do_notify_parent(struct task_struct *tsk, int sig)
{
	struct kernel_siginfo info;
	unsigned long flags;
	struct sighand_struct *psig;
	bool autoreap = false;
	u64 utime, stime;

	BUG_ON(sig == -1);

 	/* do_notify_parent_cldstop should have been called instead.  */
 	BUG_ON(task_is_stopped_or_traced(tsk));

	BUG_ON(!tsk->ptrace &&
	       (tsk->group_leader != tsk || !thread_group_empty(tsk)));

	/* Wake up all pidfd waiters */
	do_notify_pidfd(tsk);

	if (sig != SIGCHLD) {
		/*
		 * This is only possible if parent == real_parent.
		 * Check if it has changed security domain.
		 */
		if (tsk->parent_exec_id != tsk->parent->self_exec_id)
			sig = SIGCHLD;
	}

	clear_siginfo(&info);
	info.si_signo = sig;
	info.si_errno = 0;
	/*
	 * We are under tasklist_lock here so our parent is tied to
	 * us and cannot change.
	 *
	 * task_active_pid_ns will always return the same pid namespace
	 * until a task passes through release_task.
	 *
	 * write_lock() currently calls preempt_disable() which is the
	 * same as rcu_read_lock(), but according to Oleg, this is not
	 * correct to rely on this
	 */
	rcu_read_lock();
	info.si_pid = task_pid_nr_ns(tsk, task_active_pid_ns(tsk->parent));
	info.si_uid = from_kuid_munged(task_cred_xxx(tsk->parent, user_ns),
				       task_uid(tsk));
	rcu_read_unlock();

	task_cputime(tsk, &utime, &stime);
	info.si_utime = nsec_to_clock_t(utime + tsk->signal->utime);
	info.si_stime = nsec_to_clock_t(stime + tsk->signal->stime);

	info.si_status = tsk->exit_code & 0x7f;
	if (tsk->exit_code & 0x80)
		info.si_code = CLD_DUMPED;
	else if (tsk->exit_code & 0x7f)
		info.si_code = CLD_KILLED;
	else {
		info.si_code = CLD_EXITED;
		info.si_status = tsk->exit_code >> 8;
	}

	psig = tsk->parent->sighand;
	spin_lock_irqsave(&psig->siglock, flags);
	if (!tsk->ptrace && sig == SIGCHLD &&
	    (psig->action[SIGCHLD-1].sa.sa_handler == SIG_IGN ||
	     (psig->action[SIGCHLD-1].sa.sa_flags & SA_NOCLDWAIT))) {
		/*
		 * We are exiting and our parent doesn't care.  POSIX.1
		 * defines special semantics for setting SIGCHLD to SIG_IGN
		 * or setting the SA_NOCLDWAIT flag: we should be reaped
		 * automatically and not left for our parent's wait4 call.
		 * Rather than having the parent do it as a magic kind of
		 * signal handler, we just set this to tell do_exit that we
		 * can be cleaned up without becoming a zombie.  Note that
		 * we still call __wake_up_parent in this case, because a
		 * blocked sys_wait4 might now return -ECHILD.
		 *
		 * Whether we send SIGCHLD or not for SA_NOCLDWAIT
		 * is implementation-defined: we do (if you don't want
		 * it, just use SIG_IGN instead).
		 */
		autoreap = true;
		if (psig->action[SIGCHLD-1].sa.sa_handler == SIG_IGN)
			sig = 0;
	}
	if (valid_signal(sig) && sig)
		__group_send_sig_info(sig, &info, tsk->parent);
	__wake_up_parent(tsk, tsk->parent);
	spin_unlock_irqrestore(&psig->siglock, flags);

	return autoreap;
}