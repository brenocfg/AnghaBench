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
struct rcu_head {struct rcu_head* next; int /*<<< orphan*/  func; } ;
struct rcu_ctrlblk {struct rcu_head** curtail; } ;
typedef  int /*<<< orphan*/  rcu_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  debug_rcu_head_queue (struct rcu_head*) ; 
 int /*<<< orphan*/  is_idle_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  resched_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __call_rcu(struct rcu_head *head,
		       rcu_callback_t func,
		       struct rcu_ctrlblk *rcp)
{
	unsigned long flags;

	debug_rcu_head_queue(head);
	head->func = func;
	head->next = NULL;

	local_irq_save(flags);
	*rcp->curtail = head;
	rcp->curtail = &head->next;
	local_irq_restore(flags);

	if (unlikely(is_idle_task(current))) {
		/* force scheduling for rcu_sched_qs() */
		resched_cpu(0);
	}
}