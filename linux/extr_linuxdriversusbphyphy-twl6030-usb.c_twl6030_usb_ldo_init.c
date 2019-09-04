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
struct twl6030_usb {int /*<<< orphan*/  usb3v3; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TWL6030_BACKUP_REG ; 
 int /*<<< orphan*/  TWL6030_CFG_LDO_PD2 ; 
 int /*<<< orphan*/  TWL6030_MISC2 ; 
 int /*<<< orphan*/  TWL6030_MODULE_ID0 ; 
 int /*<<< orphan*/  TWL_MODULE_USB ; 
 int /*<<< orphan*/  USB_ID_CTRL_SET ; 
 int /*<<< orphan*/  USB_VBUS_CTRL_SET ; 
 int /*<<< orphan*/  regulator_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  twl6030_writeb (struct twl6030_usb*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6030_usb_ldo_init(struct twl6030_usb *twl)
{
	/* Set to OTG_REV 1.3 and turn on the ID_WAKEUP_COMP */
	twl6030_writeb(twl, TWL6030_MODULE_ID0, 0x1, TWL6030_BACKUP_REG);

	/* Program CFG_LDO_PD2 register and set VUSB bit */
	twl6030_writeb(twl, TWL6030_MODULE_ID0, 0x1, TWL6030_CFG_LDO_PD2);

	/* Program MISC2 register and set bit VUSB_IN_VBAT */
	twl6030_writeb(twl, TWL6030_MODULE_ID0, 0x10, TWL6030_MISC2);

	twl->usb3v3 = regulator_get(twl->dev, "usb");
	if (IS_ERR(twl->usb3v3))
		return -ENODEV;

	/* Program the USB_VBUS_CTRL_SET and set VBUS_ACT_COMP bit */
	twl6030_writeb(twl, TWL_MODULE_USB, 0x4, USB_VBUS_CTRL_SET);

	/*
	 * Program the USB_ID_CTRL_SET register to enable GND drive
	 * and the ID comparators
	 */
	twl6030_writeb(twl, TWL_MODULE_USB, 0x14, USB_ID_CTRL_SET);

	return 0;
}