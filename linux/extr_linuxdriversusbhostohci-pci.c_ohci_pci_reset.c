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
struct TYPE_2__ {scalar_t__ controller; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ohci_hcd {int /*<<< orphan*/  hc_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI_CTRL_RWC ; 
 scalar_t__ device_can_wakeup (int /*<<< orphan*/ *) ; 
 struct ohci_hcd* hcd_to_ohci (struct usb_hcd*) ; 
 int /*<<< orphan*/  ohci_pci_quirks ; 
 int ohci_setup (struct usb_hcd*) ; 
 struct pci_device_id* pci_match_id (int /*<<< orphan*/ ,struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (scalar_t__) ; 

__attribute__((used)) static int ohci_pci_reset (struct usb_hcd *hcd)
{
	struct ohci_hcd	*ohci = hcd_to_ohci (hcd);
	struct pci_dev *pdev = to_pci_dev(hcd->self.controller);
	int ret = 0;

	if (hcd->self.controller) {
		const struct pci_device_id *quirk_id;

		quirk_id = pci_match_id(ohci_pci_quirks, pdev);
		if (quirk_id != NULL) {
			int (*quirk)(struct usb_hcd *ohci);
			quirk = (void *)quirk_id->driver_data;
			ret = quirk(hcd);
		}
	}

	if (ret == 0)
		ret = ohci_setup(hcd);
	/*
	* After ohci setup RWC may not be set for add-in PCI cards.
	* This transfers PCI PM wakeup capabilities.
	*/
	if (device_can_wakeup(&pdev->dev))
		ohci->hc_control |= OHCI_CTRL_RWC;
	return ret;
}