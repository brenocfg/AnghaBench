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
struct TYPE_2__ {int /*<<< orphan*/  entry; } ;
struct srcu_struct {TYPE_1__ srcu_work; int /*<<< orphan*/  srcu_gp_running; struct rcu_head** srcu_cb_tail; } ;
struct rcu_head {struct rcu_head* next; int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  rcu_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  schedule_work (TYPE_1__*) ; 
 int /*<<< orphan*/  srcu_boot_list ; 
 int /*<<< orphan*/  srcu_init_done ; 

void call_srcu(struct srcu_struct *ssp, struct rcu_head *rhp,
	       rcu_callback_t func)
{
	unsigned long flags;

	rhp->func = func;
	rhp->next = NULL;
	local_irq_save(flags);
	*ssp->srcu_cb_tail = rhp;
	ssp->srcu_cb_tail = &rhp->next;
	local_irq_restore(flags);
	if (!READ_ONCE(ssp->srcu_gp_running)) {
		if (likely(srcu_init_done))
			schedule_work(&ssp->srcu_work);
		else if (list_empty(&ssp->srcu_work.entry))
			list_add(&ssp->srcu_work.entry, &srcu_boot_list);
	}
}