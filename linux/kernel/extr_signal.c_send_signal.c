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
struct user_namespace {int dummy; } ;
struct task_struct {int dummy; } ;
struct kernel_siginfo {scalar_t__ si_code; scalar_t__ si_pid; int /*<<< orphan*/  si_uid; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  enum pid_type { ____Placeholder_pid_type } pid_type ;

/* Variables and functions */
 struct kernel_siginfo* SEND_SIG_NOINFO ; 
 struct kernel_siginfo* SEND_SIG_PRIV ; 
 scalar_t__ SI_KERNEL ; 
 int __send_signal (int,struct kernel_siginfo*,struct task_struct*,int,int) ; 
 int /*<<< orphan*/  current ; 
 struct user_namespace* current_user_ns () ; 
 int /*<<< orphan*/  from_kuid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 scalar_t__ has_si_pid_and_uid (struct kernel_siginfo*) ; 
 int /*<<< orphan*/  make_kuid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  task_active_pid_ns (struct task_struct*) ; 
 struct user_namespace* task_cred_xxx (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid_nr_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_ns ; 

__attribute__((used)) static int send_signal(int sig, struct kernel_siginfo *info, struct task_struct *t,
			enum pid_type type)
{
	/* Should SIGKILL or SIGSTOP be received by a pid namespace init? */
	bool force = false;

	if (info == SEND_SIG_NOINFO) {
		/* Force if sent from an ancestor pid namespace */
		force = !task_pid_nr_ns(current, task_active_pid_ns(t));
	} else if (info == SEND_SIG_PRIV) {
		/* Don't ignore kernel generated signals */
		force = true;
	} else if (has_si_pid_and_uid(info)) {
		/* SIGKILL and SIGSTOP is special or has ids */
		struct user_namespace *t_user_ns;

		rcu_read_lock();
		t_user_ns = task_cred_xxx(t, user_ns);
		if (current_user_ns() != t_user_ns) {
			kuid_t uid = make_kuid(current_user_ns(), info->si_uid);
			info->si_uid = from_kuid_munged(t_user_ns, uid);
		}
		rcu_read_unlock();

		/* A kernel generated signal? */
		force = (info->si_code == SI_KERNEL);

		/* From an ancestor pid namespace? */
		if (!task_pid_nr_ns(current, task_active_pid_ns(t))) {
			info->si_pid = 0;
			force = true;
		}
	}
	return __send_signal(sig, info, t, type, force);
}