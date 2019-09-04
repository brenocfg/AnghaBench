#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ prtpwr; } ;
struct TYPE_9__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_3__ hprt0_data_t ;
struct TYPE_10__ {TYPE_6__* core_if; } ;
typedef  TYPE_4__ dwc_otg_hcd_t ;
struct TYPE_11__ {TYPE_2__* host_if; } ;
struct TYPE_8__ {int /*<<< orphan*/  hprt0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DWC_PRINTF (char*) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_mdelay (int) ; 
 int /*<<< orphan*/  dwc_otg_disable_host_interrupts (TYPE_6__*) ; 

void dwc_otg_hcd_stop(dwc_otg_hcd_t * hcd)
{
	hprt0_data_t hprt0 = {.d32 = 0 };

	DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD STOP\n");

	/*
	 * The root hub should be disconnected before this function is called.
	 * The disconnect will clear the QTD lists (via ..._hcd_urb_dequeue)
	 * and the QH lists (via ..._hcd_endpoint_disable).
	 */

	/* Turn off all host-specific interrupts. */
	dwc_otg_disable_host_interrupts(hcd->core_if);

	/* Turn off the vbus power */
	DWC_PRINTF("PortPower off\n");
	hprt0.b.prtpwr = 0;
	DWC_WRITE_REG32(hcd->core_if->host_if->hprt0, hprt0.d32);
	dwc_mdelay(1);
}