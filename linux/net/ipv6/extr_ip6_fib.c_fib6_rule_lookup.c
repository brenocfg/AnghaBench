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
struct sk_buff {int dummy; } ;
struct dst_entry {int /*<<< orphan*/  error; } ;
struct rt6_info {struct dst_entry dst; } ;
struct TYPE_2__ {struct rt6_info* ip6_null_entry; int /*<<< orphan*/  fib6_main_tbl; } ;
struct net {TYPE_1__ ipv6; } ;
struct flowi6 {int dummy; } ;
typedef  struct rt6_info* (* pol_lookup_t ) (struct net*,int /*<<< orphan*/ ,struct flowi6*,struct sk_buff const*,int) ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int RT6_LOOKUP_F_DST_NOREF ; 
 int /*<<< orphan*/  dst_hold (struct dst_entry*) ; 
 int /*<<< orphan*/  ip6_rt_put_flags (struct rt6_info*,int) ; 

struct dst_entry *fib6_rule_lookup(struct net *net, struct flowi6 *fl6,
				   const struct sk_buff *skb,
				   int flags, pol_lookup_t lookup)
{
	struct rt6_info *rt;

	rt = lookup(net, net->ipv6.fib6_main_tbl, fl6, skb, flags);
	if (rt->dst.error == -EAGAIN) {
		ip6_rt_put_flags(rt, flags);
		rt = net->ipv6.ip6_null_entry;
		if (!(flags & RT6_LOOKUP_F_DST_NOREF))
			dst_hold(&rt->dst);
	}

	return &rt->dst;
}