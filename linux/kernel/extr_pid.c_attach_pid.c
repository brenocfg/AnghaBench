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
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pid** task_pid_ptr (struct task_struct*,int) ; 

void attach_pid(struct task_struct *task, enum pid_type type)
{
	struct pid *pid = *task_pid_ptr(task, type);
	hlist_add_head_rcu(&task->pid_links[type], &pid->tasks[type]);
}