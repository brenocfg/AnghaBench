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
struct ns_common {int dummy; } ;
struct pid_namespace {struct ns_common ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_pid_ns (struct pid_namespace*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct pid_namespace* task_active_pid_ns (struct task_struct*) ; 

__attribute__((used)) static struct ns_common *pidns_get(struct task_struct *task)
{
	struct pid_namespace *ns;

	rcu_read_lock();
	ns = task_active_pid_ns(task);
	if (ns)
		get_pid_ns(ns);
	rcu_read_unlock();

	return ns ? &ns->ns : NULL;
}