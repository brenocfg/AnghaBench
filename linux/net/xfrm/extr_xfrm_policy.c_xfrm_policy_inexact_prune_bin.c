#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  net; } ;
struct xfrm_pol_inexact_bin {TYPE_1__ k; } ;
struct TYPE_4__ {int /*<<< orphan*/  xfrm_policy_lock; } ;
struct net {TYPE_2__ xfrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xfrm_policy_inexact_prune_bin (struct xfrm_pol_inexact_bin*,int) ; 
 struct net* read_pnet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xfrm_policy_inexact_prune_bin(struct xfrm_pol_inexact_bin *b)
{
	struct net *net = read_pnet(&b->k.net);

	spin_lock_bh(&net->xfrm.xfrm_policy_lock);
	__xfrm_policy_inexact_prune_bin(b, false);
	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
}