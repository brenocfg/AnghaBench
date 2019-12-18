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
struct xfrm_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  xfrm_state_lock; } ;
struct net {TYPE_1__ xfrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xfrm_state_bump_genids (struct xfrm_state*) ; 
 int /*<<< orphan*/  __xfrm_state_insert (struct xfrm_state*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct net* xs_net (struct xfrm_state*) ; 

void xfrm_state_insert(struct xfrm_state *x)
{
	struct net *net = xs_net(x);

	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	__xfrm_state_bump_genids(x);
	__xfrm_state_insert(x);
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);
}