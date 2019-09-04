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
struct mv_otg {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void mv_otg_start_host(struct mv_otg *mvotg, int on)
{
#ifdef CONFIG_USB
	struct usb_otg *otg = mvotg->phy.otg;
	struct usb_hcd *hcd;

	if (!otg->host)
		return;

	dev_info(&mvotg->pdev->dev, "%s host\n", on ? "start" : "stop");

	hcd = bus_to_hcd(otg->host);

	if (on) {
		usb_add_hcd(hcd, hcd->irq, IRQF_SHARED);
		device_wakeup_enable(hcd->self.controller);
	} else {
		usb_remove_hcd(hcd);
	}
#endif /* CONFIG_USB */
}