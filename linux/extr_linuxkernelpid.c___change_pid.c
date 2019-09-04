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
struct task_struct {int /*<<< orphan*/ * pid_links; } ;
struct pid {int /*<<< orphan*/ * tasks; } ;
typedef  enum pid_type { ____Placeholder_pid_type } pid_type ;

/* Variables and functions */
 int PIDTYPE_MAX ; 
 int /*<<< orphan*/  free_pid (struct pid*) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 struct pid** task_pid_ptr (struct task_struct*,int) ; 

__attribute__((used)) static void __change_pid(struct task_struct *task, enum pid_type type,
			struct pid *new)
{
	struct pid **pid_ptr = task_pid_ptr(task, type);
	struct pid *pid;
	int tmp;

	pid = *pid_ptr;

	hlist_del_rcu(&task->pid_links[type]);
	*pid_ptr = new;

	for (tmp = PIDTYPE_MAX; --tmp >= 0; )
		if (!hlist_empty(&pid->tasks[tmp]))
			return;

	free_pid(pid);
}