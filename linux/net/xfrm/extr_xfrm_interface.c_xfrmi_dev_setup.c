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
struct net_device {int needs_free_netdev; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  priv_destructor; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr_len; void* max_mtu; int /*<<< orphan*/  min_mtu; void* mtu; void* min_header_len; void* hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_NONE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 void* ETH_DATA_LEN ; 
 void* ETH_HLEN ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 
 int /*<<< orphan*/  xfrmi_dev_free ; 
 int /*<<< orphan*/  xfrmi_netdev_ops ; 

__attribute__((used)) static void xfrmi_dev_setup(struct net_device *dev)
{
	dev->netdev_ops 	= &xfrmi_netdev_ops;
	dev->type		= ARPHRD_NONE;
	dev->hard_header_len 	= ETH_HLEN;
	dev->min_header_len	= ETH_HLEN;
	dev->mtu		= ETH_DATA_LEN;
	dev->min_mtu		= ETH_MIN_MTU;
	dev->max_mtu		= ETH_DATA_LEN;
	dev->addr_len		= ETH_ALEN;
	dev->flags 		= IFF_NOARP;
	dev->needs_free_netdev	= true;
	dev->priv_destructor	= xfrmi_dev_free;
	netif_keep_dst(dev);

	eth_broadcast_addr(dev->broadcast);
}