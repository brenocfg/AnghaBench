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
struct sk_buff {int /*<<< orphan*/  sk; int /*<<< orphan*/  mark; struct net_device* dev; } ;
struct rtable {scalar_t__ rt_type; int /*<<< orphan*/  dst; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  ifindex; } ;
struct net {int dummy; } ;
struct iphdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  tos; } ;
struct flowi4 {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  flowi4_mark; int /*<<< orphan*/  flowi4_flags; int /*<<< orphan*/  flowi4_tos; int /*<<< orphan*/  flowi4_oif; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOWI_FLAG_ANYSRC ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int NET_XMIT_DROP ; 
 int NET_XMIT_SUCCESS ; 
 scalar_t__ RTN_LOCAL ; 
 scalar_t__ RTN_UNICAST ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 struct net* dev_net (struct net_device*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ip_local_out (struct net*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct rtable* ip_route_output_flow (struct net*,struct flowi4*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_xmit_eval (int) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipvlan_process_v4_outbound(struct sk_buff *skb)
{
	const struct iphdr *ip4h = ip_hdr(skb);
	struct net_device *dev = skb->dev;
	struct net *net = dev_net(dev);
	struct rtable *rt;
	int err, ret = NET_XMIT_DROP;
	struct flowi4 fl4 = {
		.flowi4_oif = dev->ifindex,
		.flowi4_tos = RT_TOS(ip4h->tos),
		.flowi4_flags = FLOWI_FLAG_ANYSRC,
		.flowi4_mark = skb->mark,
		.daddr = ip4h->daddr,
		.saddr = ip4h->saddr,
	};

	rt = ip_route_output_flow(net, &fl4, NULL);
	if (IS_ERR(rt))
		goto err;

	if (rt->rt_type != RTN_UNICAST && rt->rt_type != RTN_LOCAL) {
		ip_rt_put(rt);
		goto err;
	}
	skb_dst_set(skb, &rt->dst);
	err = ip_local_out(net, skb->sk, skb);
	if (unlikely(net_xmit_eval(err)))
		dev->stats.tx_errors++;
	else
		ret = NET_XMIT_SUCCESS;
	goto out;
err:
	dev->stats.tx_errors++;
	kfree_skb(skb);
out:
	return ret;
}