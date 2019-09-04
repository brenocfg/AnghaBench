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
struct tun_struct {int flags; } ;
struct net_device {int mtu; int flags; scalar_t__ hard_header_len; scalar_t__ max_mtu; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  type; int /*<<< orphan*/  addr_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_NONE ; 
 int /*<<< orphan*/  IFF_LIVE_ADDR_CHANGE ; 
 int IFF_MULTICAST ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
#define  IFF_TAP 129 
#define  IFF_TUN 128 
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 scalar_t__ MAX_MTU ; 
 int /*<<< orphan*/  MIN_MTU ; 
 int TUN_TYPE_MASK ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 struct tun_struct* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tap_netdev_ops ; 
 int /*<<< orphan*/  tun_netdev_ops ; 

__attribute__((used)) static void tun_net_init(struct net_device *dev)
{
	struct tun_struct *tun = netdev_priv(dev);

	switch (tun->flags & TUN_TYPE_MASK) {
	case IFF_TUN:
		dev->netdev_ops = &tun_netdev_ops;

		/* Point-to-Point TUN Device */
		dev->hard_header_len = 0;
		dev->addr_len = 0;
		dev->mtu = 1500;

		/* Zero header length */
		dev->type = ARPHRD_NONE;
		dev->flags = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;
		break;

	case IFF_TAP:
		dev->netdev_ops = &tap_netdev_ops;
		/* Ethernet TAP Device */
		ether_setup(dev);
		dev->priv_flags &= ~IFF_TX_SKB_SHARING;
		dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;

		eth_hw_addr_random(dev);

		break;
	}

	dev->min_mtu = MIN_MTU;
	dev->max_mtu = MAX_MTU - dev->hard_header_len;
}