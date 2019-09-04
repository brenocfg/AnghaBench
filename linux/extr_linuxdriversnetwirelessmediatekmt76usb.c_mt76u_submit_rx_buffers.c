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
struct mt76_queue {int ndesc; int /*<<< orphan*/  lock; scalar_t__ queued; scalar_t__ tail; scalar_t__ head; TYPE_1__* entry; } ;
struct mt76_dev {struct mt76_queue* q_rx; } ;
struct TYPE_2__ {int /*<<< orphan*/  ubuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MT_EP_IN_PKT_RX ; 
 size_t MT_RXQ_MAIN ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  mt76u_complete_rx ; 
 int mt76u_submit_buf (struct mt76_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mt76_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int mt76u_submit_rx_buffers(struct mt76_dev *dev)
{
	struct mt76_queue *q = &dev->q_rx[MT_RXQ_MAIN];
	unsigned long flags;
	int i, err = 0;

	spin_lock_irqsave(&q->lock, flags);
	for (i = 0; i < q->ndesc; i++) {
		err = mt76u_submit_buf(dev, USB_DIR_IN, MT_EP_IN_PKT_RX,
				       &q->entry[i].ubuf, GFP_ATOMIC,
				       mt76u_complete_rx, dev);
		if (err < 0)
			break;
	}
	q->head = q->tail = 0;
	q->queued = 0;
	spin_unlock_irqrestore(&q->lock, flags);

	return err;
}