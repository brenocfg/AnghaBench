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
struct xhci_virt_device {struct usb_device* udev; } ;
struct xhci_hcd {int xhc_state; struct xhci_virt_device** devs; } ;
struct usb_host_endpoint {int dummy; } ;
struct usb_hcd {int dummy; } ;
struct usb_device {size_t slot_id; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int XHCI_STATE_HALTED ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,char const*) ; 

__attribute__((used)) static int xhci_check_args(struct usb_hcd *hcd, struct usb_device *udev,
		struct usb_host_endpoint *ep, int check_ep, bool check_virt_dev,
		const char *func) {
	struct xhci_hcd	*xhci;
	struct xhci_virt_device	*virt_dev;

	if (!hcd || (check_ep && !ep) || !udev) {
		pr_debug("xHCI %s called with invalid args\n", func);
		return -EINVAL;
	}
	if (!udev->parent) {
		pr_debug("xHCI %s called for root hub\n", func);
		return 0;
	}

	xhci = hcd_to_xhci(hcd);
	if (check_virt_dev) {
		if (!udev->slot_id || !xhci->devs[udev->slot_id]) {
			xhci_dbg(xhci, "xHCI %s called with unaddressed device\n",
					func);
			return -EINVAL;
		}

		virt_dev = xhci->devs[udev->slot_id];
		if (virt_dev->udev != udev) {
			xhci_dbg(xhci, "xHCI %s called with udev and "
					  "virt_dev does not match\n", func);
			return -EINVAL;
		}
	}

	if (xhci->xhc_state & XHCI_STATE_HALTED)
		return -ENODEV;

	return 1;
}