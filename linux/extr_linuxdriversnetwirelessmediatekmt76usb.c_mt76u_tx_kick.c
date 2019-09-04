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
struct mt76u_buf {int /*<<< orphan*/  urb; } ;
struct mt76_queue {size_t first; size_t tail; int ndesc; TYPE_1__* entry; } ;
struct mt76_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {struct mt76u_buf ubuf; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MT76_REMOVED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt76u_tx_kick(struct mt76_dev *dev, struct mt76_queue *q)
{
	struct mt76u_buf *buf;
	int err;

	while (q->first != q->tail) {
		buf = &q->entry[q->first].ubuf;
		err = usb_submit_urb(buf->urb, GFP_ATOMIC);
		if (err < 0) {
			if (err == -ENODEV)
				set_bit(MT76_REMOVED, &dev->state);
			else
				dev_err(dev->dev, "tx urb submit failed:%d\n",
					err);
			break;
		}
		q->first = (q->first + 1) % q->ndesc;
	}
}