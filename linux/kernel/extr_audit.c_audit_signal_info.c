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
typedef  int /*<<< orphan*/  kuid_t ;

/* Variables and functions */
 int SIGHUP ; 
 int SIGTERM ; 
 int SIGUSR1 ; 
 int SIGUSR2 ; 
 int /*<<< orphan*/  audit_get_loginuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_sig_pid ; 
 int /*<<< orphan*/  audit_sig_sid ; 
 int /*<<< orphan*/  audit_sig_uid ; 
 int audit_signal_info_syscall (struct task_struct*) ; 
 scalar_t__ auditd_test_task (struct task_struct*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_uid () ; 
 int /*<<< orphan*/  security_task_getsecid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_tgid_nr (int /*<<< orphan*/ ) ; 
 scalar_t__ uid_valid (int /*<<< orphan*/ ) ; 

int audit_signal_info(int sig, struct task_struct *t)
{
	kuid_t uid = current_uid(), auid;

	if (auditd_test_task(t) &&
	    (sig == SIGTERM || sig == SIGHUP ||
	     sig == SIGUSR1 || sig == SIGUSR2)) {
		audit_sig_pid = task_tgid_nr(current);
		auid = audit_get_loginuid(current);
		if (uid_valid(auid))
			audit_sig_uid = auid;
		else
			audit_sig_uid = uid;
		security_task_getsecid(current, &audit_sig_sid);
	}

	return audit_signal_info_syscall(t);
}