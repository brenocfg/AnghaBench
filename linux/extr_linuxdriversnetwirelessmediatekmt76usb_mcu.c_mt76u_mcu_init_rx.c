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
struct TYPE_2__ {int /*<<< orphan*/  res; int /*<<< orphan*/  cmpl; } ;
struct mt76_usb {TYPE_1__ mcu; } ;
struct mt76_dev {struct mt76_usb usb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MCU_RESP_URB_SIZE ; 
 int /*<<< orphan*/  MT_EP_IN_CMD_RESP ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int mt76u_buf_alloc (struct mt76_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76u_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76u_mcu_complete_urb ; 
 int mt76u_submit_buf (struct mt76_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mt76u_mcu_init_rx(struct mt76_dev *dev)
{
	struct mt76_usb *usb = &dev->usb;
	int err;

	err = mt76u_buf_alloc(dev, &usb->mcu.res, 1,
			      MCU_RESP_URB_SIZE, MCU_RESP_URB_SIZE,
			      GFP_KERNEL);
	if (err < 0)
		return err;

	err = mt76u_submit_buf(dev, USB_DIR_IN, MT_EP_IN_CMD_RESP,
			       &usb->mcu.res, GFP_KERNEL,
			       mt76u_mcu_complete_urb,
			       &usb->mcu.cmpl);
	if (err < 0)
		mt76u_buf_free(&usb->mcu.res);

	return err;
}