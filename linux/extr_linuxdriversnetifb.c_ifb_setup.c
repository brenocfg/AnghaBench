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
struct net_device {int features; int hw_features; int hw_enc_features; int vlan_features; int needs_free_netdev; scalar_t__ max_mtu; scalar_t__ min_mtu; int /*<<< orphan*/  priv_destructor; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_queue_len; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int IFB_FEATURES ; 
 int /*<<< orphan*/  IFF_MULTICAST ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_HW_VLAN_STAG_TX ; 
 int /*<<< orphan*/  TX_Q_LIMIT ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  ifb_dev_free ; 
 int /*<<< orphan*/  ifb_netdev_ops ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 

__attribute__((used)) static void ifb_setup(struct net_device *dev)
{
	/* Initialize the device structure. */
	dev->netdev_ops = &ifb_netdev_ops;

	/* Fill in device structure with ethernet-generic values. */
	ether_setup(dev);
	dev->tx_queue_len = TX_Q_LIMIT;

	dev->features |= IFB_FEATURES;
	dev->hw_features |= dev->features;
	dev->hw_enc_features |= dev->features;
	dev->vlan_features |= IFB_FEATURES & ~(NETIF_F_HW_VLAN_CTAG_TX |
					       NETIF_F_HW_VLAN_STAG_TX);

	dev->flags |= IFF_NOARP;
	dev->flags &= ~IFF_MULTICAST;
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	netif_keep_dst(dev);
	eth_hw_addr_random(dev);
	dev->needs_free_netdev = true;
	dev->priv_destructor = ifb_dev_free;

	dev->min_mtu = 0;
	dev->max_mtu = 0;
}