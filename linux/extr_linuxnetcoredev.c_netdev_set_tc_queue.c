#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  void* u16 ;
struct net_device {size_t num_tc; TYPE_1__* tc_to_txq; } ;
struct TYPE_2__ {void* offset; void* count; } ;

/* Variables and functions */
 int EINVAL ; 

int netdev_set_tc_queue(struct net_device *dev, u8 tc, u16 count, u16 offset)
{
	if (tc >= dev->num_tc)
		return -EINVAL;

#ifdef CONFIG_XPS
	netif_reset_xps_queues(dev, offset, count);
#endif
	dev->tc_to_txq[tc].count = count;
	dev->tc_to_txq[tc].offset = offset;
	return 0;
}