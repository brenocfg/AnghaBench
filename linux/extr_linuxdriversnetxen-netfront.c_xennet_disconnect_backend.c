#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * sring; } ;
struct TYPE_5__ {int /*<<< orphan*/ * sring; } ;
struct netfront_queue {scalar_t__ tx_irq; scalar_t__ rx_irq; TYPE_2__ rx; TYPE_1__ tx; void* rx_ring_ref; void* tx_ring_ref; int /*<<< orphan*/  gref_rx_head; int /*<<< orphan*/  gref_tx_head; int /*<<< orphan*/  napi; scalar_t__ rx_evtchn; scalar_t__ tx_evtchn; int /*<<< orphan*/  rx_refill_timer; } ;
struct netfront_info {TYPE_3__* netdev; struct netfront_queue* queues; } ;
struct TYPE_7__ {unsigned int real_num_tx_queues; } ;

/* Variables and functions */
 void* GRANT_INVALID_REF ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_free_grant_references (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (TYPE_3__*) ; 
 scalar_t__ netif_running (TYPE_3__*) ; 
 int /*<<< orphan*/  unbind_from_irqhandler (scalar_t__,struct netfront_queue*) ; 
 int /*<<< orphan*/  xennet_end_access (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xennet_release_rx_bufs (struct netfront_queue*) ; 
 int /*<<< orphan*/  xennet_release_tx_bufs (struct netfront_queue*) ; 

__attribute__((used)) static void xennet_disconnect_backend(struct netfront_info *info)
{
	unsigned int i = 0;
	unsigned int num_queues = info->netdev->real_num_tx_queues;

	netif_carrier_off(info->netdev);

	for (i = 0; i < num_queues && info->queues; ++i) {
		struct netfront_queue *queue = &info->queues[i];

		del_timer_sync(&queue->rx_refill_timer);

		if (queue->tx_irq && (queue->tx_irq == queue->rx_irq))
			unbind_from_irqhandler(queue->tx_irq, queue);
		if (queue->tx_irq && (queue->tx_irq != queue->rx_irq)) {
			unbind_from_irqhandler(queue->tx_irq, queue);
			unbind_from_irqhandler(queue->rx_irq, queue);
		}
		queue->tx_evtchn = queue->rx_evtchn = 0;
		queue->tx_irq = queue->rx_irq = 0;

		if (netif_running(info->netdev))
			napi_synchronize(&queue->napi);

		xennet_release_tx_bufs(queue);
		xennet_release_rx_bufs(queue);
		gnttab_free_grant_references(queue->gref_tx_head);
		gnttab_free_grant_references(queue->gref_rx_head);

		/* End access and free the pages */
		xennet_end_access(queue->tx_ring_ref, queue->tx.sring);
		xennet_end_access(queue->rx_ring_ref, queue->rx.sring);

		queue->tx_ring_ref = GRANT_INVALID_REF;
		queue->rx_ring_ref = GRANT_INVALID_REF;
		queue->tx.sring = NULL;
		queue->rx.sring = NULL;
	}
}