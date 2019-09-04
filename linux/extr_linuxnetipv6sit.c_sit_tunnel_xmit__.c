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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_2__ stats; } ;
struct iphdr {int dummy; } ;
struct TYPE_3__ {struct iphdr iph; } ;
struct ip_tunnel {TYPE_1__ parms; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  SKB_GSO_IPXIP4 ; 
 int /*<<< orphan*/  ip_tunnel_xmit (struct sk_buff*,struct net_device*,struct iphdr const*,int /*<<< orphan*/ ) ; 
 scalar_t__ iptunnel_handle_offloads (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_set_inner_ipproto (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t sit_tunnel_xmit__(struct sk_buff *skb,
				     struct net_device *dev, u8 ipproto)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);
	const struct iphdr  *tiph = &tunnel->parms.iph;

	if (iptunnel_handle_offloads(skb, SKB_GSO_IPXIP4))
		goto tx_error;

	skb_set_inner_ipproto(skb, ipproto);

	ip_tunnel_xmit(skb, dev, tiph, ipproto);
	return NETDEV_TX_OK;
tx_error:
	kfree_skb(skb);
	dev->stats.tx_errors++;
	return NETDEV_TX_OK;
}