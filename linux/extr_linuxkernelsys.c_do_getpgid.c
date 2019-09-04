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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int ESRCH ; 
 struct task_struct* current ; 
 struct task_struct* find_task_by_vpid (int /*<<< orphan*/ ) ; 
 int pid_vnr (struct pid*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int security_task_getpgid (struct task_struct*) ; 
 struct pid* task_pgrp (struct task_struct*) ; 

__attribute__((used)) static int do_getpgid(pid_t pid)
{
	struct task_struct *p;
	struct pid *grp;
	int retval;

	rcu_read_lock();
	if (!pid)
		grp = task_pgrp(current);
	else {
		retval = -ESRCH;
		p = find_task_by_vpid(pid);
		if (!p)
			goto out;
		grp = task_pgrp(p);
		if (!grp)
			goto out;

		retval = security_task_getpgid(p);
		if (retval)
			goto out;
	}
	retval = pid_vnr(grp);
out:
	rcu_read_unlock();
	return retval;
}