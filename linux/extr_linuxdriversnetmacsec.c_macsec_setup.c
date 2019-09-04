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
struct net_device {int needs_free_netdev; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  priv_destructor; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  max_mtu; scalar_t__ min_mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_MAX_MTU ; 
 int /*<<< orphan*/  IFF_NO_QUEUE ; 
 int /*<<< orphan*/  SET_NETDEV_DEVTYPE (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  macsec_free_netdev ; 
 int /*<<< orphan*/  macsec_netdev_ops ; 
 int /*<<< orphan*/  macsec_type ; 

__attribute__((used)) static void macsec_setup(struct net_device *dev)
{
	ether_setup(dev);
	dev->min_mtu = 0;
	dev->max_mtu = ETH_MAX_MTU;
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->netdev_ops = &macsec_netdev_ops;
	dev->needs_free_netdev = true;
	dev->priv_destructor = macsec_free_netdev;
	SET_NETDEV_DEVTYPE(dev, &macsec_type);

	eth_zero_addr(dev->broadcast);
}