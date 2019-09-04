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
struct srcu_struct {int /*<<< orphan*/  srcu_work; int /*<<< orphan*/  srcu_gp_running; struct rcu_head** srcu_cb_tail; } ;
struct rcu_head {struct rcu_head* next; int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  rcu_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void call_srcu(struct srcu_struct *sp, struct rcu_head *rhp,
	       rcu_callback_t func)
{
	unsigned long flags;

	rhp->func = func;
	rhp->next = NULL;
	local_irq_save(flags);
	*sp->srcu_cb_tail = rhp;
	sp->srcu_cb_tail = &rhp->next;
	local_irq_restore(flags);
	if (!READ_ONCE(sp->srcu_gp_running))
		schedule_work(&sp->srcu_work);
}