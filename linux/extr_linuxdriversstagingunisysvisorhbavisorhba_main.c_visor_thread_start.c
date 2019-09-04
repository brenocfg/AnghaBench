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

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 struct task_struct* kthread_run (int (*) (void*),void*,char*,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static struct task_struct *visor_thread_start(int (*threadfn)(void *),
					      void *thrcontext, char *name)
{
	struct task_struct *task;

	task = kthread_run(threadfn, thrcontext, "%s", name);
	if (IS_ERR(task)) {
		pr_err("visorbus failed to start thread\n");
		return NULL;
	}
	return task;
}