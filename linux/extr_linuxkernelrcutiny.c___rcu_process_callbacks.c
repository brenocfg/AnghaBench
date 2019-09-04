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
struct rcu_head {struct rcu_head* next; } ;
struct rcu_ctrlblk {struct rcu_head* rcucblist; struct rcu_head** donetail; struct rcu_head** curtail; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rcu_reclaim (char*,struct rcu_head*) ; 
 int /*<<< orphan*/  debug_rcu_head_unqueue (struct rcu_head*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  prefetch (struct rcu_head*) ; 

__attribute__((used)) static void __rcu_process_callbacks(struct rcu_ctrlblk *rcp)
{
	struct rcu_head *next, *list;
	unsigned long flags;

	/* Move the ready-to-invoke callbacks to a local list. */
	local_irq_save(flags);
	if (rcp->donetail == &rcp->rcucblist) {
		/* No callbacks ready, so just leave. */
		local_irq_restore(flags);
		return;
	}
	list = rcp->rcucblist;
	rcp->rcucblist = *rcp->donetail;
	*rcp->donetail = NULL;
	if (rcp->curtail == rcp->donetail)
		rcp->curtail = &rcp->rcucblist;
	rcp->donetail = &rcp->rcucblist;
	local_irq_restore(flags);

	/* Invoke the callbacks on the local list. */
	while (list) {
		next = list->next;
		prefetch(next);
		debug_rcu_head_unqueue(list);
		local_bh_disable();
		__rcu_reclaim("", list);
		local_bh_enable();
		list = next;
	}
}