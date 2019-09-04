#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int port_suspend_change; } ;
struct TYPE_7__ {TYPE_2__ b; } ;
struct TYPE_8__ {TYPE_3__ flags; TYPE_1__* core_if; } ;
typedef  TYPE_4__ dwc_otg_hcd_t ;
struct TYPE_5__ {scalar_t__ lx_state; } ;

/* Variables and functions */
 scalar_t__ DWC_OTG_L2 ; 

__attribute__((used)) static int dwc_otg_hcd_rem_wakeup_cb(void *p)
{
	dwc_otg_hcd_t *hcd = p;

	if (hcd->core_if->lx_state == DWC_OTG_L2) {
		hcd->flags.b.port_suspend_change = 1;
	}
#ifdef CONFIG_USB_DWC_OTG_LPM
	else {
		hcd->flags.b.port_l1_change = 1;
	}
#endif
	return 0;
}