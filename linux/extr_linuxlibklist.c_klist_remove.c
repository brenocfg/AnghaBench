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
struct klist_waiter {scalar_t__ woken; int /*<<< orphan*/  list; int /*<<< orphan*/  process; struct klist_node* node; } ;
struct klist_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  klist_del (struct klist_node*) ; 
 int /*<<< orphan*/  klist_remove_lock ; 
 int /*<<< orphan*/  klist_remove_waiters ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void klist_remove(struct klist_node *n)
{
	struct klist_waiter waiter;

	waiter.node = n;
	waiter.process = current;
	waiter.woken = 0;
	spin_lock(&klist_remove_lock);
	list_add(&waiter.list, &klist_remove_waiters);
	spin_unlock(&klist_remove_lock);

	klist_del(n);

	for (;;) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		if (waiter.woken)
			break;
		schedule();
	}
	__set_current_state(TASK_RUNNING);
}