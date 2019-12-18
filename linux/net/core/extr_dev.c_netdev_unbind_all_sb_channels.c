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
struct netdev_queue {scalar_t__ sb_dev; } ;
struct net_device {size_t num_tx_queues; struct netdev_queue* _tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_unbind_sb_channel (struct net_device*,scalar_t__) ; 

__attribute__((used)) static void netdev_unbind_all_sb_channels(struct net_device *dev)
{
	struct netdev_queue *txq = &dev->_tx[dev->num_tx_queues];

	/* Unbind any subordinate channels */
	while (txq-- != &dev->_tx[0]) {
		if (txq->sb_dev)
			netdev_unbind_sb_channel(dev, txq->sb_dev);
	}
}