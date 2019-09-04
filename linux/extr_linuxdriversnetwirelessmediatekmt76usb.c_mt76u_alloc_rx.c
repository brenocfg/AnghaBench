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
struct mt76_queue {int ndesc; int /*<<< orphan*/  buf_size; TYPE_1__* entry; int /*<<< orphan*/  lock; } ;
struct mt76_dev {int /*<<< orphan*/  dev; struct mt76_queue* q_rx; } ;
struct TYPE_2__ {int /*<<< orphan*/  ubuf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MT_NUM_RX_ENTRIES ; 
 size_t MT_RXQ_MAIN ; 
 int /*<<< orphan*/  MT_RX_BUF_SIZE ; 
 int MT_SG_MAX_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SKB_WITH_OVERHEAD (int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int mt76u_buf_alloc (struct mt76_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mt76u_check_sg (struct mt76_dev*) ; 
 int mt76u_submit_rx_buffers (struct mt76_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt76u_alloc_rx(struct mt76_dev *dev)
{
	struct mt76_queue *q = &dev->q_rx[MT_RXQ_MAIN];
	int i, err, nsgs;

	spin_lock_init(&q->lock);
	q->entry = devm_kcalloc(dev->dev,
				MT_NUM_RX_ENTRIES, sizeof(*q->entry),
				GFP_KERNEL);
	if (!q->entry)
		return -ENOMEM;

	if (mt76u_check_sg(dev)) {
		q->buf_size = MT_RX_BUF_SIZE;
		nsgs = MT_SG_MAX_SIZE;
	} else {
		q->buf_size = PAGE_SIZE;
		nsgs = 1;
	}

	for (i = 0; i < MT_NUM_RX_ENTRIES; i++) {
		err = mt76u_buf_alloc(dev, &q->entry[i].ubuf,
				      nsgs, q->buf_size,
				      SKB_WITH_OVERHEAD(q->buf_size),
				      GFP_KERNEL);
		if (err < 0)
			return err;
	}
	q->ndesc = MT_NUM_RX_ENTRIES;

	return mt76u_submit_rx_buffers(dev);
}