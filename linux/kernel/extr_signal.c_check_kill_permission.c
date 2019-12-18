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
struct pid {int dummy; } ;
struct kernel_siginfo {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
#define  SIGCONT 128 
 int audit_signal_info (int,struct task_struct*) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  kill_ok_by_cred (struct task_struct*) ; 
 int /*<<< orphan*/  same_thread_group (struct task_struct*,struct task_struct*) ; 
 int security_task_kill (struct task_struct*,struct kernel_siginfo*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  si_fromuser (struct kernel_siginfo*) ; 
 struct pid* task_session (struct task_struct*) ; 
 int /*<<< orphan*/  valid_signal (int) ; 

__attribute__((used)) static int check_kill_permission(int sig, struct kernel_siginfo *info,
				 struct task_struct *t)
{
	struct pid *sid;
	int error;

	if (!valid_signal(sig))
		return -EINVAL;

	if (!si_fromuser(info))
		return 0;

	error = audit_signal_info(sig, t); /* Let audit system see the signal */
	if (error)
		return error;

	if (!same_thread_group(current, t) &&
	    !kill_ok_by_cred(t)) {
		switch (sig) {
		case SIGCONT:
			sid = task_session(t);
			/*
			 * We don't return the error if sid == NULL. The
			 * task was unhashed, the caller must notice this.
			 */
			if (!sid || sid == task_session(current))
				break;
			/* fall through */
		default:
			return -EPERM;
		}
	}

	return security_task_kill(t, info, sig, NULL);
}