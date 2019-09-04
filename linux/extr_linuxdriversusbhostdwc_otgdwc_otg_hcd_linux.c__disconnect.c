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
struct TYPE_2__ {scalar_t__ is_b_host; } ;
struct usb_hcd {TYPE_1__ self; } ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */
 struct usb_hcd* dwc_otg_hcd_to_hcd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _disconnect(dwc_otg_hcd_t * hcd)
{
	struct usb_hcd *usb_hcd = dwc_otg_hcd_to_hcd(hcd);

	usb_hcd->self.is_b_host = 0;
	return 0;
}