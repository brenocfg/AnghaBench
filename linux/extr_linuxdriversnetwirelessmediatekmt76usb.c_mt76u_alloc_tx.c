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
struct scatterlist {int dummy; } ;
struct mt76u_buf {TYPE_1__* urb; struct mt76_dev* dev; } ;
struct mt76_queue {int ndesc; TYPE_2__* entry; int /*<<< orphan*/  hw_idx; int /*<<< orphan*/  swq; int /*<<< orphan*/  lock; } ;
struct mt76_dev {int /*<<< orphan*/  dev; struct mt76_queue* q_tx; } ;
struct TYPE_4__ {struct mt76u_buf ubuf; } ;
struct TYPE_3__ {int /*<<< orphan*/  sg; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MT_NUM_TX_ENTRIES ; 
 int MT_SG_MAX_SIZE ; 
 TYPE_2__* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kzalloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q2hwq (int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt76u_alloc_tx(struct mt76_dev *dev)
{
	struct mt76u_buf *buf;
	struct mt76_queue *q;
	size_t size;
	int i, j;

	size = MT_SG_MAX_SIZE * sizeof(struct scatterlist);
	for (i = 0; i < IEEE80211_NUM_ACS; i++) {
		q = &dev->q_tx[i];
		spin_lock_init(&q->lock);
		INIT_LIST_HEAD(&q->swq);
		q->hw_idx = q2hwq(i);

		q->entry = devm_kcalloc(dev->dev,
					MT_NUM_TX_ENTRIES, sizeof(*q->entry),
					GFP_KERNEL);
		if (!q->entry)
			return -ENOMEM;

		q->ndesc = MT_NUM_TX_ENTRIES;
		for (j = 0; j < q->ndesc; j++) {
			buf = &q->entry[j].ubuf;
			buf->dev = dev;

			buf->urb = usb_alloc_urb(0, GFP_KERNEL);
			if (!buf->urb)
				return -ENOMEM;

			buf->urb->sg = devm_kzalloc(dev->dev, size, GFP_KERNEL);
			if (!buf->urb->sg)
				return -ENOMEM;
		}
	}
	return 0;
}