#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int num_tx_queues; } ;
struct TYPE_2__ {int /*<<< orphan*/  trans_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 TYPE_1__* netdev_get_tx_queue (struct net_device*,int) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 

void mwifiex_set_trans_start(struct net_device *dev)
{
	int i;

	for (i = 0; i < dev->num_tx_queues; i++)
		netdev_get_tx_queue(dev, i)->trans_start = jiffies;

	netif_trans_update(dev);
}