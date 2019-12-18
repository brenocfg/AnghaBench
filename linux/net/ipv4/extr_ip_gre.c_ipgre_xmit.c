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
struct sk_buff {int /*<<< orphan*/  protocol; scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_2__ stats; scalar_t__ needed_headroom; scalar_t__ header_ops; } ;
struct iphdr {int dummy; } ;
struct TYPE_3__ {int o_flags; struct iphdr iph; } ;
struct ip_tunnel {TYPE_1__ parms; scalar_t__ hlen; scalar_t__ collect_md; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int TUNNEL_CSUM ; 
 int /*<<< orphan*/  __gre_xmit (struct sk_buff*,struct net_device*,struct iphdr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gre_fb_xmit (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ gre_handle_offloads (struct sk_buff*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pskb_inet_may_pull (struct sk_buff*) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t ipgre_xmit(struct sk_buff *skb,
			      struct net_device *dev)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);
	const struct iphdr *tnl_params;

	if (!pskb_inet_may_pull(skb))
		goto free_skb;

	if (tunnel->collect_md) {
		gre_fb_xmit(skb, dev, skb->protocol);
		return NETDEV_TX_OK;
	}

	if (dev->header_ops) {
		/* Need space for new headers */
		if (skb_cow_head(skb, dev->needed_headroom -
				      (tunnel->hlen + sizeof(struct iphdr))))
			goto free_skb;

		tnl_params = (const struct iphdr *)skb->data;

		/* Pull skb since ip_tunnel_xmit() needs skb->data pointing
		 * to gre header.
		 */
		skb_pull(skb, tunnel->hlen + sizeof(struct iphdr));
		skb_reset_mac_header(skb);
	} else {
		if (skb_cow_head(skb, dev->needed_headroom))
			goto free_skb;

		tnl_params = &tunnel->parms.iph;
	}

	if (gre_handle_offloads(skb, !!(tunnel->parms.o_flags & TUNNEL_CSUM)))
		goto free_skb;

	__gre_xmit(skb, dev, tnl_params, skb->protocol);
	return NETDEV_TX_OK;

free_skb:
	kfree_skb(skb);
	dev->stats.tx_dropped++;
	return NETDEV_TX_OK;
}