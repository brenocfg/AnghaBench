#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct task_struct {int exit_code; struct sighand_struct* sighand; TYPE_1__* signal; struct task_struct* real_parent; struct task_struct* group_leader; struct task_struct* parent; } ;
struct sighand_struct {int /*<<< orphan*/  siglock; TYPE_3__* action; } ;
struct kernel_siginfo {int si_signo; int si_code; int si_status; void* si_stime; void* si_utime; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; scalar_t__ si_errno; } ;
struct TYPE_5__ {scalar_t__ sa_handler; int sa_flags; } ;
struct TYPE_6__ {TYPE_2__ sa; } ;
struct TYPE_4__ {int group_exit_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CLD_CONTINUED 130 
#define  CLD_STOPPED 129 
#define  CLD_TRAPPED 128 
 int SA_NOCLDSTOP ; 
 int SIGCHLD ; 
 int SIGCONT ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  __group_send_sig_info (int,struct kernel_siginfo*,struct task_struct*) ; 
 int /*<<< orphan*/  __wake_up_parent (struct task_struct*,struct task_struct*) ; 
 int /*<<< orphan*/  clear_siginfo (struct kernel_siginfo*) ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* nsec_to_clock_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  task_active_pid_ns (struct task_struct*) ; 
 int /*<<< orphan*/  task_cputime (struct task_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_cred_xxx (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid_nr_ns (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_uid (struct task_struct*) ; 
 int /*<<< orphan*/  user_ns ; 

__attribute__((used)) static void do_notify_parent_cldstop(struct task_struct *tsk,
				     bool for_ptracer, int why)
{
	struct kernel_siginfo info;
	unsigned long flags;
	struct task_struct *parent;
	struct sighand_struct *sighand;
	u64 utime, stime;

	if (for_ptracer) {
		parent = tsk->parent;
	} else {
		tsk = tsk->group_leader;
		parent = tsk->real_parent;
	}

	clear_siginfo(&info);
	info.si_signo = SIGCHLD;
	info.si_errno = 0;
	/*
	 * see comment in do_notify_parent() about the following 4 lines
	 */
	rcu_read_lock();
	info.si_pid = task_pid_nr_ns(tsk, task_active_pid_ns(parent));
	info.si_uid = from_kuid_munged(task_cred_xxx(parent, user_ns), task_uid(tsk));
	rcu_read_unlock();

	task_cputime(tsk, &utime, &stime);
	info.si_utime = nsec_to_clock_t(utime);
	info.si_stime = nsec_to_clock_t(stime);

 	info.si_code = why;
 	switch (why) {
 	case CLD_CONTINUED:
 		info.si_status = SIGCONT;
 		break;
 	case CLD_STOPPED:
 		info.si_status = tsk->signal->group_exit_code & 0x7f;
 		break;
 	case CLD_TRAPPED:
 		info.si_status = tsk->exit_code & 0x7f;
 		break;
 	default:
 		BUG();
 	}

	sighand = parent->sighand;
	spin_lock_irqsave(&sighand->siglock, flags);
	if (sighand->action[SIGCHLD-1].sa.sa_handler != SIG_IGN &&
	    !(sighand->action[SIGCHLD-1].sa.sa_flags & SA_NOCLDSTOP))
		__group_send_sig_info(SIGCHLD, &info, parent);
	/*
	 * Even if SIGCHLD is not generated, we must wake up wait4 calls.
	 */
	__wake_up_parent(tsk, parent);
	spin_unlock_irqrestore(&sighand->siglock, flags);
}