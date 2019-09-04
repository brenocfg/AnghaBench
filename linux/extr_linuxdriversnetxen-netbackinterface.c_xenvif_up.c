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
struct xenvif_queue {scalar_t__ tx_irq; scalar_t__ rx_irq; int /*<<< orphan*/  napi; } ;
struct xenvif {unsigned int num_queues; struct xenvif_queue* queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (scalar_t__) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenvif_napi_schedule_or_enable_events (struct xenvif_queue*) ; 

__attribute__((used)) static void xenvif_up(struct xenvif *vif)
{
	struct xenvif_queue *queue = NULL;
	unsigned int num_queues = vif->num_queues;
	unsigned int queue_index;

	for (queue_index = 0; queue_index < num_queues; ++queue_index) {
		queue = &vif->queues[queue_index];
		napi_enable(&queue->napi);
		enable_irq(queue->tx_irq);
		if (queue->tx_irq != queue->rx_irq)
			enable_irq(queue->rx_irq);
		xenvif_napi_schedule_or_enable_events(queue);
	}
}