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
struct usb_gadget {int dummy; } ;
struct dwc2_hsotg {int /*<<< orphan*/  uphy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 struct dwc2_hsotg* to_hsotg (struct usb_gadget*) ; 
 int usb_phy_set_power (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int dwc2_hsotg_vbus_draw(struct usb_gadget *gadget, unsigned int mA)
{
	struct dwc2_hsotg *hsotg = to_hsotg(gadget);

	if (IS_ERR_OR_NULL(hsotg->uphy))
		return -ENOTSUPP;
	return usb_phy_set_power(hsotg->uphy, mA);
}