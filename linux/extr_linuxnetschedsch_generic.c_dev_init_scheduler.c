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
struct net_device {int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/ * qdisc; } ;

/* Variables and functions */
 scalar_t__ dev_ingress_queue (struct net_device*) ; 
 int /*<<< orphan*/  dev_init_scheduler_queue (struct net_device*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_watchdog ; 
 int /*<<< orphan*/  netdev_for_each_tx_queue (struct net_device*,int /*<<< orphan*/  (*) (struct net_device*,scalar_t__,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  noop_qdisc ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dev_init_scheduler(struct net_device *dev)
{
	dev->qdisc = &noop_qdisc;
	netdev_for_each_tx_queue(dev, dev_init_scheduler_queue, &noop_qdisc);
	if (dev_ingress_queue(dev))
		dev_init_scheduler_queue(dev, dev_ingress_queue(dev), &noop_qdisc);

	timer_setup(&dev->watchdog_timer, dev_watchdog, 0);
}