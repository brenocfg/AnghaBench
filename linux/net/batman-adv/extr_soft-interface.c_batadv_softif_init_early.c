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
struct net_device {int needs_free_netdev; int features; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  mtu; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  priv_destructor; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_DATA_LEN ; 
 int /*<<< orphan*/  IFF_NO_QUEUE ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_LLTX ; 
 int NETIF_F_NETNS_LOCAL ; 
 int /*<<< orphan*/  batadv_ethtool_ops ; 
 int /*<<< orphan*/  batadv_netdev_ops ; 
 int /*<<< orphan*/  batadv_softif_free ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 

__attribute__((used)) static void batadv_softif_init_early(struct net_device *dev)
{
	ether_setup(dev);

	dev->netdev_ops = &batadv_netdev_ops;
	dev->needs_free_netdev = true;
	dev->priv_destructor = batadv_softif_free;
	dev->features |= NETIF_F_HW_VLAN_CTAG_FILTER | NETIF_F_NETNS_LOCAL;
	dev->features |= NETIF_F_LLTX;
	dev->priv_flags |= IFF_NO_QUEUE;

	/* can't call min_mtu, because the needed variables
	 * have not been initialized yet
	 */
	dev->mtu = ETH_DATA_LEN;

	/* generate random address */
	eth_hw_addr_random(dev);

	dev->ethtool_ops = &batadv_ethtool_ops;
}