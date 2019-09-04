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
struct task_struct {int /*<<< orphan*/  ptracer_cred; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_PTRACE ; 
 struct cred* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int security_capable_noaudit (struct cred const*,struct user_namespace*,int /*<<< orphan*/ ) ; 

bool ptracer_capable(struct task_struct *tsk, struct user_namespace *ns)
{
	int ret = 0;  /* An absent tracer adds no restrictions */
	const struct cred *cred;
	rcu_read_lock();
	cred = rcu_dereference(tsk->ptracer_cred);
	if (cred)
		ret = security_capable_noaudit(cred, ns, CAP_SYS_PTRACE);
	rcu_read_unlock();
	return (ret == 0);
}