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
struct task_struct {scalar_t__ exit_state; } ;
struct poll_table_struct {int dummy; } ;
struct pid {int /*<<< orphan*/  wait_pidfd; } ;
struct file {struct pid* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int POLLIN ; 
 int POLLRDNORM ; 
 struct task_struct* pid_task (struct pid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ thread_group_empty (struct task_struct*) ; 

__attribute__((used)) static unsigned int pidfd_poll(struct file *file, struct poll_table_struct *pts)
{
	struct task_struct *task;
	struct pid *pid = file->private_data;
	int poll_flags = 0;

	poll_wait(file, &pid->wait_pidfd, pts);

	rcu_read_lock();
	task = pid_task(pid, PIDTYPE_PID);
	/*
	 * Inform pollers only when the whole thread group exits.
	 * If the thread group leader exits before all other threads in the
	 * group, then poll(2) should block, similar to the wait(2) family.
	 */
	if (!task || (task->exit_state && thread_group_empty(task)))
		poll_flags = POLLIN | POLLRDNORM;
	rcu_read_unlock();

	return poll_flags;
}