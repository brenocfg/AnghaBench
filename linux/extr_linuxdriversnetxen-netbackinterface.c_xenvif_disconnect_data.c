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
struct xenvif_queue {scalar_t__ tx_irq; scalar_t__ rx_irq; int /*<<< orphan*/ * dealloc_task; int /*<<< orphan*/ * task; int /*<<< orphan*/  napi; } ;
struct xenvif {unsigned int num_queues; struct xenvif_queue* queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_task_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unbind_from_irqhandler (scalar_t__,struct xenvif_queue*) ; 
 int /*<<< orphan*/  xenvif_carrier_off (struct xenvif*) ; 
 int /*<<< orphan*/  xenvif_mcast_addr_list_free (struct xenvif*) ; 
 int /*<<< orphan*/  xenvif_unmap_frontend_data_rings (struct xenvif_queue*) ; 

void xenvif_disconnect_data(struct xenvif *vif)
{
	struct xenvif_queue *queue = NULL;
	unsigned int num_queues = vif->num_queues;
	unsigned int queue_index;

	xenvif_carrier_off(vif);

	for (queue_index = 0; queue_index < num_queues; ++queue_index) {
		queue = &vif->queues[queue_index];

		netif_napi_del(&queue->napi);

		if (queue->task) {
			kthread_stop(queue->task);
			put_task_struct(queue->task);
			queue->task = NULL;
		}

		if (queue->dealloc_task) {
			kthread_stop(queue->dealloc_task);
			queue->dealloc_task = NULL;
		}

		if (queue->tx_irq) {
			if (queue->tx_irq == queue->rx_irq)
				unbind_from_irqhandler(queue->tx_irq, queue);
			else {
				unbind_from_irqhandler(queue->tx_irq, queue);
				unbind_from_irqhandler(queue->rx_irq, queue);
			}
			queue->tx_irq = 0;
		}

		xenvif_unmap_frontend_data_rings(queue);
	}

	xenvif_mcast_addr_list_free(vif);
}