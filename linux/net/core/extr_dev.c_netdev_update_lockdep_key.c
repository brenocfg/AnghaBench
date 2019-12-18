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
struct netdev_queue {int /*<<< orphan*/  _xmit_lock; } ;
struct net_device {int num_tx_queues; int /*<<< orphan*/  qdisc_xmit_lock_key; int /*<<< orphan*/  addr_list_lock_key; int /*<<< orphan*/  addr_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_register_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_unregister_key (int /*<<< orphan*/ *) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int) ; 

void netdev_update_lockdep_key(struct net_device *dev)
{
	struct netdev_queue *queue;
	int i;

	lockdep_unregister_key(&dev->qdisc_xmit_lock_key);
	lockdep_unregister_key(&dev->addr_list_lock_key);

	lockdep_register_key(&dev->qdisc_xmit_lock_key);
	lockdep_register_key(&dev->addr_list_lock_key);

	lockdep_set_class(&dev->addr_list_lock, &dev->addr_list_lock_key);
	for (i = 0; i < dev->num_tx_queues; i++) {
		queue = netdev_get_tx_queue(dev, i);

		lockdep_set_class(&queue->_xmit_lock,
				  &dev->qdisc_xmit_lock_key);
	}
}