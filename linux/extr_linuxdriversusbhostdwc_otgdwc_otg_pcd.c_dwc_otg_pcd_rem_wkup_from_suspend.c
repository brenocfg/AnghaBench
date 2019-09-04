#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int srp_det_msk; int pmuactv; } ;
struct TYPE_28__ {scalar_t__ d32; TYPE_2__ b; } ;
typedef  TYPE_7__ gpwrdn_data_t ;
struct TYPE_29__ {scalar_t__ remote_wakeup_enable; } ;
typedef  TYPE_8__ dwc_otg_pcd_t ;
struct TYPE_30__ {TYPE_6__* dev_if; int /*<<< orphan*/  op_state; TYPE_3__* core_global_regs; scalar_t__ adp_enable; } ;
typedef  TYPE_9__ dwc_otg_core_if_t ;
struct TYPE_22__ {int /*<<< orphan*/  suspsts; } ;
struct TYPE_20__ {TYPE_1__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_10__ dsts_data_t ;
struct TYPE_25__ {int rmtwkupsig; } ;
struct TYPE_21__ {scalar_t__ d32; TYPE_4__ b; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_11__ dctl_data_t ;
struct TYPE_27__ {TYPE_5__* dev_global_regs; } ;
struct TYPE_26__ {int /*<<< orphan*/  dctl; int /*<<< orphan*/  dsts; } ;
struct TYPE_24__ {int /*<<< orphan*/  gpwrdn; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_PERIPHERAL ; 
 int /*<<< orphan*/  DBG_PCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WARN (char*) ; 
 TYPE_9__* GET_CORE_IF (TYPE_8__*) ; 
 int /*<<< orphan*/  cil_pcd_start (TYPE_9__*) ; 
 int /*<<< orphan*/  dwc_mdelay (int) ; 
 int /*<<< orphan*/  dwc_otg_adp_probe_stop (TYPE_9__*) ; 
 int /*<<< orphan*/  dwc_otg_core_init (TYPE_9__*) ; 
 int /*<<< orphan*/  dwc_otg_enable_global_interrupts (TYPE_9__*) ; 
 int /*<<< orphan*/  dwc_otg_initiate_srp (TYPE_9__*) ; 

void dwc_otg_pcd_rem_wkup_from_suspend(dwc_otg_pcd_t * pcd, int set)
{
	dctl_data_t dctl = { 0 };
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);
	dsts_data_t dsts;

	dsts.d32 = DWC_READ_REG32(&core_if->dev_if->dev_global_regs->dsts);
	if (!dsts.b.suspsts) {
		DWC_WARN("Remote wakeup while is not in suspend state\n");
	}
	/* Check if DEVICE_REMOTE_WAKEUP feature enabled */
	if (pcd->remote_wakeup_enable) {
		if (set) {

			if (core_if->adp_enable) {
				gpwrdn_data_t gpwrdn;

				dwc_otg_adp_probe_stop(core_if);

				/* Mask SRP detected interrupt from Power Down Logic */
				gpwrdn.d32 = 0;
				gpwrdn.b.srp_det_msk = 1;
				DWC_MODIFY_REG32(&core_if->
						 core_global_regs->gpwrdn,
						 gpwrdn.d32, 0);

				/* Disable Power Down Logic */
				gpwrdn.d32 = 0;
				gpwrdn.b.pmuactv = 1;
				DWC_MODIFY_REG32(&core_if->
						 core_global_regs->gpwrdn,
						 gpwrdn.d32, 0);

				/*
				 * Initialize the Core for Device mode.
				 */
				core_if->op_state = B_PERIPHERAL;
				dwc_otg_core_init(core_if);
				dwc_otg_enable_global_interrupts(core_if);
				cil_pcd_start(core_if);

				dwc_otg_initiate_srp(core_if);
			}

			dctl.b.rmtwkupsig = 1;
			DWC_MODIFY_REG32(&core_if->dev_if->dev_global_regs->
					 dctl, 0, dctl.d32);
			DWC_DEBUGPL(DBG_PCD, "Set Remote Wakeup\n");

			dwc_mdelay(2);
			DWC_MODIFY_REG32(&core_if->dev_if->dev_global_regs->
					 dctl, dctl.d32, 0);
			DWC_DEBUGPL(DBG_PCD, "Clear Remote Wakeup\n");
		}
	} else {
		DWC_DEBUGPL(DBG_PCD, "Remote Wakeup is disabled\n");
	}
}