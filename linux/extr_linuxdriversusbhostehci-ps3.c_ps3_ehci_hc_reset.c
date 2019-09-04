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
struct usb_hcd {int /*<<< orphan*/  regs; } ;
struct ehci_hcd {int big_endian_mmio; int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int ehci_setup (struct usb_hcd*) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  ps3_ehci_setup_insnreg (struct ehci_hcd*) ; 

__attribute__((used)) static int ps3_ehci_hc_reset(struct usb_hcd *hcd)
{
	int result;
	struct ehci_hcd *ehci = hcd_to_ehci(hcd);

	ehci->big_endian_mmio = 1;
	ehci->caps = hcd->regs;

	result = ehci_setup(hcd);
	if (result)
		return result;

	ps3_ehci_setup_insnreg(ehci);

	return result;
}