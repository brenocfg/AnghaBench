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
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct musb {int /*<<< orphan*/  isr; int /*<<< orphan*/  controller; TYPE_1__ nb; int /*<<< orphan*/  xceiv; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_PHY_TYPE_USB2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  musb_otg_notifications ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  usb_get_phy (int /*<<< orphan*/ ) ; 
 int usb_register_notifier (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ux500_musb_interrupt ; 

__attribute__((used)) static int ux500_musb_init(struct musb *musb)
{
	int status;

	musb->xceiv = usb_get_phy(USB_PHY_TYPE_USB2);
	if (IS_ERR_OR_NULL(musb->xceiv)) {
		pr_err("HS USB OTG: no transceiver configured\n");
		return -EPROBE_DEFER;
	}

	musb->nb.notifier_call = musb_otg_notifications;
	status = usb_register_notifier(musb->xceiv, &musb->nb);
	if (status < 0) {
		dev_dbg(musb->controller, "notification register failed\n");
		return status;
	}

	musb->isr = ux500_musb_interrupt;

	return 0;
}