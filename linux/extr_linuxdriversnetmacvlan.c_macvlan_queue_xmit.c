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
struct sk_buff {int /*<<< orphan*/  dev; scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct macvlan_port {int dummy; } ;
struct macvlan_dev {scalar_t__ mode; int /*<<< orphan*/  lowerdev; struct macvlan_port* port; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; } ;

/* Variables and functions */
 scalar_t__ MACVLAN_MODE_BRIDGE ; 
 int NET_XMIT_SUCCESS ; 
 int /*<<< orphan*/  dev_forward_skb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int dev_queue_xmit_accel (struct sk_buff*,struct net_device*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macvlan_broadcast (struct sk_buff*,struct macvlan_port const*,struct net_device*,scalar_t__) ; 
 struct macvlan_dev* macvlan_hash_lookup (struct macvlan_port const*,int /*<<< orphan*/ ) ; 
 scalar_t__ netdev_get_sb_channel (struct net_device*) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int macvlan_queue_xmit(struct sk_buff *skb, struct net_device *dev)
{
	const struct macvlan_dev *vlan = netdev_priv(dev);
	const struct macvlan_port *port = vlan->port;
	const struct macvlan_dev *dest;

	if (vlan->mode == MACVLAN_MODE_BRIDGE) {
		const struct ethhdr *eth = (void *)skb->data;

		/* send to other bridge ports directly */
		if (is_multicast_ether_addr(eth->h_dest)) {
			macvlan_broadcast(skb, port, dev, MACVLAN_MODE_BRIDGE);
			goto xmit_world;
		}

		dest = macvlan_hash_lookup(port, eth->h_dest);
		if (dest && dest->mode == MACVLAN_MODE_BRIDGE) {
			/* send to lowerdev first for its network taps */
			dev_forward_skb(vlan->lowerdev, skb);

			return NET_XMIT_SUCCESS;
		}
	}
xmit_world:
	skb->dev = vlan->lowerdev;
	return dev_queue_xmit_accel(skb,
				    netdev_get_sb_channel(dev) ? dev : NULL);
}