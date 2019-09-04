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
struct dwc3 {int /*<<< orphan*/  xhci; int /*<<< orphan*/  dev; int /*<<< orphan*/  usb3_generic_phy; int /*<<< orphan*/  usb2_generic_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_remove_lookup (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

void dwc3_host_exit(struct dwc3 *dwc)
{
	phy_remove_lookup(dwc->usb2_generic_phy, "usb2-phy",
			  dev_name(dwc->dev));
	phy_remove_lookup(dwc->usb3_generic_phy, "usb3-phy",
			  dev_name(dwc->dev));
	platform_device_unregister(dwc->xhci);
}