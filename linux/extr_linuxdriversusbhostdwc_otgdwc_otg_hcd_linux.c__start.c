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
struct TYPE_2__ {int /*<<< orphan*/  is_b_host; } ;
struct usb_hcd {TYPE_1__ self; } ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  dwc_otg_hcd_is_b_host (int /*<<< orphan*/ *) ; 
 struct usb_hcd* dwc_otg_hcd_to_hcd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hcd_start (struct usb_hcd*) ; 

__attribute__((used)) static int _start(dwc_otg_hcd_t * hcd)
{
	struct usb_hcd *usb_hcd = dwc_otg_hcd_to_hcd(hcd);

	usb_hcd->self.is_b_host = dwc_otg_hcd_is_b_host(hcd);
	hcd_start(usb_hcd);

	return 0;
}