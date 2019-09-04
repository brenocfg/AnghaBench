#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_18__ {int pmuintsel; int pmuactv; int pwrdnswtch; } ;
struct TYPE_21__ {scalar_t__ d32; TYPE_2__ b; } ;
typedef  TYPE_5__ gpwrdn_data_t ;
struct TYPE_17__ {int hstsethnpen; scalar_t__ devhnpen; } ;
struct TYPE_22__ {TYPE_1__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_6__ gotgctl_data_t ;
struct TYPE_19__ {int disconnect; } ;
struct TYPE_23__ {scalar_t__ d32; TYPE_3__ b; } ;
typedef  TYPE_7__ gintsts_data_t ;
struct TYPE_24__ {scalar_t__ op_state; int power_down; TYPE_4__* core_global_regs; int /*<<< orphan*/  lx_state; scalar_t__ adp_enable; int /*<<< orphan*/  lock; } ;
typedef  TYPE_8__ dwc_otg_core_if_t ;
struct TYPE_20__ {int /*<<< orphan*/  gintsts; int /*<<< orphan*/  gpwrdn; int /*<<< orphan*/  gotgctl; } ;

/* Variables and functions */
 scalar_t__ A_HOST ; 
 scalar_t__ B_HOST ; 
 void* B_PERIPHERAL ; 
 int /*<<< orphan*/  DBG_ANY ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DWC_OTG_L3 ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cil_hcd_disconnect (TYPE_8__*) ; 
 int /*<<< orphan*/  cil_hcd_stop (TYPE_8__*) ; 
 int /*<<< orphan*/  cil_pcd_start (TYPE_8__*) ; 
 int /*<<< orphan*/  dwc_otg_adp_probe_start (TYPE_8__*) ; 
 scalar_t__ dwc_otg_is_device_mode (TYPE_8__*) ; 
 scalar_t__ dwc_otg_is_host_mode (TYPE_8__*) ; 
 int /*<<< orphan*/  op_state_str (TYPE_8__*) ; 

int32_t dwc_otg_handle_disconnect_intr(dwc_otg_core_if_t * core_if)
{
	gintsts_data_t gintsts;

	DWC_DEBUGPL(DBG_ANY, "++Disconnect Detected Interrupt++ (%s) %s\n",
		    (dwc_otg_is_host_mode(core_if) ? "Host" : "Device"),
		    op_state_str(core_if));

/** @todo Consolidate this if statement. */
#ifndef DWC_HOST_ONLY
	if (core_if->op_state == B_HOST) {
		/* If in device mode Disconnect and stop the HCD, then
		 * start the PCD. */
		DWC_SPINUNLOCK(core_if->lock);
		cil_hcd_disconnect(core_if);
		cil_pcd_start(core_if);
		DWC_SPINLOCK(core_if->lock);
		core_if->op_state = B_PERIPHERAL;
	} else if (dwc_otg_is_device_mode(core_if)) {
		gotgctl_data_t gotgctl = {.d32 = 0 };
		gotgctl.d32 =
		    DWC_READ_REG32(&core_if->core_global_regs->gotgctl);
		if (gotgctl.b.hstsethnpen == 1) {
			/* Do nothing, if HNP in process the OTG
			 * interrupt "Host Negotiation Detected"
			 * interrupt will do the mode switch.
			 */
		} else if (gotgctl.b.devhnpen == 0) {
			/* If in device mode Disconnect and stop the HCD, then
			 * start the PCD. */
			DWC_SPINUNLOCK(core_if->lock);
			cil_hcd_disconnect(core_if);
			cil_pcd_start(core_if);
			DWC_SPINLOCK(core_if->lock);
			core_if->op_state = B_PERIPHERAL;
		} else {
			DWC_DEBUGPL(DBG_ANY, "!a_peripheral && !devhnpen\n");
		}
	} else {
		if (core_if->op_state == A_HOST) {
			/* A-Cable still connected but device disconnected. */
			DWC_SPINUNLOCK(core_if->lock);
			cil_hcd_disconnect(core_if);
			DWC_SPINLOCK(core_if->lock);
			if (core_if->adp_enable) {
				gpwrdn_data_t gpwrdn = { .d32 = 0 };
				cil_hcd_stop(core_if);
				/* Enable Power Down Logic */
				gpwrdn.b.pmuintsel = 1;
				gpwrdn.b.pmuactv = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);
				dwc_otg_adp_probe_start(core_if);

				/* Power off the core */
				if (core_if->power_down == 2) {
					gpwrdn.d32 = 0;
					gpwrdn.b.pwrdnswtch = 1;
					DWC_MODIFY_REG32
					    (&core_if->core_global_regs->gpwrdn,
					     gpwrdn.d32, 0);
				}
			}
		}
	}
#endif
	/* Change to L3(OFF) state */
	core_if->lx_state = DWC_OTG_L3;

	gintsts.d32 = 0;
	gintsts.b.disconnect = 1;
	DWC_WRITE_REG32(&core_if->core_global_regs->gintsts, gintsts.d32);
	return 1;
}