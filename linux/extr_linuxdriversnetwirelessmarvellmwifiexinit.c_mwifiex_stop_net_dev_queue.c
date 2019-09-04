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
struct net_device {int dummy; } ;
struct mwifiex_adapter {int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mwifiex_stop_net_dev_queue(struct net_device *netdev,
					struct mwifiex_adapter *adapter)
{
	unsigned long dev_queue_flags;

	spin_lock_irqsave(&adapter->queue_lock, dev_queue_flags);
	netif_tx_stop_all_queues(netdev);
	spin_unlock_irqrestore(&adapter->queue_lock, dev_queue_flags);
}