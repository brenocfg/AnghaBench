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
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int ocic_mask ; 
 int orig_ohci_hub_status_data (struct usb_hcd*,char*) ; 

__attribute__((used)) static int ohci_da8xx_hub_status_data(struct usb_hcd *hcd, char *buf)
{
	int length		= orig_ohci_hub_status_data(hcd, buf);

	/* See if we have OCIC bit set on port 1 */
	if (ocic_mask & (1 << 1)) {
		dev_dbg(hcd->self.controller, "over-current indicator change "
			"on port 1\n");

		if (!length)
			length = 1;

		buf[0] |= 1 << 1;
	}
	return length;
}