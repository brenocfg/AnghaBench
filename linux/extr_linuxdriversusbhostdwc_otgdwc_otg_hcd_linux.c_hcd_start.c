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
struct usb_hcd {int /*<<< orphan*/  state; } ;
struct usb_bus {scalar_t__ root_hub; } ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HC_STATE_RUNNING ; 
 scalar_t__ dwc_otg_hcd_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hcd_fops ; 
 struct usb_bus* hcd_to_bus (struct usb_hcd*) ; 
 int /*<<< orphan*/ * hcd_to_dwc_otg_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_hcd_resume_root_hub (struct usb_hcd*) ; 

int hcd_start(struct usb_hcd *hcd)
{
	dwc_otg_hcd_t *dwc_otg_hcd = hcd_to_dwc_otg_hcd(hcd);
	struct usb_bus *bus;

	DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD START\n");
	bus = hcd_to_bus(hcd);

	hcd->state = HC_STATE_RUNNING;
	if (dwc_otg_hcd_start(dwc_otg_hcd, &hcd_fops)) {
		return 0;
	}

	/* Initialize and connect root hub if one is not already attached */
	if (bus->root_hub) {
		DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD Has Root Hub\n");
		/* Inform the HUB driver to resume. */
		usb_hcd_resume_root_hub(hcd);
	}

	return 0;
}