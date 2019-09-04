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
typedef  int u8 ;
typedef  int u32 ;
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int msg_seq; int /*<<< orphan*/  mutex; } ;
struct mt76_usb {TYPE_1__ mcu; int /*<<< orphan*/ * out_ep; } ;
struct mt76_dev {int /*<<< orphan*/  state; struct mt76_usb usb; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TX_PORT ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT76_REMOVED ; 
 size_t MT_EP_OUT_INBAND_CMD ; 
 int /*<<< orphan*/  MT_MCU_MSG_CMD_SEQ ; 
 int /*<<< orphan*/  MT_MCU_MSG_CMD_TYPE ; 
 int MT_MCU_MSG_TYPE_CMD ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int mt76u_mcu_wait_resp (struct mt76_dev*,int) ; 
 int mt76u_skb_dma_info (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 
 int usb_bulk_msg (struct usb_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 unsigned int usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

int mt76u_mcu_send_msg(struct mt76_dev *dev, struct sk_buff *skb,
		       int cmd, bool wait_resp)
{
	struct usb_interface *intf = to_usb_interface(dev->dev);
	struct usb_device *udev = interface_to_usbdev(intf);
	struct mt76_usb *usb = &dev->usb;
	unsigned int pipe;
	int ret, sent;
	u8 seq = 0;
	u32 info;

	if (test_bit(MT76_REMOVED, &dev->state))
		return 0;

	mutex_lock(&usb->mcu.mutex);

	pipe = usb_sndbulkpipe(udev, usb->out_ep[MT_EP_OUT_INBAND_CMD]);
	if (wait_resp) {
		seq = ++usb->mcu.msg_seq & 0xf;
		if (!seq)
			seq = ++usb->mcu.msg_seq & 0xf;
	}

	info = FIELD_PREP(MT_MCU_MSG_CMD_SEQ, seq) |
	       FIELD_PREP(MT_MCU_MSG_CMD_TYPE, cmd) |
	       MT_MCU_MSG_TYPE_CMD;
	ret = mt76u_skb_dma_info(skb, CPU_TX_PORT, info);
	if (ret)
		goto out;

	ret = usb_bulk_msg(udev, pipe, skb->data, skb->len, &sent, 500);
	if (ret)
		goto out;

	if (wait_resp)
		ret = mt76u_mcu_wait_resp(dev, seq);

out:
	mutex_unlock(&usb->mcu.mutex);

	consume_skb(skb);

	return ret;
}