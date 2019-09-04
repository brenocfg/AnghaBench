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
struct mt76_queue_entry {scalar_t__ txwi; scalar_t__ skb; scalar_t__ schedule; } ;
struct mt76_queue {int ndesc; int queued; int tail; int /*<<< orphan*/  lock; TYPE_2__* regs; int /*<<< orphan*/  swq_queued; } ;
struct mt76_dev {int /*<<< orphan*/  hw; int /*<<< orphan*/  tx_wait; TYPE_1__* drv; struct mt76_queue* q_tx; } ;
typedef  enum mt76_txq_id { ____Placeholder_mt76_txq_id } mt76_txq_id ;
struct TYPE_4__ {int /*<<< orphan*/  dma_idx; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* tx_complete_skb ) (struct mt76_dev*,struct mt76_queue*,struct mt76_queue_entry*,int) ;} ;

/* Variables and functions */
 int IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  ieee80211_wake_queue (int /*<<< orphan*/ ,int) ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_dma_sync_idx (struct mt76_dev*,struct mt76_queue*) ; 
 int /*<<< orphan*/  mt76_dma_tx_cleanup_idx (struct mt76_dev*,struct mt76_queue*,int,struct mt76_queue_entry*) ; 
 int /*<<< orphan*/  mt76_put_txwi (struct mt76_dev*,scalar_t__) ; 
 int /*<<< orphan*/  mt76_txq_schedule (struct mt76_dev*,struct mt76_queue*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mt76_dev*,struct mt76_queue*,struct mt76_queue_entry*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt76_dma_tx_cleanup(struct mt76_dev *dev, enum mt76_txq_id qid, bool flush)
{
	struct mt76_queue *q = &dev->q_tx[qid];
	struct mt76_queue_entry entry;
	bool wake = false;
	int last;

	if (!q->ndesc)
		return;

	spin_lock_bh(&q->lock);
	if (flush)
		last = -1;
	else
		last = ioread32(&q->regs->dma_idx);

	while (q->queued && q->tail != last) {
		mt76_dma_tx_cleanup_idx(dev, q, q->tail, &entry);
		if (entry.schedule)
			q->swq_queued--;

		if (entry.skb)
			dev->drv->tx_complete_skb(dev, q, &entry, flush);

		if (entry.txwi) {
			mt76_put_txwi(dev, entry.txwi);
			wake = true;
		}

		q->tail = (q->tail + 1) % q->ndesc;
		q->queued--;

		if (!flush && q->tail == last)
			last = ioread32(&q->regs->dma_idx);
	}

	if (!flush)
		mt76_txq_schedule(dev, q);
	else
		mt76_dma_sync_idx(dev, q);

	wake = wake && qid < IEEE80211_NUM_ACS && q->queued < q->ndesc - 8;

	if (!q->queued)
		wake_up(&dev->tx_wait);

	spin_unlock_bh(&q->lock);

	if (wake)
		ieee80211_wake_queue(dev->hw, qid);
}