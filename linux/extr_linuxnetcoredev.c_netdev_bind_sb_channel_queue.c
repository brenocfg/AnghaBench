#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;
struct net_device {scalar_t__ num_tc; scalar_t__ real_num_tx_queues; TYPE_1__* tc_to_txq; } ;
struct TYPE_4__ {struct net_device* sb_dev; } ;
struct TYPE_3__ {scalar_t__ offset; scalar_t__ count; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__* netdev_get_tx_queue (struct net_device*,scalar_t__) ; 

int netdev_bind_sb_channel_queue(struct net_device *dev,
				 struct net_device *sb_dev,
				 u8 tc, u16 count, u16 offset)
{
	/* Make certain the sb_dev and dev are already configured */
	if (sb_dev->num_tc >= 0 || tc >= dev->num_tc)
		return -EINVAL;

	/* We cannot hand out queues we don't have */
	if ((offset + count) > dev->real_num_tx_queues)
		return -EINVAL;

	/* Record the mapping */
	sb_dev->tc_to_txq[tc].count = count;
	sb_dev->tc_to_txq[tc].offset = offset;

	/* Provide a way for Tx queue to find the tc_to_txq map or
	 * XPS map for itself.
	 */
	while (count--)
		netdev_get_tx_queue(dev, count + offset)->sb_dev = sb_dev;

	return 0;
}