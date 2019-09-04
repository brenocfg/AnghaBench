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
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int nh_flags; scalar_t__ nh_lwtstate; TYPE_1__* nh_dev; int /*<<< orphan*/  nh_gw; } ;
struct fib6_info {int fib6_flags; TYPE_2__ fib6_nh; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  RTA_GATEWAY ; 
 int /*<<< orphan*/  RTA_OIF ; 
 int RTF_GATEWAY ; 
 int RTNH_F_DEAD ; 
 int RTNH_F_LINKDOWN ; 
 int RTNH_F_OFFLOAD ; 
 unsigned int RTNH_F_ONLINK ; 
 scalar_t__ fib6_ignore_linkdown (struct fib6_info*) ; 
 scalar_t__ lwtunnel_fill_encap (struct sk_buff*,scalar_t__) ; 
 scalar_t__ nla_put_in6_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int rt6_nexthop_info(struct sk_buff *skb, struct fib6_info *rt,
			    unsigned int *flags, bool skip_oif)
{
	if (rt->fib6_nh.nh_flags & RTNH_F_DEAD)
		*flags |= RTNH_F_DEAD;

	if (rt->fib6_nh.nh_flags & RTNH_F_LINKDOWN) {
		*flags |= RTNH_F_LINKDOWN;

		rcu_read_lock();
		if (fib6_ignore_linkdown(rt))
			*flags |= RTNH_F_DEAD;
		rcu_read_unlock();
	}

	if (rt->fib6_flags & RTF_GATEWAY) {
		if (nla_put_in6_addr(skb, RTA_GATEWAY, &rt->fib6_nh.nh_gw) < 0)
			goto nla_put_failure;
	}

	*flags |= (rt->fib6_nh.nh_flags & RTNH_F_ONLINK);
	if (rt->fib6_nh.nh_flags & RTNH_F_OFFLOAD)
		*flags |= RTNH_F_OFFLOAD;

	/* not needed for multipath encoding b/c it has a rtnexthop struct */
	if (!skip_oif && rt->fib6_nh.nh_dev &&
	    nla_put_u32(skb, RTA_OIF, rt->fib6_nh.nh_dev->ifindex))
		goto nla_put_failure;

	if (rt->fib6_nh.nh_lwtstate &&
	    lwtunnel_fill_encap(skb, rt->fib6_nh.nh_lwtstate) < 0)
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}