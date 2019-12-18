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
struct task_struct {struct nsproxy* nsproxy; } ;
struct nsproxy {int /*<<< orphan*/  net_ns; } ;
struct net {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDTYPE_PID ; 
 struct net* get_net (int /*<<< orphan*/ ) ; 
 struct task_struct* pid_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_pid (struct inode*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

__attribute__((used)) static struct net *get_proc_task_net(struct inode *dir)
{
	struct task_struct *task;
	struct nsproxy *ns;
	struct net *net = NULL;

	rcu_read_lock();
	task = pid_task(proc_pid(dir), PIDTYPE_PID);
	if (task != NULL) {
		task_lock(task);
		ns = task->nsproxy;
		if (ns != NULL)
			net = get_net(ns->net_ns);
		task_unlock(task);
	}
	rcu_read_unlock();

	return net;
}