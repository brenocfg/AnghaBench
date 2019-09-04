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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct xenvif_queue {scalar_t__ rx_queue_len; scalar_t__ rx_queue_max; TYPE_2__ rx_queue; int /*<<< orphan*/  id; TYPE_1__* vif; } ;
struct sk_buff {scalar_t__ len; } ;
struct netdev_queue {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (TYPE_2__*) ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff *xenvif_rx_dequeue(struct xenvif_queue *queue)
{
	struct sk_buff *skb;

	spin_lock_irq(&queue->rx_queue.lock);

	skb = __skb_dequeue(&queue->rx_queue);
	if (skb) {
		queue->rx_queue_len -= skb->len;
		if (queue->rx_queue_len < queue->rx_queue_max) {
			struct netdev_queue *txq;

			txq = netdev_get_tx_queue(queue->vif->dev, queue->id);
			netif_tx_wake_queue(txq);
		}
	}

	spin_unlock_irq(&queue->rx_queue.lock);

	return skb;
}