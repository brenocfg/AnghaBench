#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  mark; scalar_t__ data; } ;
struct rtable {int dummy; } ;
struct net {int dummy; } ;
struct iphdr {int /*<<< orphan*/  tos; } ;
struct flowi4 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP4_REPLY_MARK (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __build_flow_key (struct net*,struct flowi4*,int /*<<< orphan*/ *,struct iphdr const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtable* __ip_route_output_key (struct net*,struct flowi4*) ; 
 int /*<<< orphan*/  __ip_rt_update_pmtu (struct rtable*,struct flowi4*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 

void ipv4_update_pmtu(struct sk_buff *skb, struct net *net, u32 mtu,
		      int oif, u8 protocol)
{
	const struct iphdr *iph = (const struct iphdr *) skb->data;
	struct flowi4 fl4;
	struct rtable *rt;
	u32 mark = IP4_REPLY_MARK(net, skb->mark);

	__build_flow_key(net, &fl4, NULL, iph, oif,
			 RT_TOS(iph->tos), protocol, mark, 0);
	rt = __ip_route_output_key(net, &fl4);
	if (!IS_ERR(rt)) {
		__ip_rt_update_pmtu(rt, &fl4, mtu);
		ip_rt_put(rt);
	}
}