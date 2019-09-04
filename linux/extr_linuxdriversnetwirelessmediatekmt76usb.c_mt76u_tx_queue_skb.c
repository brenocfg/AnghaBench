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
typedef  size_t u8 ;
typedef  size_t u16 ;
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct mt76u_buf {int done; int /*<<< orphan*/  urb; } ;
struct mt76_wcid {int dummy; } ;
struct mt76_queue {size_t tail; int queued; int ndesc; TYPE_3__* entry; int /*<<< orphan*/  hw_idx; } ;
struct TYPE_5__ {int /*<<< orphan*/ * out_ep; } ;
struct mt76_dev {TYPE_2__ usb; TYPE_1__* drv; int /*<<< orphan*/  dev; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_6__ {struct sk_buff* skb; struct mt76u_buf ubuf; } ;
struct TYPE_4__ {int (* tx_prepare_skb ) (struct mt76_dev*,int /*<<< orphan*/ *,struct sk_buff*,struct mt76_queue*,struct mt76_wcid*,struct ieee80211_sta*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ENOSPC ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  mt76u_complete_tx ; 
 int mt76u_tx_build_sg (struct sk_buff*,int /*<<< orphan*/ ) ; 
 size_t q2ep (int /*<<< orphan*/ ) ; 
 int stub1 (struct mt76_dev*,int /*<<< orphan*/ *,struct sk_buff*,struct mt76_queue*,struct mt76_wcid*,struct ieee80211_sta*,int /*<<< orphan*/ *) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,struct usb_device*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mt76u_buf*) ; 
 unsigned int usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt76u_tx_queue_skb(struct mt76_dev *dev, struct mt76_queue *q,
		   struct sk_buff *skb, struct mt76_wcid *wcid,
		   struct ieee80211_sta *sta)
{
	struct usb_interface *intf = to_usb_interface(dev->dev);
	struct usb_device *udev = interface_to_usbdev(intf);
	u8 ep = q2ep(q->hw_idx);
	struct mt76u_buf *buf;
	u16 idx = q->tail;
	unsigned int pipe;
	int err;

	if (q->queued == q->ndesc)
		return -ENOSPC;

	err = dev->drv->tx_prepare_skb(dev, NULL, skb, q, wcid, sta, NULL);
	if (err < 0)
		return err;

	buf = &q->entry[idx].ubuf;
	buf->done = false;

	err = mt76u_tx_build_sg(skb, buf->urb);
	if (err < 0)
		return err;

	pipe = usb_sndbulkpipe(udev, dev->usb.out_ep[ep]);
	usb_fill_bulk_urb(buf->urb, udev, pipe, NULL, skb->len,
			  mt76u_complete_tx, buf);

	q->tail = (q->tail + 1) % q->ndesc;
	q->entry[idx].skb = skb;
	q->queued++;

	return idx;
}