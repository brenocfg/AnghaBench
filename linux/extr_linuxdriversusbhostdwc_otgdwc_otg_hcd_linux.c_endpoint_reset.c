#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_host_endpoint {int /*<<< orphan*/  hcpriv; } ;
struct usb_hcd {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_irqflags_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_IRQSAVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK_IRQRESTORE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_hcd_endpoint_reset (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epnum ; 
 TYPE_1__* hcd_to_dwc_otg_hcd (struct usb_hcd*) ; 

__attribute__((used)) static void endpoint_reset(struct usb_hcd *hcd, struct usb_host_endpoint *ep)
{
	dwc_irqflags_t flags;
	dwc_otg_hcd_t *dwc_otg_hcd = hcd_to_dwc_otg_hcd(hcd);

	DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD EP RESET: Endpoint Num=0x%02d\n", epnum);

	DWC_SPINLOCK_IRQSAVE(dwc_otg_hcd->lock, &flags);
	if (ep->hcpriv) {
		dwc_otg_hcd_endpoint_reset(dwc_otg_hcd, ep->hcpriv);
	}
	DWC_SPINUNLOCK_IRQRESTORE(dwc_otg_hcd->lock, flags);
}