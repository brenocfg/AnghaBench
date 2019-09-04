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
struct net_device {unsigned long num_tx_queues; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,unsigned long) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 

__attribute__((used)) static struct netdev_queue *mqprio_queue_get(struct Qdisc *sch,
					     unsigned long cl)
{
	struct net_device *dev = qdisc_dev(sch);
	unsigned long ntx = cl - 1;

	if (ntx >= dev->num_tx_queues)
		return NULL;
	return netdev_get_tx_queue(dev, ntx);
}