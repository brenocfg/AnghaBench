#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {TYPE_1__* nsproxy; } ;
struct ns_common {int dummy; } ;
struct pid_namespace {struct ns_common ns; int /*<<< orphan*/  child_reaper; } ;
struct TYPE_2__ {struct pid_namespace* pid_ns_for_children; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_pid_ns (struct pid_namespace*) ; 
 int /*<<< orphan*/  put_pid_ns (struct pid_namespace*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 

__attribute__((used)) static struct ns_common *pidns_for_children_get(struct task_struct *task)
{
	struct pid_namespace *ns = NULL;

	task_lock(task);
	if (task->nsproxy) {
		ns = task->nsproxy->pid_ns_for_children;
		get_pid_ns(ns);
	}
	task_unlock(task);

	if (ns) {
		read_lock(&tasklist_lock);
		if (!ns->child_reaper) {
			put_pid_ns(ns);
			ns = NULL;
		}
		read_unlock(&tasklist_lock);
	}

	return ns ? &ns->ns : NULL;
}