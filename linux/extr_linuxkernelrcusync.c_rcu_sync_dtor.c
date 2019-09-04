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
struct rcu_sync {int gp_count; int cb_state; size_t gp_type; int /*<<< orphan*/  rss_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* wait ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CB_IDLE ; 
 int CB_PENDING ; 
 int CB_REPLAY ; 
 TYPE_1__* gp_ops ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 

void rcu_sync_dtor(struct rcu_sync *rsp)
{
	int cb_state;

	BUG_ON(rsp->gp_count);

	spin_lock_irq(&rsp->rss_lock);
	if (rsp->cb_state == CB_REPLAY)
		rsp->cb_state = CB_PENDING;
	cb_state = rsp->cb_state;
	spin_unlock_irq(&rsp->rss_lock);

	if (cb_state != CB_IDLE) {
		gp_ops[rsp->gp_type].wait();
		BUG_ON(rsp->cb_state != CB_IDLE);
	}
}