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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int /*<<< orphan*/  current ; 
 int generic_permission (struct inode*,int) ; 
 struct task_struct* pid_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_pid (struct inode*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ same_thread_group (struct task_struct*,int /*<<< orphan*/ ) ; 

int proc_fd_permission(struct inode *inode, int mask)
{
	struct task_struct *p;
	int rv;

	rv = generic_permission(inode, mask);
	if (rv == 0)
		return rv;

	rcu_read_lock();
	p = pid_task(proc_pid(inode), PIDTYPE_PID);
	if (p && same_thread_group(p, current))
		rv = 0;
	rcu_read_unlock();

	return rv;
}