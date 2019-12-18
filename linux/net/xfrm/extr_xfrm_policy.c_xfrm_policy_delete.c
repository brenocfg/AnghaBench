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
struct xfrm_policy {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  xfrm_policy_lock; } ;
struct net {TYPE_1__ xfrm; } ;

/* Variables and functions */
 int ENOENT ; 
 struct xfrm_policy* __xfrm_policy_unlink (struct xfrm_policy*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_policy_kill (struct xfrm_policy*) ; 
 struct net* xp_net (struct xfrm_policy*) ; 

int xfrm_policy_delete(struct xfrm_policy *pol, int dir)
{
	struct net *net = xp_net(pol);

	spin_lock_bh(&net->xfrm.xfrm_policy_lock);
	pol = __xfrm_policy_unlink(pol, dir);
	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
	if (pol) {
		xfrm_policy_kill(pol);
		return 0;
	}
	return -ENOENT;
}