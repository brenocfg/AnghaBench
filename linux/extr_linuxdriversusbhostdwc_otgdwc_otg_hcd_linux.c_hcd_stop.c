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
struct usb_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  dwc_otg_hcd_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hcd_to_dwc_otg_hcd (struct usb_hcd*) ; 

void hcd_stop(struct usb_hcd *hcd)
{
	dwc_otg_hcd_t *dwc_otg_hcd = hcd_to_dwc_otg_hcd(hcd);

	dwc_otg_hcd_stop(dwc_otg_hcd);
}