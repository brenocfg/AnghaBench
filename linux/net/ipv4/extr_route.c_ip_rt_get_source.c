#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  mark; TYPE_1__* dev; } ;
struct TYPE_6__ {TYPE_3__* dev; } ;
struct rtable {TYPE_2__ dst; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  tos; int /*<<< orphan*/  saddr; } ;
struct flowi4 {int /*<<< orphan*/  flowi4_mark; int /*<<< orphan*/  flowi4_iif; int /*<<< orphan*/  flowi4_oif; int /*<<< orphan*/  flowi4_tos; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct fib_result {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_7__ {int /*<<< orphan*/  ifindex; } ;
struct TYPE_5__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (TYPE_3__*) ; 
 scalar_t__ fib_lookup (int /*<<< orphan*/ ,struct flowi4*,struct fib_result*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib_result_prefsrc (int /*<<< orphan*/ ,struct fib_result*) ; 
 int /*<<< orphan*/  inet_select_addr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ rt_is_output_route (struct rtable*) ; 
 int /*<<< orphan*/  rt_nexthop (struct rtable*,int /*<<< orphan*/ ) ; 

void ip_rt_get_source(u8 *addr, struct sk_buff *skb, struct rtable *rt)
{
	__be32 src;

	if (rt_is_output_route(rt))
		src = ip_hdr(skb)->saddr;
	else {
		struct fib_result res;
		struct iphdr *iph = ip_hdr(skb);
		struct flowi4 fl4 = {
			.daddr = iph->daddr,
			.saddr = iph->saddr,
			.flowi4_tos = RT_TOS(iph->tos),
			.flowi4_oif = rt->dst.dev->ifindex,
			.flowi4_iif = skb->dev->ifindex,
			.flowi4_mark = skb->mark,
		};

		rcu_read_lock();
		if (fib_lookup(dev_net(rt->dst.dev), &fl4, &res, 0) == 0)
			src = fib_result_prefsrc(dev_net(rt->dst.dev), &res);
		else
			src = inet_select_addr(rt->dst.dev,
					       rt_nexthop(rt, iph->daddr),
					       RT_SCOPE_UNIVERSE);
		rcu_read_unlock();
	}
	memcpy(addr, &src, 4);
}