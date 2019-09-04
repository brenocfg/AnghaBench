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
struct TYPE_2__ {int /*<<< orphan*/  resp; int /*<<< orphan*/  resp_cmpl; } ;
struct mt76x0_dev {TYPE_1__ mcu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MCU_RESP_URB_SIZE ; 
 int /*<<< orphan*/  MT_EP_IN_CMD_RESP ; 
 int /*<<< orphan*/  Q_SELECT ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x0_complete_urb ; 
 int mt76x0_mcu_function_select (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mt76x0_usb_alloc_buf (struct mt76x0_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x0_usb_free_buf (struct mt76x0_dev*,int /*<<< orphan*/ *) ; 
 int mt76x0_usb_submit_buf (struct mt76x0_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mt76x0_mcu_cmd_init(struct mt76x0_dev *dev)
{
	int ret;

	ret = mt76x0_mcu_function_select(dev, Q_SELECT, 1);
	if (ret)
		return ret;

	init_completion(&dev->mcu.resp_cmpl);
	if (mt76x0_usb_alloc_buf(dev, MCU_RESP_URB_SIZE, &dev->mcu.resp)) {
		mt76x0_usb_free_buf(dev, &dev->mcu.resp);
		return -ENOMEM;
	}

	ret = mt76x0_usb_submit_buf(dev, USB_DIR_IN, MT_EP_IN_CMD_RESP,
				     &dev->mcu.resp, GFP_KERNEL,
				     mt76x0_complete_urb, &dev->mcu.resp_cmpl);
	if (ret) {
		mt76x0_usb_free_buf(dev, &dev->mcu.resp);
		return ret;
	}

	return 0;
}