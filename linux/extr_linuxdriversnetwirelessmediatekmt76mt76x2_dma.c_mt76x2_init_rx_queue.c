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
struct TYPE_2__ {scalar_t__ regs; } ;
struct mt76x2_dev {TYPE_1__ mt76; } ;
struct mt76_queue {int ndesc; int buf_size; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_INT_RX_DONE (int) ; 
 int MT_RING_SIZE ; 
 scalar_t__ MT_RX_RING_BASE ; 
 int mt76_queue_alloc (struct mt76x2_dev*,struct mt76_queue*) ; 
 int /*<<< orphan*/  mt76x2_irq_enable (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt76x2_init_rx_queue(struct mt76x2_dev *dev, struct mt76_queue *q,
		     int idx, int n_desc, int bufsize)
{
	int ret;

	q->regs = dev->mt76.regs + MT_RX_RING_BASE + idx * MT_RING_SIZE;
	q->ndesc = n_desc;
	q->buf_size = bufsize;

	ret = mt76_queue_alloc(dev, q);
	if (ret)
		return ret;

	mt76x2_irq_enable(dev, MT_INT_RX_DONE(idx));

	return 0;
}