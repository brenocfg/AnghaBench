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
struct net_device {int watchdog_timeo; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  max_mtu; scalar_t__ min_mtu; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  broadcast; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_MAX_MTU ; 
 int HZ ; 
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int /*<<< orphan*/  bnep_netdev_ops ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 

void bnep_net_setup(struct net_device *dev)
{

	eth_broadcast_addr(dev->broadcast);
	dev->addr_len = ETH_ALEN;

	ether_setup(dev);
	dev->min_mtu = 0;
	dev->max_mtu = ETH_MAX_MTU;
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->netdev_ops = &bnep_netdev_ops;

	dev->watchdog_timeo  = HZ * 2;
}