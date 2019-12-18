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
 int /*<<< orphan*/  init_srcu_struct_fields (struct srcu_struct*,int) ; 
 int /*<<< orphan*/  rcu_seq_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave_rcu_node (struct srcu_struct*,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore_rcu_node (struct srcu_struct*,unsigned long) ; 

__attribute__((used)) static void check_init_srcu_struct(struct srcu_struct *ssp)
{
	unsigned long flags;

	/* The smp_load_acquire() pairs with the smp_store_release(). */
	if (!rcu_seq_state(smp_load_acquire(&ssp->srcu_gp_seq_needed))) /*^^^*/
		return; /* Already initialized. */
	spin_lock_irqsave_rcu_node(ssp, flags);
	if (!rcu_seq_state(ssp->srcu_gp_seq_needed)) {
		spin_unlock_irqrestore_rcu_node(ssp, flags);
		return;
	}
	init_srcu_struct_fields(ssp, true);
	spin_unlock_irqrestore_rcu_node(ssp, flags);
}