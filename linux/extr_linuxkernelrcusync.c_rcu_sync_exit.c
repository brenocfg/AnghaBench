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
struct rcu_sync {scalar_t__ cb_state; size_t gp_type; int /*<<< orphan*/  rss_lock; int /*<<< orphan*/  cb_head; int /*<<< orphan*/  gp_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* call ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ CB_IDLE ; 
 scalar_t__ CB_PENDING ; 
 scalar_t__ CB_REPLAY ; 
 TYPE_1__* gp_ops ; 
 int /*<<< orphan*/  rcu_sync_func ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void rcu_sync_exit(struct rcu_sync *rsp)
{
	spin_lock_irq(&rsp->rss_lock);
	if (!--rsp->gp_count) {
		if (rsp->cb_state == CB_IDLE) {
			rsp->cb_state = CB_PENDING;
			gp_ops[rsp->gp_type].call(&rsp->cb_head, rcu_sync_func);
		} else if (rsp->cb_state == CB_PENDING) {
			rsp->cb_state = CB_REPLAY;
		}
	}
	spin_unlock_irq(&rsp->rss_lock);
}