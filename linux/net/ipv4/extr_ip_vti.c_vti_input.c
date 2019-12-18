#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_2__* dev; } ;
struct net {int dummy; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct ip_tunnel_net {int dummy; } ;
struct ip_tunnel {TYPE_2__* dev; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {struct ip_tunnel* ip4; } ;
struct TYPE_6__ {TYPE_1__ tunnel; } ;
struct TYPE_5__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TUNNEL_NO_KEY ; 
 int /*<<< orphan*/  XFRM_POLICY_IN ; 
 TYPE_3__* XFRM_TUNNEL_SKB_CB (struct sk_buff*) ; 
 struct net* dev_net (TYPE_2__*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 struct ip_tunnel* ip_tunnel_lookup (struct ip_tunnel_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct ip_tunnel_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vti_net_id ; 
 int /*<<< orphan*/  xfrm4_policy_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int xfrm_input (struct sk_buff*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vti_input(struct sk_buff *skb, int nexthdr, __be32 spi,
		     int encap_type, bool update_skb_dev)
{
	struct ip_tunnel *tunnel;
	const struct iphdr *iph = ip_hdr(skb);
	struct net *net = dev_net(skb->dev);
	struct ip_tunnel_net *itn = net_generic(net, vti_net_id);

	tunnel = ip_tunnel_lookup(itn, skb->dev->ifindex, TUNNEL_NO_KEY,
				  iph->saddr, iph->daddr, 0);
	if (tunnel) {
		if (!xfrm4_policy_check(NULL, XFRM_POLICY_IN, skb))
			goto drop;

		XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip4 = tunnel;

		if (update_skb_dev)
			skb->dev = tunnel->dev;

		return xfrm_input(skb, nexthdr, spi, encap_type);
	}

	return -EINVAL;
drop:
	kfree_skb(skb);
	return 0;
}