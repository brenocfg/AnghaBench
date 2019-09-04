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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  tx_zerocopy_fail; int /*<<< orphan*/  tx_zerocopy_success; } ;
struct xenvif_queue {scalar_t__ dealloc_prod; scalar_t__ dealloc_cons; TYPE_1__ stats; int /*<<< orphan*/  callback_lock; int /*<<< orphan*/ * dealloc_ring; } ;
struct ubuf_info {scalar_t__ ctx; int /*<<< orphan*/  desc; } ;
typedef  size_t pending_ring_idx_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ MAX_PENDING_REQS ; 
 scalar_t__ likely (int) ; 
 size_t pending_index (scalar_t__) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct xenvif_queue* ubuf_to_queue (struct ubuf_info*) ; 
 int /*<<< orphan*/  xenvif_skb_zerocopy_complete (struct xenvif_queue*) ; 

void xenvif_zerocopy_callback(struct ubuf_info *ubuf, bool zerocopy_success)
{
	unsigned long flags;
	pending_ring_idx_t index;
	struct xenvif_queue *queue = ubuf_to_queue(ubuf);

	/* This is the only place where we grab this lock, to protect callbacks
	 * from each other.
	 */
	spin_lock_irqsave(&queue->callback_lock, flags);
	do {
		u16 pending_idx = ubuf->desc;
		ubuf = (struct ubuf_info *) ubuf->ctx;
		BUG_ON(queue->dealloc_prod - queue->dealloc_cons >=
			MAX_PENDING_REQS);
		index = pending_index(queue->dealloc_prod);
		queue->dealloc_ring[index] = pending_idx;
		/* Sync with xenvif_tx_dealloc_action:
		 * insert idx then incr producer.
		 */
		smp_wmb();
		queue->dealloc_prod++;
	} while (ubuf);
	spin_unlock_irqrestore(&queue->callback_lock, flags);

	if (likely(zerocopy_success))
		queue->stats.tx_zerocopy_success++;
	else
		queue->stats.tx_zerocopy_fail++;
	xenvif_skb_zerocopy_complete(queue);
}