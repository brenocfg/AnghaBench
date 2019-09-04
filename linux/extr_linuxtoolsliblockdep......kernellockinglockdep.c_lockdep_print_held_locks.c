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
struct task_struct {scalar_t__ state; scalar_t__ held_locks; int /*<<< orphan*/  comm; int /*<<< orphan*/  lockdep_depth; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ TASK_RUNNING ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  print_lock (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 
 int /*<<< orphan*/  task_pid_nr (struct task_struct*) ; 

__attribute__((used)) static void lockdep_print_held_locks(struct task_struct *p)
{
	int i, depth = READ_ONCE(p->lockdep_depth);

	if (!depth)
		printk("no locks held by %s/%d.\n", p->comm, task_pid_nr(p));
	else
		printk("%d lock%s held by %s/%d:\n", depth,
		       depth > 1 ? "s" : "", p->comm, task_pid_nr(p));
	/*
	 * It's not reliable to print a task's held locks if it's not sleeping
	 * and it's not the current task.
	 */
	if (p->state == TASK_RUNNING && p != current)
		return;
	for (i = 0; i < depth; i++) {
		printk(" #%d: ", i);
		print_lock(p->held_locks + i);
	}
}