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
struct netfront_queue {int /*<<< orphan*/  napi; } ;
struct netfront_info {struct netfront_queue* queues; int /*<<< orphan*/  netdev; } ;
struct net_device {unsigned int real_num_tx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct netfront_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xennet_close(struct net_device *dev)
{
	struct netfront_info *np = netdev_priv(dev);
	unsigned int num_queues = dev->real_num_tx_queues;
	unsigned int i;
	struct netfront_queue *queue;
	netif_tx_stop_all_queues(np->netdev);
	for (i = 0; i < num_queues; ++i) {
		queue = &np->queues[i];
		napi_disable(&queue->napi);
	}
	return 0;
}