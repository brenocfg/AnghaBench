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
struct net_device {int needs_free_netdev; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  features; int /*<<< orphan*/  priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int /*<<< orphan*/  NETIF_F_LLTX ; 
 int /*<<< orphan*/  SET_NETDEV_DEVTYPE (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  l2tp_eth_netdev_ops ; 
 int /*<<< orphan*/  l2tpeth_type ; 

__attribute__((used)) static void l2tp_eth_dev_setup(struct net_device *dev)
{
	SET_NETDEV_DEVTYPE(dev, &l2tpeth_type);
	ether_setup(dev);
	dev->priv_flags		&= ~IFF_TX_SKB_SHARING;
	dev->features		|= NETIF_F_LLTX;
	dev->netdev_ops		= &l2tp_eth_netdev_ops;
	dev->needs_free_netdev	= true;
}