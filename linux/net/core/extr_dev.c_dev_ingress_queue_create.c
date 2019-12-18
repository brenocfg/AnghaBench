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
struct netdev_queue {int /*<<< orphan*/ * qdisc_sleeping; int /*<<< orphan*/  qdisc; } ;
struct net_device {int /*<<< orphan*/  ingress_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct netdev_queue* dev_ingress_queue (struct net_device*) ; 
 struct netdev_queue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_init_one_queue (struct net_device*,struct netdev_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  noop_qdisc ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct netdev_queue*) ; 

struct netdev_queue *dev_ingress_queue_create(struct net_device *dev)
{
	struct netdev_queue *queue = dev_ingress_queue(dev);

#ifdef CONFIG_NET_CLS_ACT
	if (queue)
		return queue;
	queue = kzalloc(sizeof(*queue), GFP_KERNEL);
	if (!queue)
		return NULL;
	netdev_init_one_queue(dev, queue, NULL);
	RCU_INIT_POINTER(queue->qdisc, &noop_qdisc);
	queue->qdisc_sleeping = &noop_qdisc;
	rcu_assign_pointer(dev->ingress_queue, queue);
#endif
	return queue;
}