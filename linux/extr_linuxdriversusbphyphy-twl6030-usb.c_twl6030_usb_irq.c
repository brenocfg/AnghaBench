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
struct twl6030_usb {int asleep; int linkstat; TYPE_1__* dev; int /*<<< orphan*/  usb3v3; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum musb_vbus_id_status { ____Placeholder_musb_vbus_id_status } musb_vbus_id_status ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROLLER_STAT1 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MUSB_UNKNOWN ; 
 int MUSB_VBUS_OFF ; 
 int MUSB_VBUS_VALID ; 
 int /*<<< orphan*/  STS_HW_CONDITIONS ; 
 int STS_USB_ID ; 
 int /*<<< orphan*/  TWL6030_MODULE_ID0 ; 
 int /*<<< orphan*/  TWL_MODULE_MAIN_CHARGE ; 
 int VBUS_DET ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int musb_mailbox (int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int twl6030_readb (struct twl6030_usb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t twl6030_usb_irq(int irq, void *_twl)
{
	struct twl6030_usb *twl = _twl;
	enum musb_vbus_id_status status = MUSB_UNKNOWN;
	u8 vbus_state, hw_state;
	int ret;

	hw_state = twl6030_readb(twl, TWL6030_MODULE_ID0, STS_HW_CONDITIONS);

	vbus_state = twl6030_readb(twl, TWL_MODULE_MAIN_CHARGE,
						CONTROLLER_STAT1);
	if (!(hw_state & STS_USB_ID)) {
		if (vbus_state & VBUS_DET) {
			ret = regulator_enable(twl->usb3v3);
			if (ret)
				dev_err(twl->dev, "Failed to enable usb3v3\n");

			twl->asleep = 1;
			status = MUSB_VBUS_VALID;
			twl->linkstat = status;
			ret = musb_mailbox(status);
			if (ret)
				twl->linkstat = MUSB_UNKNOWN;
		} else {
			if (twl->linkstat != MUSB_UNKNOWN) {
				status = MUSB_VBUS_OFF;
				twl->linkstat = status;
				ret = musb_mailbox(status);
				if (ret)
					twl->linkstat = MUSB_UNKNOWN;
				if (twl->asleep) {
					regulator_disable(twl->usb3v3);
					twl->asleep = 0;
				}
			}
		}
	}
	sysfs_notify(&twl->dev->kobj, NULL, "vbus");

	return IRQ_HANDLED;
}