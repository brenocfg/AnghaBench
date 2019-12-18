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
struct task_struct {struct mm_struct* mm; } ;
struct mm_struct {int /*<<< orphan*/  user_ns; } ;
struct cred {int /*<<< orphan*/  user_ns; int /*<<< orphan*/  gid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  egid; int /*<<< orphan*/  uid; int /*<<< orphan*/  suid; int /*<<< orphan*/  euid; int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int EPERM ; 
 unsigned int PTRACE_MODE_FSCREDS ; 
 unsigned int PTRACE_MODE_REALCREDS ; 
 scalar_t__ SUID_DUMP_USER ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 struct cred* __task_cred (struct task_struct*) ; 
 int /*<<< orphan*/  current ; 
 struct cred* current_cred () ; 
 scalar_t__ get_dumpable (struct mm_struct*) ; 
 scalar_t__ gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ptrace_has_cap (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ same_thread_group (struct task_struct*,int /*<<< orphan*/ ) ; 
 int security_ptrace_access_check (struct task_struct*,unsigned int) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ptrace_may_access(struct task_struct *task, unsigned int mode)
{
	const struct cred *cred = current_cred(), *tcred;
	struct mm_struct *mm;
	kuid_t caller_uid;
	kgid_t caller_gid;

	if (!(mode & PTRACE_MODE_FSCREDS) == !(mode & PTRACE_MODE_REALCREDS)) {
		WARN(1, "denying ptrace access check without PTRACE_MODE_*CREDS\n");
		return -EPERM;
	}

	/* May we inspect the given task?
	 * This check is used both for attaching with ptrace
	 * and for allowing access to sensitive information in /proc.
	 *
	 * ptrace_attach denies several cases that /proc allows
	 * because setting up the necessary parent/child relationship
	 * or halting the specified task is impossible.
	 */

	/* Don't let security modules deny introspection */
	if (same_thread_group(task, current))
		return 0;
	rcu_read_lock();
	if (mode & PTRACE_MODE_FSCREDS) {
		caller_uid = cred->fsuid;
		caller_gid = cred->fsgid;
	} else {
		/*
		 * Using the euid would make more sense here, but something
		 * in userland might rely on the old behavior, and this
		 * shouldn't be a security problem since
		 * PTRACE_MODE_REALCREDS implies that the caller explicitly
		 * used a syscall that requests access to another process
		 * (and not a filesystem syscall to procfs).
		 */
		caller_uid = cred->uid;
		caller_gid = cred->gid;
	}
	tcred = __task_cred(task);
	if (uid_eq(caller_uid, tcred->euid) &&
	    uid_eq(caller_uid, tcred->suid) &&
	    uid_eq(caller_uid, tcred->uid)  &&
	    gid_eq(caller_gid, tcred->egid) &&
	    gid_eq(caller_gid, tcred->sgid) &&
	    gid_eq(caller_gid, tcred->gid))
		goto ok;
	if (ptrace_has_cap(tcred->user_ns, mode))
		goto ok;
	rcu_read_unlock();
	return -EPERM;
ok:
	rcu_read_unlock();
	/*
	 * If a task drops privileges and becomes nondumpable (through a syscall
	 * like setresuid()) while we are trying to access it, we must ensure
	 * that the dumpability is read after the credentials; otherwise,
	 * we may be able to attach to a task that we shouldn't be able to
	 * attach to (as if the task had dropped privileges without becoming
	 * nondumpable).
	 * Pairs with a write barrier in commit_creds().
	 */
	smp_rmb();
	mm = task->mm;
	if (mm &&
	    ((get_dumpable(mm) != SUID_DUMP_USER) &&
	     !ptrace_has_cap(mm->user_ns, mode)))
	    return -EPERM;

	return security_ptrace_access_check(task, mode);
}