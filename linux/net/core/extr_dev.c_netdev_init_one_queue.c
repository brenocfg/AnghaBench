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
struct netdev_queue {int xmit_lock_owner; int /*<<< orphan*/  dql; struct net_device* dev; int /*<<< orphan*/  _xmit_lock; } ;
struct net_device {int /*<<< orphan*/  qdisc_xmit_lock_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int /*<<< orphan*/  dql_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_queue_numa_node_write (struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netdev_init_one_queue(struct net_device *dev,
				  struct netdev_queue *queue, void *_unused)
{
	/* Initialize queue lock */
	spin_lock_init(&queue->_xmit_lock);
	lockdep_set_class(&queue->_xmit_lock, &dev->qdisc_xmit_lock_key);
	queue->xmit_lock_owner = -1;
	netdev_queue_numa_node_write(queue, NUMA_NO_NODE);
	queue->dev = dev;
#ifdef CONFIG_BQL
	dql_init(&queue->dql, HZ);
#endif
}