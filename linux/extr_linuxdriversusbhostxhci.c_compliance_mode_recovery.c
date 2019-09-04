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
typedef  int u32 ;
struct xhci_hub {int num_ports; TYPE_1__** ports; } ;
struct xhci_hcd {int port_status_u0; int /*<<< orphan*/  comp_mode_recovery_timer; struct usb_hcd* shared_hcd; struct xhci_hub usb3_rhub; } ;
struct usb_hcd {scalar_t__ state; } ;
struct timer_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_MODE_RCVRY_MSECS ; 
 scalar_t__ HC_STATE_SUSPENDED ; 
 int PORT_PLS_MASK ; 
 int USB_SS_PORT_LS_COMP_MOD ; 
 int /*<<< orphan*/  comp_mode_recovery_timer ; 
 struct xhci_hcd* from_timer (struct xhci_hcd*,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xhci_dbg_quirks ; 
 int /*<<< orphan*/  usb_hcd_poll_rh_status (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_hcd_resume_root_hub (struct usb_hcd*) ; 
 int /*<<< orphan*/  xhci_dbg_trace (struct xhci_hcd*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void compliance_mode_recovery(struct timer_list *t)
{
	struct xhci_hcd *xhci;
	struct usb_hcd *hcd;
	struct xhci_hub *rhub;
	u32 temp;
	int i;

	xhci = from_timer(xhci, t, comp_mode_recovery_timer);
	rhub = &xhci->usb3_rhub;

	for (i = 0; i < rhub->num_ports; i++) {
		temp = readl(rhub->ports[i]->addr);
		if ((temp & PORT_PLS_MASK) == USB_SS_PORT_LS_COMP_MOD) {
			/*
			 * Compliance Mode Detected. Letting USB Core
			 * handle the Warm Reset
			 */
			xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
					"Compliance mode detected->port %d",
					i + 1);
			xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
					"Attempting compliance mode recovery");
			hcd = xhci->shared_hcd;

			if (hcd->state == HC_STATE_SUSPENDED)
				usb_hcd_resume_root_hub(hcd);

			usb_hcd_poll_rh_status(hcd);
		}
	}

	if (xhci->port_status_u0 != ((1 << rhub->num_ports) - 1))
		mod_timer(&xhci->comp_mode_recovery_timer,
			jiffies + msecs_to_jiffies(COMP_MODE_RCVRY_MSECS));
}