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
struct usb_hcd {int /*<<< orphan*/  flags; int /*<<< orphan*/  state; int /*<<< orphan*/  irq; } ;
struct dwc2_hsotg {int /*<<< orphan*/  lock; int /*<<< orphan*/  lx_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC2_L3 ; 
 int /*<<< orphan*/  HCD_FLAG_HW_ACCESSIBLE ; 
 int /*<<< orphan*/  HC_STATE_HALT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc2_disable_host_interrupts (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_hcd_disconnect (struct dwc2_hsotg*,int) ; 
 int /*<<< orphan*/  dwc2_hcd_stop (struct dwc2_hsotg*) ; 
 struct dwc2_hsotg* dwc2_hcd_to_hsotg (struct usb_hcd*) ; 
 int /*<<< orphan*/  dwc2_vbus_supply_exit (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void _dwc2_hcd_stop(struct usb_hcd *hcd)
{
	struct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	unsigned long flags;

	/* Turn off all host-specific interrupts */
	dwc2_disable_host_interrupts(hsotg);

	/* Wait for interrupt processing to finish */
	synchronize_irq(hcd->irq);

	spin_lock_irqsave(&hsotg->lock, flags);
	/* Ensure hcd is disconnected */
	dwc2_hcd_disconnect(hsotg, true);
	dwc2_hcd_stop(hsotg);
	hsotg->lx_state = DWC2_L3;
	hcd->state = HC_STATE_HALT;
	clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
	spin_unlock_irqrestore(&hsotg->lock, flags);

	dwc2_vbus_supply_exit(hsotg);

	usleep_range(1000, 3000);
}