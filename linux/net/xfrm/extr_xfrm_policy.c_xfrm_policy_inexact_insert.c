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
typedef  size_t u8 ;
struct xfrm_policy {int dummy; } ;
struct xfrm_pol_inexact_bin {int dummy; } ;
struct TYPE_2__ {struct hlist_head* policy_inexact; int /*<<< orphan*/  xfrm_policy_lock; } ;
struct net {TYPE_1__ xfrm; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct xfrm_policy* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __xfrm_policy_inexact_prune_bin (struct xfrm_pol_inexact_bin*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct xfrm_pol_inexact_bin* xfrm_policy_inexact_alloc_bin (struct xfrm_policy*,size_t) ; 
 struct hlist_head* xfrm_policy_inexact_alloc_chain (struct xfrm_pol_inexact_bin*,struct xfrm_policy*,size_t) ; 
 int /*<<< orphan*/  xfrm_policy_insert_inexact_list (struct hlist_head*,struct xfrm_policy*) ; 
 struct xfrm_policy* xfrm_policy_insert_list (struct hlist_head*,struct xfrm_policy*,int) ; 
 struct net* xp_net (struct xfrm_policy*) ; 

__attribute__((used)) static struct xfrm_policy *
xfrm_policy_inexact_insert(struct xfrm_policy *policy, u8 dir, int excl)
{
	struct xfrm_pol_inexact_bin *bin;
	struct xfrm_policy *delpol;
	struct hlist_head *chain;
	struct net *net;

	bin = xfrm_policy_inexact_alloc_bin(policy, dir);
	if (!bin)
		return ERR_PTR(-ENOMEM);

	net = xp_net(policy);
	lockdep_assert_held(&net->xfrm.xfrm_policy_lock);

	chain = xfrm_policy_inexact_alloc_chain(bin, policy, dir);
	if (!chain) {
		__xfrm_policy_inexact_prune_bin(bin, false);
		return ERR_PTR(-ENOMEM);
	}

	delpol = xfrm_policy_insert_list(chain, policy, excl);
	if (delpol && excl) {
		__xfrm_policy_inexact_prune_bin(bin, false);
		return ERR_PTR(-EEXIST);
	}

	chain = &net->xfrm.policy_inexact[dir];
	xfrm_policy_insert_inexact_list(chain, policy);

	if (delpol)
		__xfrm_policy_inexact_prune_bin(bin, false);

	return delpol;
}