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
struct TYPE_2__ {int last_event; int /*<<< orphan*/  notifier; struct usb_otg* otg; } ;
struct usb_phy_generic {int vbus; TYPE_1__ phy; int /*<<< orphan*/  gpiod_vbus; } ;
struct usb_otg {int /*<<< orphan*/  gadget; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  OTG_STATE_B_IDLE ; 
 int /*<<< orphan*/  OTG_STATE_B_PERIPHERAL ; 
 int USB_EVENT_NONE ; 
 int USB_EVENT_VBUS ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nop_set_vbus_draw (struct usb_phy_generic*,int) ; 

__attribute__((used)) static irqreturn_t nop_gpio_vbus_thread(int irq, void *data)
{
	struct usb_phy_generic *nop = data;
	struct usb_otg *otg = nop->phy.otg;
	int vbus, status;

	vbus = gpiod_get_value(nop->gpiod_vbus);
	if ((vbus ^ nop->vbus) == 0)
		return IRQ_HANDLED;
	nop->vbus = vbus;

	if (vbus) {
		status = USB_EVENT_VBUS;
		otg->state = OTG_STATE_B_PERIPHERAL;
		nop->phy.last_event = status;

		/* drawing a "unit load" is *always* OK, except for OTG */
		nop_set_vbus_draw(nop, 100);

		atomic_notifier_call_chain(&nop->phy.notifier, status,
					   otg->gadget);
	} else {
		nop_set_vbus_draw(nop, 0);

		status = USB_EVENT_NONE;
		otg->state = OTG_STATE_B_IDLE;
		nop->phy.last_event = status;

		atomic_notifier_call_chain(&nop->phy.notifier, status,
					   otg->gadget);
	}
	return IRQ_HANDLED;
}