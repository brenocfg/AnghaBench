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
struct TYPE_3__ {scalar_t__ use_time; int /*<<< orphan*/  add_time; } ;
struct xfrm_policy {int /*<<< orphan*/  timer; TYPE_1__ curlft; int /*<<< orphan*/  index; int /*<<< orphan*/  byidx; int /*<<< orphan*/  family; int /*<<< orphan*/  selector; } ;
struct TYPE_4__ {int /*<<< orphan*/  policy_hash_work; int /*<<< orphan*/  xfrm_policy_lock; scalar_t__ policy_byidx; } ;
struct net {TYPE_2__ xfrm; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ HZ ; 
 scalar_t__ IS_ERR (struct xfrm_policy*) ; 
 int PTR_ERR (struct xfrm_policy*) ; 
 int /*<<< orphan*/  __xfrm_policy_link (struct xfrm_policy*,int) ; 
 int /*<<< orphan*/  __xfrm_policy_unlink (struct xfrm_policy*,int) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ idx_hash (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct hlist_head* policy_hash_bysel (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt_genid_bump_ipv4 (struct net*) ; 
 int /*<<< orphan*/  rt_genid_bump_ipv6 (struct net*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ xfrm_bydst_should_resize (struct net*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_gen_index (struct net*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_pol_hold (struct xfrm_policy*) ; 
 struct xfrm_policy* xfrm_policy_inexact_insert (struct xfrm_policy*,int,int) ; 
 struct xfrm_policy* xfrm_policy_insert_list (struct hlist_head*,struct xfrm_policy*,int) ; 
 int /*<<< orphan*/  xfrm_policy_kill (struct xfrm_policy*) ; 
 int /*<<< orphan*/  xfrm_policy_requeue (struct xfrm_policy*,struct xfrm_policy*) ; 
 struct net* xp_net (struct xfrm_policy*) ; 

int xfrm_policy_insert(int dir, struct xfrm_policy *policy, int excl)
{
	struct net *net = xp_net(policy);
	struct xfrm_policy *delpol;
	struct hlist_head *chain;

	spin_lock_bh(&net->xfrm.xfrm_policy_lock);
	chain = policy_hash_bysel(net, &policy->selector, policy->family, dir);
	if (chain)
		delpol = xfrm_policy_insert_list(chain, policy, excl);
	else
		delpol = xfrm_policy_inexact_insert(policy, dir, excl);

	if (IS_ERR(delpol)) {
		spin_unlock_bh(&net->xfrm.xfrm_policy_lock);
		return PTR_ERR(delpol);
	}

	__xfrm_policy_link(policy, dir);

	/* After previous checking, family can either be AF_INET or AF_INET6 */
	if (policy->family == AF_INET)
		rt_genid_bump_ipv4(net);
	else
		rt_genid_bump_ipv6(net);

	if (delpol) {
		xfrm_policy_requeue(delpol, policy);
		__xfrm_policy_unlink(delpol, dir);
	}
	policy->index = delpol ? delpol->index : xfrm_gen_index(net, dir, policy->index);
	hlist_add_head(&policy->byidx, net->xfrm.policy_byidx+idx_hash(net, policy->index));
	policy->curlft.add_time = ktime_get_real_seconds();
	policy->curlft.use_time = 0;
	if (!mod_timer(&policy->timer, jiffies + HZ))
		xfrm_pol_hold(policy);
	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);

	if (delpol)
		xfrm_policy_kill(delpol);
	else if (xfrm_bydst_should_resize(net, dir, NULL))
		schedule_work(&net->xfrm.policy_hash_work);

	return 0;
}