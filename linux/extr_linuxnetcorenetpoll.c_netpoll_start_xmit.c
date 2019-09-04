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
struct sk_buff {int /*<<< orphan*/  vlan_proto; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 int NETDEV_TX_OK ; 
 struct sk_buff* __vlan_hwaccel_push_inside (struct sk_buff*) ; 
 int netdev_start_xmit (struct sk_buff*,struct net_device*,struct netdev_queue*,int) ; 
 int /*<<< orphan*/  netif_skb_features (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlan_hw_offload_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netpoll_start_xmit(struct sk_buff *skb, struct net_device *dev,
			      struct netdev_queue *txq)
{
	int status = NETDEV_TX_OK;
	netdev_features_t features;

	features = netif_skb_features(skb);

	if (skb_vlan_tag_present(skb) &&
	    !vlan_hw_offload_capable(features, skb->vlan_proto)) {
		skb = __vlan_hwaccel_push_inside(skb);
		if (unlikely(!skb)) {
			/* This is actually a packet drop, but we
			 * don't want the code that calls this
			 * function to try and operate on a NULL skb.
			 */
			goto out;
		}
	}

	status = netdev_start_xmit(skb, dev, txq, false);

out:
	return status;
}