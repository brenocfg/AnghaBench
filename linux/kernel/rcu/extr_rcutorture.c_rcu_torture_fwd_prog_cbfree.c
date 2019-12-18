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
struct rcu_fwd_cb {struct rcu_fwd_cb* rfc_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rcu_fwd_cb*) ; 
 struct rcu_fwd_cb* rcu_fwd_cb_head ; 
 struct rcu_fwd_cb** rcu_fwd_cb_tail ; 
 int /*<<< orphan*/  rcu_fwd_lock ; 
 int /*<<< orphan*/  rcu_torture_fwd_prog_cond_resched (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned long rcu_torture_fwd_prog_cbfree(void)
{
	unsigned long flags;
	unsigned long freed = 0;
	struct rcu_fwd_cb *rfcp;

	for (;;) {
		spin_lock_irqsave(&rcu_fwd_lock, flags);
		rfcp = rcu_fwd_cb_head;
		if (!rfcp) {
			spin_unlock_irqrestore(&rcu_fwd_lock, flags);
			break;
		}
		rcu_fwd_cb_head = rfcp->rfc_next;
		if (!rcu_fwd_cb_head)
			rcu_fwd_cb_tail = &rcu_fwd_cb_head;
		spin_unlock_irqrestore(&rcu_fwd_lock, flags);
		kfree(rfcp);
		freed++;
		rcu_torture_fwd_prog_cond_resched(freed);
	}
	return freed;
}