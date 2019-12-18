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
struct TYPE_2__ {scalar_t__ state; } ;
struct xfrm_state {int /*<<< orphan*/  gclist; TYPE_1__ km; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ XFRM_STATE_DEAD ; 
 int /*<<< orphan*/  ___xfrm_state_destroy (struct xfrm_state*) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  xfrm_state_gc_list ; 
 int /*<<< orphan*/  xfrm_state_gc_lock ; 
 int /*<<< orphan*/  xfrm_state_gc_work ; 

void __xfrm_state_destroy(struct xfrm_state *x, bool sync)
{
	WARN_ON(x->km.state != XFRM_STATE_DEAD);

	if (sync) {
		synchronize_rcu();
		___xfrm_state_destroy(x);
	} else {
		spin_lock_bh(&xfrm_state_gc_lock);
		hlist_add_head(&x->gclist, &xfrm_state_gc_list);
		spin_unlock_bh(&xfrm_state_gc_lock);
		schedule_work(&xfrm_state_gc_work);
	}
}