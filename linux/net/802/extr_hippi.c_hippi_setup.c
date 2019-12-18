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
struct net_device {int mtu; int min_mtu; int max_mtu; int tx_queue_len; scalar_t__ flags; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/ * header_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_HIPPI ; 
 int /*<<< orphan*/  HIPPI_ALEN ; 
 int /*<<< orphan*/  HIPPI_HLEN ; 
 int /*<<< orphan*/  hippi_header_ops ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hippi_setup(struct net_device *dev)
{
	dev->header_ops			= &hippi_header_ops;

	/*
	 * We don't support HIPPI `ARP' for the time being, and probably
	 * never will unless someone else implements it. However we
	 * still need a fake ARPHRD to make ifconfig and friends play ball.
	 */
	dev->type		= ARPHRD_HIPPI;
	dev->hard_header_len 	= HIPPI_HLEN;
	dev->mtu		= 65280;
	dev->min_mtu		= 68;
	dev->max_mtu		= 65280;
	dev->addr_len		= HIPPI_ALEN;
	dev->tx_queue_len	= 25 /* 5 */;
	memset(dev->broadcast, 0xFF, HIPPI_ALEN);


	/*
	 * HIPPI doesn't support broadcast+multicast and we only use
	 * static ARP tables. ARP is disabled by hippi_neigh_setup_dev.
	 */
	dev->flags = 0;
}