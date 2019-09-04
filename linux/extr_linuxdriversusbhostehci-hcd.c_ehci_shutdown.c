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
struct usb_hcd {int dummy; } ;
struct ehci_hcd {int shutdown; int /*<<< orphan*/  hrtimer; int /*<<< orphan*/  lock; scalar_t__ enabled_hrtimer_events; int /*<<< orphan*/  rh_state; int /*<<< orphan*/  sbrn; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_RH_STOPPING ; 
 int /*<<< orphan*/  ehci_silence_controller (struct ehci_hcd*) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ehci_shutdown(struct usb_hcd *hcd)
{
	struct ehci_hcd	*ehci = hcd_to_ehci(hcd);

	/**
	 * Protect the system from crashing at system shutdown in cases where
	 * usb host is not added yet from OTG controller driver.
	 * As ehci_setup() not done yet, so stop accessing registers or
	 * variables initialized in ehci_setup()
	 */
	if (!ehci->sbrn)
		return;

	spin_lock_irq(&ehci->lock);
	ehci->shutdown = true;
	ehci->rh_state = EHCI_RH_STOPPING;
	ehci->enabled_hrtimer_events = 0;
	spin_unlock_irq(&ehci->lock);

	ehci_silence_controller(ehci);

	hrtimer_cancel(&ehci->hrtimer);
}