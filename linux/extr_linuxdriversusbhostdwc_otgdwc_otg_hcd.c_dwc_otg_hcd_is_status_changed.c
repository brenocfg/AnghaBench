#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ port_over_current_change; scalar_t__ port_suspend_change; scalar_t__ port_enable_change; scalar_t__ port_reset_change; scalar_t__ port_connect_status_change; } ;
struct TYPE_5__ {TYPE_2__ b; } ;
struct TYPE_7__ {TYPE_1__ flags; } ;
typedef  TYPE_3__ dwc_otg_hcd_t ;

/* Variables and functions */
 int DWC_E_INVALID ; 

int dwc_otg_hcd_is_status_changed(dwc_otg_hcd_t * hcd, int port)
{
	int retval;

	if (port != 1) {
		return -DWC_E_INVALID;
	}

	retval = (hcd->flags.b.port_connect_status_change ||
		  hcd->flags.b.port_reset_change ||
		  hcd->flags.b.port_enable_change ||
		  hcd->flags.b.port_suspend_change ||
		  hcd->flags.b.port_over_current_change);
#ifdef DEBUG
	if (retval) {
		DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD HUB STATUS DATA:"
			    " Root port status changed\n");
		DWC_DEBUGPL(DBG_HCDV, "  port_connect_status_change: %d\n",
			    hcd->flags.b.port_connect_status_change);
		DWC_DEBUGPL(DBG_HCDV, "  port_reset_change: %d\n",
			    hcd->flags.b.port_reset_change);
		DWC_DEBUGPL(DBG_HCDV, "  port_enable_change: %d\n",
			    hcd->flags.b.port_enable_change);
		DWC_DEBUGPL(DBG_HCDV, "  port_suspend_change: %d\n",
			    hcd->flags.b.port_suspend_change);
		DWC_DEBUGPL(DBG_HCDV, "  port_over_current_change: %d\n",
			    hcd->flags.b.port_over_current_change);
	}
#endif
	return retval;
}