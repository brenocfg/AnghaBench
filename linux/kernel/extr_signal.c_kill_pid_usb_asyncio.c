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
struct kernel_siginfo {int si_signo; int si_errno; int /*<<< orphan*/  si_pid; int /*<<< orphan*/  si_code; } ;
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  sigval_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int ESRCH ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int /*<<< orphan*/  PIDTYPE_TGID ; 
 int /*<<< orphan*/  SI_ASYNCIO ; 
 int __send_signal (int,struct kernel_siginfo*,struct task_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_siginfo (struct kernel_siginfo*) ; 
 int /*<<< orphan*/  kill_as_cred_perm (struct cred const*,struct task_struct*) ; 
 scalar_t__ lock_task_sighand (struct task_struct*,unsigned long*) ; 
 struct task_struct* pid_task (struct pid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int security_task_kill (struct task_struct*,struct kernel_siginfo*,int,struct cred const*) ; 
 int /*<<< orphan*/  unlock_task_sighand (struct task_struct*,unsigned long*) ; 
 int /*<<< orphan*/  valid_signal (int) ; 

int kill_pid_usb_asyncio(int sig, int errno, sigval_t addr,
			 struct pid *pid, const struct cred *cred)
{
	struct kernel_siginfo info;
	struct task_struct *p;
	unsigned long flags;
	int ret = -EINVAL;

	clear_siginfo(&info);
	info.si_signo = sig;
	info.si_errno = errno;
	info.si_code = SI_ASYNCIO;
	*((sigval_t *)&info.si_pid) = addr;

	if (!valid_signal(sig))
		return ret;

	rcu_read_lock();
	p = pid_task(pid, PIDTYPE_PID);
	if (!p) {
		ret = -ESRCH;
		goto out_unlock;
	}
	if (!kill_as_cred_perm(cred, p)) {
		ret = -EPERM;
		goto out_unlock;
	}
	ret = security_task_kill(p, &info, sig, cred);
	if (ret)
		goto out_unlock;

	if (sig) {
		if (lock_task_sighand(p, &flags)) {
			ret = __send_signal(sig, &info, p, PIDTYPE_TGID, false);
			unlock_task_sighand(p, &flags);
		} else
			ret = -ESRCH;
	}
out_unlock:
	rcu_read_unlock();
	return ret;
}