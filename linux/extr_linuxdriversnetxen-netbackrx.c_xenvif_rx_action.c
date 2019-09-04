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
struct TYPE_2__ {struct sk_buff_head* completed; } ;
struct xenvif_queue {TYPE_1__ rx_copy; } ;
struct sk_buff_head {int dummy; } ;

/* Variables and functions */
 unsigned int RX_BATCH_SIZE ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  xenvif_rx_copy_flush (struct xenvif_queue*) ; 
 scalar_t__ xenvif_rx_ring_slots_available (struct xenvif_queue*) ; 
 int /*<<< orphan*/  xenvif_rx_skb (struct xenvif_queue*) ; 

void xenvif_rx_action(struct xenvif_queue *queue)
{
	struct sk_buff_head completed_skbs;
	unsigned int work_done = 0;

	__skb_queue_head_init(&completed_skbs);
	queue->rx_copy.completed = &completed_skbs;

	while (xenvif_rx_ring_slots_available(queue) &&
	       work_done < RX_BATCH_SIZE) {
		xenvif_rx_skb(queue);
		work_done++;
	}

	/* Flush any pending copies and complete all skbs. */
	xenvif_rx_copy_flush(queue);
}