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
typedef  scalar_t__ u8 ;
struct net_device {scalar_t__ num_tc; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TC_MAX_QUEUE ; 
 int /*<<< orphan*/  netdev_unbind_all_sb_channels (struct net_device*) ; 
 int /*<<< orphan*/  netif_reset_xps_queues_gt (struct net_device*,int /*<<< orphan*/ ) ; 

int netdev_set_num_tc(struct net_device *dev, u8 num_tc)
{
	if (num_tc > TC_MAX_QUEUE)
		return -EINVAL;

#ifdef CONFIG_XPS
	netif_reset_xps_queues_gt(dev, 0);
#endif
	netdev_unbind_all_sb_channels(dev);

	dev->num_tc = num_tc;
	return 0;
}