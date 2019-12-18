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
struct net_device {int /*<<< orphan*/  prio_tc_map; int /*<<< orphan*/  tc_to_txq; scalar_t__ num_tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_unbind_all_sb_channels (struct net_device*) ; 
 int /*<<< orphan*/  netif_reset_xps_queues_gt (struct net_device*,int /*<<< orphan*/ ) ; 

void netdev_reset_tc(struct net_device *dev)
{
#ifdef CONFIG_XPS
	netif_reset_xps_queues_gt(dev, 0);
#endif
	netdev_unbind_all_sb_channels(dev);

	/* Reset TC configuration of device */
	dev->num_tc = 0;
	memset(dev->tc_to_txq, 0, sizeof(dev->tc_to_txq));
	memset(dev->prio_tc_map, 0, sizeof(dev->prio_tc_map));
}