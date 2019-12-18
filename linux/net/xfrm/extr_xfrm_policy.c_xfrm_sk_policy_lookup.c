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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int m; int v; } ;
struct xfrm_policy {scalar_t__ if_id; int /*<<< orphan*/  security; TYPE_1__ mark; int /*<<< orphan*/  selector; int /*<<< orphan*/  family; } ;
struct sock {int sk_mark; int /*<<< orphan*/ * sk_policy; } ;
struct flowi {int /*<<< orphan*/  flowi_secid; } ;

/* Variables and functions */
 struct xfrm_policy* ERR_PTR (int) ; 
 int ESRCH ; 
 struct xfrm_policy* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int security_xfrm_policy_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfrm_pol_hold_rcu (struct xfrm_policy*) ; 
 int xfrm_selector_match (int /*<<< orphan*/ *,struct flowi const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xfrm_policy *xfrm_sk_policy_lookup(const struct sock *sk, int dir,
						 const struct flowi *fl,
						 u16 family, u32 if_id)
{
	struct xfrm_policy *pol;

	rcu_read_lock();
 again:
	pol = rcu_dereference(sk->sk_policy[dir]);
	if (pol != NULL) {
		bool match;
		int err = 0;

		if (pol->family != family) {
			pol = NULL;
			goto out;
		}

		match = xfrm_selector_match(&pol->selector, fl, family);
		if (match) {
			if ((sk->sk_mark & pol->mark.m) != pol->mark.v ||
			    pol->if_id != if_id) {
				pol = NULL;
				goto out;
			}
			err = security_xfrm_policy_lookup(pol->security,
						      fl->flowi_secid,
						      dir);
			if (!err) {
				if (!xfrm_pol_hold_rcu(pol))
					goto again;
			} else if (err == -ESRCH) {
				pol = NULL;
			} else {
				pol = ERR_PTR(err);
			}
		} else
			pol = NULL;
	}
out:
	rcu_read_unlock();
	return pol;
}