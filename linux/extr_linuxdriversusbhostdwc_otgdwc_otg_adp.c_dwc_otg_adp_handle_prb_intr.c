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

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_24__ {int pmuactv; int pmuintsel; int pwrdnswtch; int srp_det_msk; scalar_t__ bsessvld; int /*<<< orphan*/  idsts; } ;
struct TYPE_27__ {void* d32; TYPE_3__ b; } ;
typedef  TYPE_6__ gpwrdn_data_t ;
struct TYPE_23__ {int /*<<< orphan*/  bsesvld; } ;
struct TYPE_28__ {TYPE_2__ b; void* d32; } ;
typedef  TYPE_7__ gotgctl_data_t ;
struct TYPE_22__ {int probe_counter; scalar_t__ initial_probe; void* gpwrdn; } ;
struct TYPE_29__ {int power_down; void* op_state; TYPE_4__* core_global_regs; TYPE_1__ adp; int /*<<< orphan*/  lock; } ;
typedef  TYPE_8__ dwc_otg_core_if_t ;
struct TYPE_26__ {scalar_t__ rtim; int adp_prb_int; } ;
struct TYPE_30__ {int /*<<< orphan*/  d32; TYPE_5__ b; } ;
typedef  TYPE_9__ adpctl_data_t ;
struct TYPE_25__ {int /*<<< orphan*/  gpwrdn; int /*<<< orphan*/  gotgctl; int /*<<< orphan*/  gintsts; } ;

/* Variables and functions */
 void* A_HOST ; 
 void* B_PERIPHERAL ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  DWC_PRINTF (char*) ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cil_hcd_start (TYPE_8__*) ; 
 int /*<<< orphan*/  cil_pcd_start (TYPE_8__*) ; 
 scalar_t__ compare_timer_values (TYPE_8__*) ; 
 int /*<<< orphan*/  dwc_otg_adp_probe_stop (TYPE_8__*) ; 
 int /*<<< orphan*/  dwc_otg_adp_read_reg (TYPE_8__*) ; 
 int /*<<< orphan*/  dwc_otg_adp_turnon_vbus (TYPE_8__*) ; 
 int /*<<< orphan*/  dwc_otg_adp_write_reg (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_core_init (TYPE_8__*) ; 
 int /*<<< orphan*/  dwc_otg_enable_global_interrupts (TYPE_8__*) ; 
 int /*<<< orphan*/  dwc_otg_initiate_srp (TYPE_8__*) ; 
 scalar_t__ set_timer_value (TYPE_8__*,scalar_t__) ; 

__attribute__((used)) static int32_t dwc_otg_adp_handle_prb_intr(dwc_otg_core_if_t * core_if,
						 uint32_t val)
{
	adpctl_data_t adpctl = {.d32 = 0 };
	gpwrdn_data_t gpwrdn, temp;
	adpctl.d32 = val;

	temp.d32 = DWC_READ_REG32(&core_if->core_global_regs->gpwrdn);
	core_if->adp.probe_counter++;
	core_if->adp.gpwrdn = DWC_READ_REG32(&core_if->core_global_regs->gpwrdn);
	if (adpctl.b.rtim == 0 && !temp.b.idsts){
		DWC_PRINTF("RTIM value is 0\n");
		goto exit;
	}
	if (set_timer_value(core_if, adpctl.b.rtim) &&
	    core_if->adp.initial_probe) {
		core_if->adp.initial_probe = 0;
		dwc_otg_adp_probe_stop(core_if);
		gpwrdn.d32 = 0;
		gpwrdn.b.pmuactv = 1;
		gpwrdn.b.pmuintsel = 1;
		DWC_MODIFY_REG32(&core_if->core_global_regs->gpwrdn, gpwrdn.d32, 0);
		DWC_WRITE_REG32(&core_if->core_global_regs->gintsts, 0xFFFFFFFF);

		/* check which value is for device mode and which for Host mode */
		if (!temp.b.idsts) {	/* considered host mode value is 0 */
			/*
			 * Turn on VBUS after initial ADP probe.
			 */
			core_if->op_state = A_HOST;
			dwc_otg_enable_global_interrupts(core_if);
			DWC_SPINUNLOCK(core_if->lock);
			cil_hcd_start(core_if);
			dwc_otg_adp_turnon_vbus(core_if);
			DWC_SPINLOCK(core_if->lock);
		} else {
			/*
			 * Initiate SRP after initial ADP probe.
			 */
			dwc_otg_enable_global_interrupts(core_if);
			dwc_otg_initiate_srp(core_if);
		}
	} else if (core_if->adp.probe_counter > 2){
		gpwrdn.d32 = DWC_READ_REG32(&core_if->core_global_regs->gpwrdn);
		if (compare_timer_values(core_if)) {
			DWC_PRINTF("Difference in timer values !!! \n");
//                      core_if->adp.attached = DWC_OTG_ADP_ATTACHED;
			dwc_otg_adp_probe_stop(core_if);

			/* Power on the core */
			if (core_if->power_down == 2) {
				gpwrdn.b.pwrdnswtch = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);
			}

			/* check which value is for device mode and which for Host mode */
			if (!temp.b.idsts) {	/* considered host mode value is 0 */
				/* Disable Interrupt from Power Down Logic */
				gpwrdn.d32 = 0;
				gpwrdn.b.pmuintsel = 1;
				gpwrdn.b.pmuactv = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, gpwrdn.d32, 0);

				/*
				 * Initialize the Core for Host mode.
				 */
				core_if->op_state = A_HOST;
				dwc_otg_core_init(core_if);
				dwc_otg_enable_global_interrupts(core_if);
				cil_hcd_start(core_if);
			} else {
				gotgctl_data_t gotgctl;
				/* Mask SRP detected interrupt from Power Down Logic */
				gpwrdn.d32 = 0;
				gpwrdn.b.srp_det_msk = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, gpwrdn.d32, 0);

				/* Disable Power Down Logic */
				gpwrdn.d32 = 0;
				gpwrdn.b.pmuintsel = 1;
				gpwrdn.b.pmuactv = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, gpwrdn.d32, 0);

				/*
				 * Initialize the Core for Device mode.
				 */
				core_if->op_state = B_PERIPHERAL;
				dwc_otg_core_init(core_if);
				dwc_otg_enable_global_interrupts(core_if);
				cil_pcd_start(core_if);

				gotgctl.d32 = DWC_READ_REG32(&core_if->core_global_regs->gotgctl);
				if (!gotgctl.b.bsesvld) {
					dwc_otg_initiate_srp(core_if);
				}
			}
		}
		if (core_if->power_down == 2) {
			if (gpwrdn.b.bsessvld) {
				/* Mask SRP detected interrupt from Power Down Logic */
				gpwrdn.d32 = 0;
				gpwrdn.b.srp_det_msk = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->gpwrdn, gpwrdn.d32, 0);

				/* Disable Power Down Logic */
				gpwrdn.d32 = 0;
				gpwrdn.b.pmuactv = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->gpwrdn, gpwrdn.d32, 0);

				/*
				 * Initialize the Core for Device mode.
				 */
				core_if->op_state = B_PERIPHERAL;
				dwc_otg_core_init(core_if);
				dwc_otg_enable_global_interrupts(core_if);
				cil_pcd_start(core_if);
			}
		}
	}
exit:
	/* Clear interrupt */
	adpctl.d32 = dwc_otg_adp_read_reg(core_if);
	adpctl.b.adp_prb_int = 1;
	dwc_otg_adp_write_reg(core_if, adpctl.d32);

	return 0;
}