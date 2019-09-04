#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mt76u_buf {int /*<<< orphan*/  done; } ;
struct mt76_queue {size_t head; int queued; int ndesc; int /*<<< orphan*/  lock; int /*<<< orphan*/  swq_queued; TYPE_3__* entry; } ;
struct TYPE_5__ {int /*<<< orphan*/  stat_work; } ;
struct mt76_dev {int /*<<< orphan*/  hw; TYPE_2__ usb; int /*<<< orphan*/  state; int /*<<< orphan*/  tx_wait; TYPE_1__* drv; struct mt76_queue* q_tx; } ;
struct TYPE_6__ {int schedule; struct mt76u_buf ubuf; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* tx_complete_skb ) (struct mt76_dev*,struct mt76_queue*,TYPE_3__*,int) ;} ;

/* Variables and functions */
 int IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  MT76_READING_STATS ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_wake_queue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mt76_txq_schedule (struct mt76_dev*,struct mt76_queue*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mt76_dev*,struct mt76_queue*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt76u_tx_tasklet(unsigned long data)
{
	struct mt76_dev *dev = (struct mt76_dev *)data;
	struct mt76u_buf *buf;
	struct mt76_queue *q;
	bool wake;
	int i;

	for (i = 0; i < IEEE80211_NUM_ACS; i++) {
		q = &dev->q_tx[i];

		spin_lock_bh(&q->lock);
		while (true) {
			buf = &q->entry[q->head].ubuf;
			if (!buf->done || !q->queued)
				break;

			dev->drv->tx_complete_skb(dev, q,
						  &q->entry[q->head],
						  false);

			if (q->entry[q->head].schedule) {
				q->entry[q->head].schedule = false;
				q->swq_queued--;
			}

			q->head = (q->head + 1) % q->ndesc;
			q->queued--;
		}
		mt76_txq_schedule(dev, q);
		wake = i < IEEE80211_NUM_ACS && q->queued < q->ndesc - 8;
		if (!q->queued)
			wake_up(&dev->tx_wait);

		spin_unlock_bh(&q->lock);

		if (!test_and_set_bit(MT76_READING_STATS, &dev->state))
			ieee80211_queue_delayed_work(dev->hw,
						     &dev->usb.stat_work,
						     msecs_to_jiffies(10));

		if (wake)
			ieee80211_wake_queue(dev->hw, i);
	}
}