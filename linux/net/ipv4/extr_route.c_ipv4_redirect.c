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
struct sk_buff {scalar_t__ data; } ;
struct rtable {int dummy; } ;
struct net {int dummy; } ;
struct iphdr {int /*<<< orphan*/  tos; } ;
struct flowi4 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __build_flow_key (struct net*,struct flowi4*,int /*<<< orphan*/ *,struct iphdr const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ip_do_redirect (struct rtable*,struct sk_buff*,struct flowi4*,int) ; 
 struct rtable* __ip_route_output_key (struct net*,struct flowi4*) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 

void ipv4_redirect(struct sk_buff *skb, struct net *net,
		   int oif, u8 protocol)
{
	const struct iphdr *iph = (const struct iphdr *) skb->data;
	struct flowi4 fl4;
	struct rtable *rt;

	__build_flow_key(net, &fl4, NULL, iph, oif,
			 RT_TOS(iph->tos), protocol, 0, 0);
	rt = __ip_route_output_key(net, &fl4);
	if (!IS_ERR(rt)) {
		__ip_do_redirect(rt, skb, &fl4, false);
		ip_rt_put(rt);
	}
}