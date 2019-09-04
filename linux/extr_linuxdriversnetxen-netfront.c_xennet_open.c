#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rsp_cons; TYPE_1__* sring; } ;
struct netfront_queue {int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  napi; TYPE_2__ rx; } ;
struct netfront_info {struct netfront_queue* queues; } ;
struct net_device {unsigned int real_num_tx_queues; } ;
struct TYPE_3__ {scalar_t__ rsp_event; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ RING_HAS_UNCONSUMED_RESPONSES (TYPE_2__*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct netfront_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xennet_alloc_rx_buffers (struct netfront_queue*) ; 

__attribute__((used)) static int xennet_open(struct net_device *dev)
{
	struct netfront_info *np = netdev_priv(dev);
	unsigned int num_queues = dev->real_num_tx_queues;
	unsigned int i = 0;
	struct netfront_queue *queue = NULL;

	if (!np->queues)
		return -ENODEV;

	for (i = 0; i < num_queues; ++i) {
		queue = &np->queues[i];
		napi_enable(&queue->napi);

		spin_lock_bh(&queue->rx_lock);
		if (netif_carrier_ok(dev)) {
			xennet_alloc_rx_buffers(queue);
			queue->rx.sring->rsp_event = queue->rx.rsp_cons + 1;
			if (RING_HAS_UNCONSUMED_RESPONSES(&queue->rx))
				napi_schedule(&queue->napi);
		}
		spin_unlock_bh(&queue->rx_lock);
	}

	netif_tx_start_all_queues(dev);

	return 0;
}