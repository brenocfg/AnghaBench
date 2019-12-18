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
struct task_struct {TYPE_3__* sighand; TYPE_2__* signal; int /*<<< orphan*/  ptrace; int /*<<< orphan*/  blocked; } ;
struct kernel_siginfo {int si_signo; } ;
struct TYPE_4__ {scalar_t__ sa_handler; } ;
struct k_sigaction {TYPE_1__ sa; } ;
struct TYPE_6__ {int /*<<< orphan*/  siglock; struct k_sigaction* action; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int /*<<< orphan*/  SIGNAL_UNKILLABLE ; 
 scalar_t__ SIG_DFL ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  recalc_sigpending_and_wake (struct task_struct*) ; 
 int send_signal (int,struct kernel_siginfo*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int) ; 
 int sigismember (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
force_sig_info_to_task(struct kernel_siginfo *info, struct task_struct *t)
{
	unsigned long int flags;
	int ret, blocked, ignored;
	struct k_sigaction *action;
	int sig = info->si_signo;

	spin_lock_irqsave(&t->sighand->siglock, flags);
	action = &t->sighand->action[sig-1];
	ignored = action->sa.sa_handler == SIG_IGN;
	blocked = sigismember(&t->blocked, sig);
	if (blocked || ignored) {
		action->sa.sa_handler = SIG_DFL;
		if (blocked) {
			sigdelset(&t->blocked, sig);
			recalc_sigpending_and_wake(t);
		}
	}
	/*
	 * Don't clear SIGNAL_UNKILLABLE for traced tasks, users won't expect
	 * debugging to leave init killable.
	 */
	if (action->sa.sa_handler == SIG_DFL && !t->ptrace)
		t->signal->flags &= ~SIGNAL_UNKILLABLE;
	ret = send_signal(sig, info, t, PIDTYPE_PID);
	spin_unlock_irqrestore(&t->sighand->siglock, flags);

	return ret;
}