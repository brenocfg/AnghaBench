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
struct dwc2_hsotg {scalar_t__ dr_mode; int /*<<< orphan*/  dev; } ;
typedef  enum usb_dr_mode { ____Placeholder_usb_dr_mode } usb_dr_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_USB_DWC2_HOST ; 
 int /*<<< orphan*/  CONFIG_USB_DWC2_PERIPHERAL ; 
 int EINVAL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int USB_DR_MODE_HOST ; 
 scalar_t__ USB_DR_MODE_OTG ; 
 int USB_DR_MODE_PERIPHERAL ; 
 scalar_t__ USB_DR_MODE_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ dwc2_hw_is_device (struct dwc2_hsotg*) ; 
 scalar_t__ dwc2_hw_is_host (struct dwc2_hsotg*) ; 
 scalar_t__ usb_get_dr_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc2_get_dr_mode(struct dwc2_hsotg *hsotg)
{
	enum usb_dr_mode mode;

	hsotg->dr_mode = usb_get_dr_mode(hsotg->dev);
	if (hsotg->dr_mode == USB_DR_MODE_UNKNOWN)
		hsotg->dr_mode = USB_DR_MODE_OTG;

	mode = hsotg->dr_mode;

	if (dwc2_hw_is_device(hsotg)) {
		if (IS_ENABLED(CONFIG_USB_DWC2_HOST)) {
			dev_err(hsotg->dev,
				"Controller does not support host mode.\n");
			return -EINVAL;
		}
		mode = USB_DR_MODE_PERIPHERAL;
	} else if (dwc2_hw_is_host(hsotg)) {
		if (IS_ENABLED(CONFIG_USB_DWC2_PERIPHERAL)) {
			dev_err(hsotg->dev,
				"Controller does not support device mode.\n");
			return -EINVAL;
		}
		mode = USB_DR_MODE_HOST;
	} else {
		if (IS_ENABLED(CONFIG_USB_DWC2_HOST))
			mode = USB_DR_MODE_HOST;
		else if (IS_ENABLED(CONFIG_USB_DWC2_PERIPHERAL))
			mode = USB_DR_MODE_PERIPHERAL;
	}

	if (mode != hsotg->dr_mode) {
		dev_warn(hsotg->dev,
			 "Configuration mismatch. dr_mode forced to %s\n",
			mode == USB_DR_MODE_HOST ? "host" : "device");

		hsotg->dr_mode = mode;
	}

	return 0;
}