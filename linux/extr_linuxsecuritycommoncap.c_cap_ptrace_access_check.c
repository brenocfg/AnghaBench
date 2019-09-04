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
struct cred {scalar_t__ user_ns; int /*<<< orphan*/  cap_permitted; int /*<<< orphan*/  cap_effective; } ;
typedef  int /*<<< orphan*/  kernel_cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_PTRACE ; 
 int EPERM ; 
 unsigned int PTRACE_MODE_FSCREDS ; 
 struct cred* __task_cred (struct task_struct*) ; 
 scalar_t__ cap_issubset (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 struct cred* current_cred () ; 
 scalar_t__ ns_capable (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int cap_ptrace_access_check(struct task_struct *child, unsigned int mode)
{
	int ret = 0;
	const struct cred *cred, *child_cred;
	const kernel_cap_t *caller_caps;

	rcu_read_lock();
	cred = current_cred();
	child_cred = __task_cred(child);
	if (mode & PTRACE_MODE_FSCREDS)
		caller_caps = &cred->cap_effective;
	else
		caller_caps = &cred->cap_permitted;
	if (cred->user_ns == child_cred->user_ns &&
	    cap_issubset(child_cred->cap_permitted, *caller_caps))
		goto out;
	if (ns_capable(child_cred->user_ns, CAP_SYS_PTRACE))
		goto out;
	ret = -EPERM;
out:
	rcu_read_unlock();
	return ret;
}