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
typedef  size_t u8 ;
struct usb_device {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct mt76x0_tx_queue {int entries; int used; size_t end; struct mt76x0_dma_buf_tx* e; } ;
struct mt76x0_dma_buf_tx {int /*<<< orphan*/  urb; struct sk_buff* skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; int /*<<< orphan*/  dev; int /*<<< orphan*/  state; } ;
struct mt76x0_dev {int /*<<< orphan*/  tx_lock; TYPE_1__ mt76; struct mt76x0_tx_queue* tx_q; int /*<<< orphan*/ * out_ep; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MT76_REMOVED ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ieee80211_stop_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x0_complete_tx ; 
 struct usb_device* mt76x0_to_usb_dev (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,struct usb_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mt76x0_tx_queue*) ; 
 unsigned int usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt76x0_dma_submit_tx(struct mt76x0_dev *dev,
				 struct sk_buff *skb, u8 ep)
{
	struct usb_device *usb_dev = mt76x0_to_usb_dev(dev);
	unsigned snd_pipe = usb_sndbulkpipe(usb_dev, dev->out_ep[ep]);
	struct mt76x0_dma_buf_tx *e;
	struct mt76x0_tx_queue *q = &dev->tx_q[ep];
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&dev->tx_lock, flags);

	if (WARN_ON_ONCE(q->entries <= q->used)) {
		ret = -ENOSPC;
		goto out;
	}

	e = &q->e[q->end];
	e->skb = skb;
	usb_fill_bulk_urb(e->urb, usb_dev, snd_pipe, skb->data, skb->len,
			  mt76x0_complete_tx, q);
	ret = usb_submit_urb(e->urb, GFP_ATOMIC);
	if (ret) {
		/* Special-handle ENODEV from TX urb submission because it will
		 * often be the first ENODEV we see after device is removed.
		 */
		if (ret == -ENODEV)
			set_bit(MT76_REMOVED, &dev->mt76.state);
		else
			dev_err(dev->mt76.dev, "Error: TX urb submit failed:%d\n",
				ret);
		goto out;
	}

	q->end = (q->end + 1) % q->entries;
	q->used++;

	if (q->used >= q->entries)
		ieee80211_stop_queue(dev->mt76.hw, skb_get_queue_mapping(skb));
out:
	spin_unlock_irqrestore(&dev->tx_lock, flags);

	return ret;
}