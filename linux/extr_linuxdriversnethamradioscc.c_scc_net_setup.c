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
struct net_device {int tx_queue_len; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  mtu; scalar_t__ hard_header_len; int /*<<< orphan*/  type; scalar_t__ flags; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  broadcast; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_AX25 ; 
 int /*<<< orphan*/  AX25_ADDR_LEN ; 
 scalar_t__ AX25_BPQ_HEADER_LEN ; 
 int /*<<< orphan*/  AX25_DEF_PACLEN ; 
 scalar_t__ AX25_MAX_HEADER_LEN ; 
 int /*<<< orphan*/  ax25_bcast ; 
 int /*<<< orphan*/  ax25_defaddr ; 
 int /*<<< orphan*/  ax25_header_ops ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scc_netdev_ops ; 

__attribute__((used)) static void scc_net_setup(struct net_device *dev)
{
	dev->tx_queue_len    = 16;	/* should be enough... */

	dev->netdev_ops	     = &scc_netdev_ops;
	dev->header_ops      = &ax25_header_ops;

	memcpy(dev->broadcast, &ax25_bcast,  AX25_ADDR_LEN);
	memcpy(dev->dev_addr,  &ax25_defaddr, AX25_ADDR_LEN);
 
	dev->flags      = 0;

	dev->type = ARPHRD_AX25;
	dev->hard_header_len = AX25_MAX_HEADER_LEN + AX25_BPQ_HEADER_LEN;
	dev->mtu = AX25_DEF_PACLEN;
	dev->addr_len = AX25_ADDR_LEN;

}