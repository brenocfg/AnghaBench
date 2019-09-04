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
struct net_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  addr_len; scalar_t__ hard_header_len; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_NETROM ; 
 int /*<<< orphan*/  AX25_ADDR_LEN ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  NR_MAX_PACKET_SIZE ; 
 scalar_t__ NR_NETWORK_LEN ; 
 scalar_t__ NR_TRANSPORT_LEN ; 
 int /*<<< orphan*/  nr_header_ops ; 
 int /*<<< orphan*/  nr_netdev_ops ; 

void nr_setup(struct net_device *dev)
{
	dev->mtu		= NR_MAX_PACKET_SIZE;
	dev->netdev_ops		= &nr_netdev_ops;
	dev->header_ops		= &nr_header_ops;
	dev->hard_header_len	= NR_NETWORK_LEN + NR_TRANSPORT_LEN;
	dev->addr_len		= AX25_ADDR_LEN;
	dev->type		= ARPHRD_NETROM;

	/* New-style flags. */
	dev->flags		= IFF_NOARP;
}