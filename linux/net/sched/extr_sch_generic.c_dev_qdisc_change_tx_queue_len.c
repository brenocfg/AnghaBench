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
struct net_device {int flags; unsigned int num_tx_queues; int /*<<< orphan*/ * _tx; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  dev_activate (struct net_device*) ; 
 int /*<<< orphan*/  dev_deactivate (struct net_device*) ; 
 int qdisc_change_tx_queue_len (struct net_device*,int /*<<< orphan*/ *) ; 

int dev_qdisc_change_tx_queue_len(struct net_device *dev)
{
	bool up = dev->flags & IFF_UP;
	unsigned int i;
	int ret = 0;

	if (up)
		dev_deactivate(dev);

	for (i = 0; i < dev->num_tx_queues; i++) {
		ret = qdisc_change_tx_queue_len(dev, &dev->_tx[i]);

		/* TODO: revert changes on a partial failure */
		if (ret)
			break;
	}

	if (up)
		dev_activate(dev);
	return ret;
}