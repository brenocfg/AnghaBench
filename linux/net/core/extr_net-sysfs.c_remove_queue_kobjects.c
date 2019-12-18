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
struct net_device {int real_num_rx_queues; int real_num_tx_queues; int /*<<< orphan*/  queues_kset; } ;

/* Variables and functions */
 int /*<<< orphan*/  kset_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_rx_queue_update_kobjects (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_queue_update_kobjects (struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_queue_kobjects(struct net_device *dev)
{
	int real_rx = 0, real_tx = 0;

#ifdef CONFIG_SYSFS
	real_rx = dev->real_num_rx_queues;
#endif
	real_tx = dev->real_num_tx_queues;

	net_rx_queue_update_kobjects(dev, real_rx, 0);
	netdev_queue_update_kobjects(dev, real_tx, 0);
#ifdef CONFIG_SYSFS
	kset_unregister(dev->queues_kset);
#endif
}