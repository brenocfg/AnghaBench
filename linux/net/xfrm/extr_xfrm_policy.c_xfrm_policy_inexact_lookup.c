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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct xfrm_pol_inexact_bin {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  xfrm_policy_lock; } ;
struct net {TYPE_1__ xfrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct xfrm_pol_inexact_bin* xfrm_policy_inexact_lookup_rcu (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xfrm_pol_inexact_bin *
xfrm_policy_inexact_lookup(struct net *net, u8 type, u16 family,
			   u8 dir, u32 if_id)
{
	struct xfrm_pol_inexact_bin *bin;

	lockdep_assert_held(&net->xfrm.xfrm_policy_lock);

	rcu_read_lock();
	bin = xfrm_policy_inexact_lookup_rcu(net, type, family, dir, if_id);
	rcu_read_unlock();

	return bin;
}