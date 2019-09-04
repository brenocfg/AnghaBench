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
struct net_device {int flags; int needs_free_netdev; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  addr_assign_type; int /*<<< orphan*/ * ethtool_ops; scalar_t__ hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/  tx_queue_len; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  needed_headroom; int /*<<< orphan*/  mtu; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_RAWIP ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  NET_ADDR_RANDOM ; 
 int /*<<< orphan*/  RMNET_DFLT_PACKET_SIZE ; 
 int /*<<< orphan*/  RMNET_NEEDED_HEADROOM ; 
 int /*<<< orphan*/  RMNET_TX_QUEUE_LEN ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmnet_ethtool_ops ; 
 int /*<<< orphan*/  rmnet_vnd_ops ; 

void rmnet_vnd_setup(struct net_device *rmnet_dev)
{
	rmnet_dev->netdev_ops = &rmnet_vnd_ops;
	rmnet_dev->mtu = RMNET_DFLT_PACKET_SIZE;
	rmnet_dev->needed_headroom = RMNET_NEEDED_HEADROOM;
	eth_random_addr(rmnet_dev->dev_addr);
	rmnet_dev->tx_queue_len = RMNET_TX_QUEUE_LEN;

	/* Raw IP mode */
	rmnet_dev->header_ops = NULL;  /* No header */
	rmnet_dev->type = ARPHRD_RAWIP;
	rmnet_dev->hard_header_len = 0;
	rmnet_dev->flags &= ~(IFF_BROADCAST | IFF_MULTICAST);

	rmnet_dev->needs_free_netdev = true;
	rmnet_dev->ethtool_ops = &rmnet_ethtool_ops;

	/* This perm addr will be used as interface identifier by IPv6 */
	rmnet_dev->addr_assign_type = NET_ADDR_RANDOM;
	eth_random_addr(rmnet_dev->perm_addr);
}