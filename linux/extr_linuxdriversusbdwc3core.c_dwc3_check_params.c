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
struct TYPE_2__ {int /*<<< orphan*/  hwparams3; } ;
struct dwc3 {int imod_interval; scalar_t__ revision; int maximum_speed; TYPE_1__ hwparams; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GHWPARAMS3_SSPHY_IFC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC3_GHWPARAMS3_SSPHY_IFC_GEN2 ; 
 scalar_t__ DWC3_REVISION_300A ; 
#define  USB_SPEED_FULL 133 
#define  USB_SPEED_HIGH 132 
#define  USB_SPEED_LOW 131 
#define  USB_SPEED_SUPER 130 
#define  USB_SPEED_SUPER_PLUS 129 
#define  USB_SPEED_UNKNOWN 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  dwc3_has_imod (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_is_usb31 (struct dwc3*) ; 

__attribute__((used)) static void dwc3_check_params(struct dwc3 *dwc)
{
	struct device *dev = dwc->dev;

	/* Check for proper value of imod_interval */
	if (dwc->imod_interval && !dwc3_has_imod(dwc)) {
		dev_warn(dwc->dev, "Interrupt moderation not supported\n");
		dwc->imod_interval = 0;
	}

	/*
	 * Workaround for STAR 9000961433 which affects only version
	 * 3.00a of the DWC_usb3 core. This prevents the controller
	 * interrupt from being masked while handling events. IMOD
	 * allows us to work around this issue. Enable it for the
	 * affected version.
	 */
	if (!dwc->imod_interval &&
	    (dwc->revision == DWC3_REVISION_300A))
		dwc->imod_interval = 1;

	/* Check the maximum_speed parameter */
	switch (dwc->maximum_speed) {
	case USB_SPEED_LOW:
	case USB_SPEED_FULL:
	case USB_SPEED_HIGH:
	case USB_SPEED_SUPER:
	case USB_SPEED_SUPER_PLUS:
		break;
	default:
		dev_err(dev, "invalid maximum_speed parameter %d\n",
			dwc->maximum_speed);
		/* fall through */
	case USB_SPEED_UNKNOWN:
		/* default to superspeed */
		dwc->maximum_speed = USB_SPEED_SUPER;

		/*
		 * default to superspeed plus if we are capable.
		 */
		if (dwc3_is_usb31(dwc) &&
		    (DWC3_GHWPARAMS3_SSPHY_IFC(dwc->hwparams.hwparams3) ==
		     DWC3_GHWPARAMS3_SSPHY_IFC_GEN2))
			dwc->maximum_speed = USB_SPEED_SUPER_PLUS;

		break;
	}
}