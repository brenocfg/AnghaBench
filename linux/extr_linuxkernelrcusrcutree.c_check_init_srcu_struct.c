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
struct srcu_struct {int /*<<< orphan*/  srcu_gp_seq_needed; } ;

/* Variables and functions */
 scalar_t__ RCU_SCHEDULER_INIT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  init_srcu_struct_fields (struct srcu_struct*,int) ; 
 scalar_t__ rcu_scheduler_active ; 
 int /*<<< orphan*/  rcu_seq_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave_rcu_node (struct srcu_struct*,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore_rcu_node (struct srcu_struct*,unsigned long) ; 

__attribute__((used)) static void check_init_srcu_struct(struct srcu_struct *sp)
{
	unsigned long flags;

	WARN_ON_ONCE(rcu_scheduler_active == RCU_SCHEDULER_INIT);
	/* The smp_load_acquire() pairs with the smp_store_release(). */
	if (!rcu_seq_state(smp_load_acquire(&sp->srcu_gp_seq_needed))) /*^^^*/
		return; /* Already initialized. */
	spin_lock_irqsave_rcu_node(sp, flags);
	if (!rcu_seq_state(sp->srcu_gp_seq_needed)) {
		spin_unlock_irqrestore_rcu_node(sp, flags);
		return;
	}
	init_srcu_struct_fields(sp, true);
	spin_unlock_irqrestore_rcu_node(sp, flags);
}