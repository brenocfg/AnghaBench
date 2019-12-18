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
struct task_struct {struct mutex_waiter* blocked_on; } ;
struct mutex_waiter {struct task_struct* task; int /*<<< orphan*/  list; } ;
struct mutex {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOCKS_WARN_ON (int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 

void mutex_remove_waiter(struct mutex *lock, struct mutex_waiter *waiter,
			 struct task_struct *task)
{
	DEBUG_LOCKS_WARN_ON(list_empty(&waiter->list));
	DEBUG_LOCKS_WARN_ON(waiter->task != task);
	DEBUG_LOCKS_WARN_ON(task->blocked_on != waiter);
	task->blocked_on = NULL;

	list_del_init(&waiter->list);
	waiter->task = NULL;
}