#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct usb_device {int dummy; } ;
struct rsi_hw {scalar_t__ rsi_dev; } ;
struct rsi_91x_usbdev {struct usb_device* usbdev; } ;

/* Variables and functions */
 int rsi_usb_reg_read (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsi_usb_master_reg_read(struct rsi_hw *adapter, u32 reg,
				   u32 *value, u16 len)
{
	struct usb_device *usbdev =
		((struct rsi_91x_usbdev *)adapter->rsi_dev)->usbdev;
	u16 temp;
	int ret;

	ret = rsi_usb_reg_read(usbdev, reg, &temp, len);
	if (ret < 0)
		return ret;
	*value = temp;

	return 0;
}