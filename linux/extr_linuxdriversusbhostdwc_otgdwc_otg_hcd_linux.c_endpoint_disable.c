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
struct TYPE_2__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_host_endpoint {int /*<<< orphan*/ * hcpriv; TYPE_1__ desc; } ;
struct usb_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_ep_addr_to_endpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_hcd_endpoint_disable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * hcd_to_dwc_otg_hcd (struct usb_hcd*) ; 

__attribute__((used)) static void endpoint_disable(struct usb_hcd *hcd, struct usb_host_endpoint *ep)
{
	dwc_otg_hcd_t *dwc_otg_hcd = hcd_to_dwc_otg_hcd(hcd);

	DWC_DEBUGPL(DBG_HCD,
		    "DWC OTG HCD EP DISABLE: _bEndpointAddress=0x%02x, "
		    "endpoint=%d\n", ep->desc.bEndpointAddress,
		    dwc_ep_addr_to_endpoint(ep->desc.bEndpointAddress));
	dwc_otg_hcd_endpoint_disable(dwc_otg_hcd, ep->hcpriv, 250);
	ep->hcpriv = NULL;
}