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
struct usb_hcd {int has_tt; int /*<<< orphan*/  regs; } ;
struct ehci_hcd {int big_endian_mmio; int big_endian_desc; int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int ehci_setup (struct usb_hcd*) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_hcd_tdi_set_mode (struct ehci_hcd*) ; 

__attribute__((used)) static int ehci_msp_setup(struct usb_hcd *hcd)
{
	struct ehci_hcd		*ehci = hcd_to_ehci(hcd);
	int			retval;

	ehci->big_endian_mmio = 1;
	ehci->big_endian_desc = 1;

	ehci->caps = hcd->regs;
	hcd->has_tt = 1;

	retval = ehci_setup(hcd);
	if (retval)
		return retval;

	usb_hcd_tdi_set_mode(ehci);

	return retval;
}