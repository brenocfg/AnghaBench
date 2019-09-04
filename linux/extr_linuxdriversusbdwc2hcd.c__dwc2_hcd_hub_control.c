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
typedef  int /*<<< orphan*/  u16 ;
struct usb_hcd {int dummy; } ;

/* Variables and functions */
 int dwc2_hcd_hub_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_hcd_to_hsotg (struct usb_hcd*) ; 

__attribute__((used)) static int _dwc2_hcd_hub_control(struct usb_hcd *hcd, u16 typereq, u16 wvalue,
				 u16 windex, char *buf, u16 wlength)
{
	int retval = dwc2_hcd_hub_control(dwc2_hcd_to_hsotg(hcd), typereq,
					  wvalue, windex, buf, wlength);
	return retval;
}