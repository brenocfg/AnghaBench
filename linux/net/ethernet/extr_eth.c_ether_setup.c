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
struct net_device {int flags; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  tx_queue_len; int /*<<< orphan*/  addr_len; void* max_mtu; int /*<<< orphan*/  min_mtu; void* mtu; void* min_header_len; void* hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/ * header_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  DEFAULT_TX_QUEUE_LEN ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 void* ETH_DATA_LEN ; 
 void* ETH_HLEN ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_header_ops ; 

void ether_setup(struct net_device *dev)
{
	dev->header_ops		= &eth_header_ops;
	dev->type		= ARPHRD_ETHER;
	dev->hard_header_len 	= ETH_HLEN;
	dev->min_header_len	= ETH_HLEN;
	dev->mtu		= ETH_DATA_LEN;
	dev->min_mtu		= ETH_MIN_MTU;
	dev->max_mtu		= ETH_DATA_LEN;
	dev->addr_len		= ETH_ALEN;
	dev->tx_queue_len	= DEFAULT_TX_QUEUE_LEN;
	dev->flags		= IFF_BROADCAST|IFF_MULTICAST;
	dev->priv_flags		|= IFF_TX_SKB_SHARING;

	eth_broadcast_addr(dev->broadcast);

}