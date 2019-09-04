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
struct netdev_queue {int dummy; } ;
struct net_device {unsigned int num_tx_queues; int /*<<< orphan*/  tx_global_lock; struct netdev_queue* _tx; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int __GFP_RETRY_MAYFAIL ; 
 struct netdev_queue* kvzalloc (size_t,int) ; 
 int /*<<< orphan*/  netdev_for_each_tx_queue (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_init_one_queue ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netif_alloc_netdev_queues(struct net_device *dev)
{
	unsigned int count = dev->num_tx_queues;
	struct netdev_queue *tx;
	size_t sz = count * sizeof(*tx);

	if (count < 1 || count > 0xffff)
		return -EINVAL;

	tx = kvzalloc(sz, GFP_KERNEL | __GFP_RETRY_MAYFAIL);
	if (!tx)
		return -ENOMEM;

	dev->_tx = tx;

	netdev_for_each_tx_queue(dev, netdev_init_one_queue, NULL);
	spin_lock_init(&dev->tx_global_lock);

	return 0;
}