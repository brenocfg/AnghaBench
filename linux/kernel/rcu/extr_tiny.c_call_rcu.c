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
struct rcu_head {struct rcu_head* next; int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  rcu_callback_t ;
struct TYPE_2__ {struct rcu_head** curtail; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  debug_rcu_head_queue (struct rcu_head*) ; 
 int /*<<< orphan*/  is_idle_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_1__ rcu_ctrlblk ; 
 int /*<<< orphan*/  resched_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void call_rcu(struct rcu_head *head, rcu_callback_t func)
{
	unsigned long flags;

	debug_rcu_head_queue(head);
	head->func = func;
	head->next = NULL;

	local_irq_save(flags);
	*rcu_ctrlblk.curtail = head;
	rcu_ctrlblk.curtail = &head->next;
	local_irq_restore(flags);

	if (unlikely(is_idle_task(current))) {
		/* force scheduling for rcu_qs() */
		resched_cpu(0);
	}
}