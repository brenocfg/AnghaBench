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
struct TYPE_3__ {int /*<<< orphan*/  add_time; } ;
struct xfrm_policy {scalar_t__ type; int /*<<< orphan*/  index; TYPE_1__ curlft; } ;
struct sock {int /*<<< orphan*/ * sk_policy; } ;
struct TYPE_4__ {int /*<<< orphan*/  xfrm_policy_lock; } ;
struct net {TYPE_2__ xfrm; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ XFRM_POLICY_MAX ; 
 scalar_t__ XFRM_POLICY_TYPE_MAIN ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct xfrm_policy*) ; 
 struct xfrm_policy* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_gen_index (struct net*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_policy_kill (struct xfrm_policy*) ; 
 int /*<<< orphan*/  xfrm_policy_requeue (struct xfrm_policy*,struct xfrm_policy*) ; 
 int /*<<< orphan*/  xfrm_sk_policy_link (struct xfrm_policy*,int) ; 
 int /*<<< orphan*/  xfrm_sk_policy_unlink (struct xfrm_policy*,int) ; 

int xfrm_sk_policy_insert(struct sock *sk, int dir, struct xfrm_policy *pol)
{
	struct net *net = sock_net(sk);
	struct xfrm_policy *old_pol;

#ifdef CONFIG_XFRM_SUB_POLICY
	if (pol && pol->type != XFRM_POLICY_TYPE_MAIN)
		return -EINVAL;
#endif

	spin_lock_bh(&net->xfrm.xfrm_policy_lock);
	old_pol = rcu_dereference_protected(sk->sk_policy[dir],
				lockdep_is_held(&net->xfrm.xfrm_policy_lock));
	if (pol) {
		pol->curlft.add_time = ktime_get_real_seconds();
		pol->index = xfrm_gen_index(net, XFRM_POLICY_MAX+dir, 0);
		xfrm_sk_policy_link(pol, dir);
	}
	rcu_assign_pointer(sk->sk_policy[dir], pol);
	if (old_pol) {
		if (pol)
			xfrm_policy_requeue(old_pol, pol);

		/* Unlinking succeeds always. This is the only function
		 * allowed to delete or replace socket policy.
		 */
		xfrm_sk_policy_unlink(old_pol, dir);
	}
	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);

	if (old_pol) {
		xfrm_policy_kill(old_pol);
	}
	return 0;
}