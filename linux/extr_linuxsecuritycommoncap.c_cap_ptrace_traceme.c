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
struct cred {scalar_t__ user_ns; int /*<<< orphan*/  cap_permitted; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_PTRACE ; 
 int EPERM ; 
 struct cred* __task_cred (struct task_struct*) ; 
 scalar_t__ cap_issubset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cred* current_cred () ; 
 scalar_t__ has_ns_capability (struct task_struct*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int cap_ptrace_traceme(struct task_struct *parent)
{
	int ret = 0;
	const struct cred *cred, *child_cred;

	rcu_read_lock();
	cred = __task_cred(parent);
	child_cred = current_cred();
	if (cred->user_ns == child_cred->user_ns &&
	    cap_issubset(child_cred->cap_permitted, cred->cap_permitted))
		goto out;
	if (has_ns_capability(parent, child_cred->user_ns, CAP_SYS_PTRACE))
		goto out;
	ret = -EPERM;
out:
	rcu_read_unlock();
	return ret;
}