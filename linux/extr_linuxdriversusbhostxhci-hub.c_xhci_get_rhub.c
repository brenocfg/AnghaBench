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
struct xhci_hub {int dummy; } ;
struct xhci_hcd {struct xhci_hub usb2_rhub; struct xhci_hub usb3_rhub; } ;
struct usb_hcd {scalar_t__ speed; } ;

/* Variables and functions */
 scalar_t__ HCD_USB3 ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 

struct xhci_hub *xhci_get_rhub(struct usb_hcd *hcd)
{
	struct xhci_hcd	*xhci = hcd_to_xhci(hcd);

	if (hcd->speed >= HCD_USB3)
		return &xhci->usb3_rhub;
	return &xhci->usb2_rhub;
}