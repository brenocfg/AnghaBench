#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ bsesvld; } ;
struct TYPE_14__ {TYPE_2__ b; void* d32; } ;
typedef  TYPE_6__ gotgctl_data_t ;
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
struct TYPE_13__ {scalar_t__ suspsts; } ;
struct TYPE_15__ {TYPE_5__ b; void* d32; } ;
typedef  TYPE_7__ dsts_data_t ;
struct TYPE_16__ {TYPE_4__* dev_if; TYPE_1__* core_global_regs; } ;
struct TYPE_12__ {TYPE_3__* dev_global_regs; } ;
struct TYPE_11__ {int /*<<< orphan*/  dsts; } ;
struct TYPE_9__ {int /*<<< orphan*/  gotgctl; } ;

/* Variables and functions */
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 TYPE_8__* GET_CORE_IF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_pcd_initiate_srp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_pcd_remote_wakeup (int /*<<< orphan*/ *,int) ; 

int dwc_otg_pcd_wakeup(dwc_otg_pcd_t * pcd)
{
	dsts_data_t dsts;
	gotgctl_data_t gotgctl;

	/*
	 * This function starts the Protocol if no session is in progress. If
	 * a session is already in progress, but the device is suspended,
	 * remote wakeup signaling is started.
	 */

	/* Check if valid session */
	gotgctl.d32 =
	    DWC_READ_REG32(&(GET_CORE_IF(pcd)->core_global_regs->gotgctl));
	if (gotgctl.b.bsesvld) {
		/* Check if suspend state */
		dsts.d32 =
		    DWC_READ_REG32(&
				   (GET_CORE_IF(pcd)->dev_if->
				    dev_global_regs->dsts));
		if (dsts.b.suspsts) {
			dwc_otg_pcd_remote_wakeup(pcd, 1);
		}
	} else {
		dwc_otg_pcd_initiate_srp(pcd);
	}

	return 0;

}