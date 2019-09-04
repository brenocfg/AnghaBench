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
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (scalar_t__) ; 
 int /*<<< orphan*/  S3C2410X_CLEAR_EINTPEND () ; 
 scalar_t__ dwc_otg_hcd_handle_intr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hcd_to_dwc_otg_hcd (struct usb_hcd*) ; 

__attribute__((used)) static irqreturn_t dwc_otg_hcd_irq(struct usb_hcd *hcd)
{
	dwc_otg_hcd_t *dwc_otg_hcd = hcd_to_dwc_otg_hcd(hcd);
	int32_t retval = dwc_otg_hcd_handle_intr(dwc_otg_hcd);
	if (retval != 0) {
		S3C2410X_CLEAR_EINTPEND();
	}
	return IRQ_RETVAL(retval);
}