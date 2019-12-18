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
struct srcu_struct {int /*<<< orphan*/  work; int /*<<< orphan*/  srcu_gp_seq; int /*<<< orphan*/  srcu_gp_seq_needed; } ;

/* Variables and functions */
 scalar_t__ ULONG_CMP_GE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rcu_gp_wq ; 
 int /*<<< orphan*/  rcu_seq_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq_rcu_node (struct srcu_struct*) ; 
 int /*<<< orphan*/  spin_unlock_irq_rcu_node (struct srcu_struct*) ; 
 int /*<<< orphan*/  srcu_gp_start (struct srcu_struct*) ; 

__attribute__((used)) static void srcu_reschedule(struct srcu_struct *ssp, unsigned long delay)
{
	bool pushgp = true;

	spin_lock_irq_rcu_node(ssp);
	if (ULONG_CMP_GE(ssp->srcu_gp_seq, ssp->srcu_gp_seq_needed)) {
		if (!WARN_ON_ONCE(rcu_seq_state(ssp->srcu_gp_seq))) {
			/* All requests fulfilled, time to go idle. */
			pushgp = false;
		}
	} else if (!rcu_seq_state(ssp->srcu_gp_seq)) {
		/* Outstanding request and no GP.  Start one. */
		srcu_gp_start(ssp);
	}
	spin_unlock_irq_rcu_node(ssp);

	if (pushgp)
		queue_delayed_work(rcu_gp_wq, &ssp->work, delay);
}