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
struct net_device {int priv_flags; int needs_free_netdev; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  max_mtu; scalar_t__ min_mtu; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  priv_destructor; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_MAX_MTU ; 
 int IFF_802_1Q_VLAN ; 
 int IFF_NO_QUEUE ; 
 int IFF_TX_SKB_SHARING ; 
 int IFF_UNICAST_FLT ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 
 int /*<<< orphan*/  vlan_dev_free ; 
 int /*<<< orphan*/  vlan_ethtool_ops ; 
 int /*<<< orphan*/  vlan_netdev_ops ; 

void vlan_setup(struct net_device *dev)
{
	ether_setup(dev);

	dev->priv_flags		|= IFF_802_1Q_VLAN | IFF_NO_QUEUE;
	dev->priv_flags		|= IFF_UNICAST_FLT;
	dev->priv_flags		&= ~IFF_TX_SKB_SHARING;
	netif_keep_dst(dev);

	dev->netdev_ops		= &vlan_netdev_ops;
	dev->needs_free_netdev	= true;
	dev->priv_destructor	= vlan_dev_free;
	dev->ethtool_ops	= &vlan_ethtool_ops;

	dev->min_mtu		= 0;
	dev->max_mtu		= ETH_MAX_MTU;

	eth_zero_addr(dev->broadcast);
}