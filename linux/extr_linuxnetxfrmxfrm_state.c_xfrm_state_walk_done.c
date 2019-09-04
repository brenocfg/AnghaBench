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
struct xfrm_state_walk {int /*<<< orphan*/  all; int /*<<< orphan*/  filter; } ;
struct TYPE_2__ {int /*<<< orphan*/  xfrm_state_lock; } ;
struct net {TYPE_1__ xfrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void xfrm_state_walk_done(struct xfrm_state_walk *walk, struct net *net)
{
	kfree(walk->filter);

	if (list_empty(&walk->all))
		return;

	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	list_del(&walk->all);
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);
}