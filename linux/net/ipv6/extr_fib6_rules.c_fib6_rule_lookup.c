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
struct dst_entry {int /*<<< orphan*/  error; } ;
struct rt6_info {struct dst_entry dst; } ;
struct TYPE_4__ {struct rt6_info* ip6_null_entry; int /*<<< orphan*/  fib6_main_tbl; int /*<<< orphan*/  fib6_local_tbl; int /*<<< orphan*/  fib6_rules_ops; scalar_t__ fib6_has_custom_rules; } ;
struct net {TYPE_2__ ipv6; } ;
struct flowi6 {int dummy; } ;
struct fib_lookup_arg {int /*<<< orphan*/  flags; struct fib6_result* result; struct sk_buff const* lookup_data; struct rt6_info* (* lookup_ptr ) (struct net*,int /*<<< orphan*/ ,struct flowi6*,struct sk_buff const*,int) ;} ;
struct fib6_result {TYPE_1__* rt6; } ;
typedef  struct rt6_info* (* pol_lookup_t ) (struct net*,int /*<<< orphan*/ ,struct flowi6*,struct sk_buff const*,int) ;
struct TYPE_3__ {struct dst_entry dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  FIB_LOOKUP_NOREF ; 
 int RT6_LOOKUP_F_DST_NOREF ; 
 int /*<<< orphan*/  dst_hold (struct dst_entry*) ; 
 int /*<<< orphan*/  fib_rules_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct fib_lookup_arg*) ; 
 int /*<<< orphan*/  flowi6_to_flowi (struct flowi6*) ; 
 int /*<<< orphan*/  ip6_rt_put_flags (struct rt6_info*,int) ; 
 int /*<<< orphan*/  l3mdev_update_flow (struct net*,int /*<<< orphan*/ ) ; 

struct dst_entry *fib6_rule_lookup(struct net *net, struct flowi6 *fl6,
				   const struct sk_buff *skb,
				   int flags, pol_lookup_t lookup)
{
	if (net->ipv6.fib6_has_custom_rules) {
		struct fib6_result res = {};
		struct fib_lookup_arg arg = {
			.lookup_ptr = lookup,
			.lookup_data = skb,
			.result = &res,
			.flags = FIB_LOOKUP_NOREF,
		};

		/* update flow if oif or iif point to device enslaved to l3mdev */
		l3mdev_update_flow(net, flowi6_to_flowi(fl6));

		fib_rules_lookup(net->ipv6.fib6_rules_ops,
				 flowi6_to_flowi(fl6), flags, &arg);

		if (res.rt6)
			return &res.rt6->dst;
	} else {
		struct rt6_info *rt;

		rt = lookup(net, net->ipv6.fib6_local_tbl, fl6, skb, flags);
		if (rt != net->ipv6.ip6_null_entry && rt->dst.error != -EAGAIN)
			return &rt->dst;
		ip6_rt_put_flags(rt, flags);
		rt = lookup(net, net->ipv6.fib6_main_tbl, fl6, skb, flags);
		if (rt->dst.error != -EAGAIN)
			return &rt->dst;
		ip6_rt_put_flags(rt, flags);
	}

	if (!(flags & RT6_LOOKUP_F_DST_NOREF))
		dst_hold(&net->ipv6.ip6_null_entry->dst);
	return &net->ipv6.ip6_null_entry->dst;
}