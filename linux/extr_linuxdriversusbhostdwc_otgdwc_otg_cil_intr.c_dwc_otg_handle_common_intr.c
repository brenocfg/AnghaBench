#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_57__   TYPE_9__ ;
typedef  struct TYPE_56__   TYPE_8__ ;
typedef  struct TYPE_55__   TYPE_7__ ;
typedef  struct TYPE_54__   TYPE_6__ ;
typedef  struct TYPE_53__   TYPE_5__ ;
typedef  struct TYPE_52__   TYPE_4__ ;
typedef  struct TYPE_51__   TYPE_3__ ;
typedef  struct TYPE_50__   TYPE_2__ ;
typedef  struct TYPE_49__   TYPE_1__ ;
typedef  struct TYPE_48__   TYPE_18__ ;
typedef  struct TYPE_47__   TYPE_17__ ;
typedef  struct TYPE_46__   TYPE_16__ ;
typedef  struct TYPE_45__   TYPE_15__ ;
typedef  struct TYPE_44__   TYPE_14__ ;
typedef  struct TYPE_43__   TYPE_13__ ;
typedef  struct TYPE_42__   TYPE_12__ ;
typedef  struct TYPE_41__   TYPE_11__ ;
typedef  struct TYPE_40__   TYPE_10__ ;

/* Type definitions */
struct TYPE_41__ {int rstpdwnmodule; int enbl_extnd_hiber; } ;
struct TYPE_42__ {scalar_t__ d32; TYPE_11__ b; } ;
typedef  TYPE_12__ pcgcctl_data_t ;
typedef  int int32_t ;
struct TYPE_57__ {int restore; int linestate; scalar_t__ sts_chngint_msk; scalar_t__ sts_chngint; scalar_t__ adp_int; scalar_t__ srp_det_msk; scalar_t__ srp_det; scalar_t__ rst_det_msk; scalar_t__ rst_det; scalar_t__ lnstchng_msk; scalar_t__ lnstschng; scalar_t__ disconn_det_msk; scalar_t__ disconn_det; } ;
struct TYPE_43__ {TYPE_9__ b; scalar_t__ d32; } ;
typedef  TYPE_13__ gpwrdn_data_t ;
struct TYPE_56__ {int restoredone; int portintr; scalar_t__ usbsuspend; scalar_t__ wkupintr; scalar_t__ sessreqintr; scalar_t__ disconnect; scalar_t__ conidstschng; scalar_t__ otgintr; scalar_t__ modemismatch; } ;
struct TYPE_44__ {int d32; TYPE_8__ b; } ;
typedef  TYPE_14__ gintsts_data_t ;
struct TYPE_55__ {int portintr; } ;
struct TYPE_45__ {int d32; TYPE_7__ b; } ;
typedef  TYPE_15__ gintmsk_data_t ;
struct TYPE_46__ {int /*<<< orphan*/  hcd; TYPE_17__* core_if; } ;
typedef  TYPE_16__ dwc_otg_device_t ;
struct TYPE_47__ {int power_down; int xhib; int hibernation_suspend; scalar_t__ lock; TYPE_10__* core_global_regs; TYPE_6__* pcd_cb; int /*<<< orphan*/  lx_state; int /*<<< orphan*/ * pcgcctl; TYPE_5__* dev_if; TYPE_2__* dr_backup; TYPE_1__* gr_backup; int /*<<< orphan*/  frame_num; } ;
typedef  TYPE_17__ dwc_otg_core_if_t ;
struct TYPE_51__ {int pwronprgdone; } ;
struct TYPE_48__ {scalar_t__ d32; TYPE_3__ b; } ;
typedef  TYPE_18__ dctl_data_t ;
struct TYPE_54__ {int /*<<< orphan*/  p; int /*<<< orphan*/  (* resume_wakeup ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_53__ {TYPE_4__* dev_global_regs; } ;
struct TYPE_52__ {int /*<<< orphan*/  dctl; int /*<<< orphan*/  dcfg; } ;
struct TYPE_50__ {int dcfg; int dctl; } ;
struct TYPE_49__ {int gusbcfg_local; } ;
struct TYPE_40__ {int /*<<< orphan*/  gintmsk; int /*<<< orphan*/  gintsts; int /*<<< orphan*/  gusbcfg; int /*<<< orphan*/  gpwrdn; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_GPWRDN_INTR (TYPE_17__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_ANY ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DWC_OTG_L0 ; 
 int /*<<< orphan*/  DWC_PRINTF (char*,...) ; 
 scalar_t__ DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINLOCK (scalar_t__) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK (scalar_t__) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  adp_int ; 
 int /*<<< orphan*/  disconn_det ; 
 int /*<<< orphan*/  dwc_otg_adp_handle_intr (TYPE_17__*) ; 
 int dwc_otg_device_hibernation_restore (TYPE_17__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dwc_otg_get_frame_number (TYPE_17__*) ; 
 int dwc_otg_handle_conn_id_status_change_intr (TYPE_17__*) ; 
 int dwc_otg_handle_disconnect_intr (TYPE_17__*) ; 
 int dwc_otg_handle_mode_mismatch_intr (TYPE_17__*) ; 
 int dwc_otg_handle_otg_intr (TYPE_17__*) ; 
 int /*<<< orphan*/  dwc_otg_handle_pwrdn_disconnect_intr (TYPE_17__*) ; 
 int /*<<< orphan*/  dwc_otg_handle_pwrdn_srp_intr (TYPE_17__*) ; 
 int /*<<< orphan*/  dwc_otg_handle_pwrdn_stschng_intr (TYPE_16__*) ; 
 int /*<<< orphan*/  dwc_otg_handle_pwrdn_wakeup_detected_intr (TYPE_17__*) ; 
 int dwc_otg_handle_session_req_intr (TYPE_17__*) ; 
 int dwc_otg_handle_usb_suspend_intr (TYPE_17__*) ; 
 int dwc_otg_handle_wakeup_detected_intr (TYPE_17__*) ; 
 int dwc_otg_handle_xhib_exit_intr (TYPE_17__*) ; 
 scalar_t__ dwc_otg_is_device_mode (TYPE_17__*) ; 
 int dwc_otg_read_common_intr (TYPE_17__*,TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_restore_dev_regs (TYPE_17__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_restore_global_regs (TYPE_17__*) ; 
 int /*<<< orphan*/  dwc_udelay (int) ; 
 scalar_t__ fiq_enable ; 
 int /*<<< orphan*/  lnstschng ; 
 int /*<<< orphan*/  rst_det ; 
 int /*<<< orphan*/  srp_det ; 
 int /*<<< orphan*/  sts_chngint ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

int32_t dwc_otg_handle_common_intr(void *dev)
{
	int retval = 0;
	gintsts_data_t gintsts;
	gintmsk_data_t gintmsk_reenable = { .d32 = 0 };
	gpwrdn_data_t gpwrdn = {.d32 = 0 };
	dwc_otg_device_t *otg_dev = dev;
	dwc_otg_core_if_t *core_if = otg_dev->core_if;
	gpwrdn.d32 = DWC_READ_REG32(&core_if->core_global_regs->gpwrdn);
	if (dwc_otg_is_device_mode(core_if))
		core_if->frame_num = dwc_otg_get_frame_number(core_if);

	if (core_if->lock)
		DWC_SPINLOCK(core_if->lock);

	if (core_if->power_down == 3 && core_if->xhib == 1) {
		DWC_DEBUGPL(DBG_ANY, "Exiting from xHIB state\n");
		retval |= dwc_otg_handle_xhib_exit_intr(core_if);
		core_if->xhib = 2;
		if (core_if->lock)
			DWC_SPINUNLOCK(core_if->lock);

		return retval;
	}

	if (core_if->hibernation_suspend <= 0) {
		/* read_common will have to poke the FIQ's saved mask. We must then clear this mask at the end
		 * of this handler - god only knows why it's done like this
		 */
		gintsts.d32 = dwc_otg_read_common_intr(core_if, &gintmsk_reenable, otg_dev->hcd);

		if (gintsts.b.modemismatch) {
			retval |= dwc_otg_handle_mode_mismatch_intr(core_if);
		}
		if (gintsts.b.otgintr) {
			retval |= dwc_otg_handle_otg_intr(core_if);
		}
		if (gintsts.b.conidstschng) {
			retval |=
			    dwc_otg_handle_conn_id_status_change_intr(core_if);
		}
		if (gintsts.b.disconnect) {
			retval |= dwc_otg_handle_disconnect_intr(core_if);
		}
		if (gintsts.b.sessreqintr) {
			retval |= dwc_otg_handle_session_req_intr(core_if);
		}
		if (gintsts.b.wkupintr) {
			retval |= dwc_otg_handle_wakeup_detected_intr(core_if);
		}
		if (gintsts.b.usbsuspend) {
			retval |= dwc_otg_handle_usb_suspend_intr(core_if);
		}
#ifdef CONFIG_USB_DWC_OTG_LPM
		if (gintsts.b.lpmtranrcvd) {
			retval |= dwc_otg_handle_lpm_intr(core_if);
		}
#endif
		if (gintsts.b.restoredone) {
			gintsts.d32 = 0;
	                if (core_if->power_down == 2)
				core_if->hibernation_suspend = -1;
			else if (core_if->power_down == 3 && core_if->xhib == 2) {
				gpwrdn_data_t gpwrdn = {.d32 = 0 };
				pcgcctl_data_t pcgcctl = {.d32 = 0 };
				dctl_data_t dctl = {.d32 = 0 };

				DWC_WRITE_REG32(&core_if->core_global_regs->
						gintsts, 0xFFFFFFFF);

				DWC_DEBUGPL(DBG_ANY,
					    "RESTORE DONE generated\n");

				gpwrdn.b.restore = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->gpwrdn, gpwrdn.d32, 0);
				dwc_udelay(10);

				pcgcctl.b.rstpdwnmodule = 1;
				DWC_MODIFY_REG32(core_if->pcgcctl, pcgcctl.d32, 0);

				DWC_WRITE_REG32(&core_if->core_global_regs->gusbcfg, core_if->gr_backup->gusbcfg_local);
				DWC_WRITE_REG32(&core_if->dev_if->dev_global_regs->dcfg, core_if->dr_backup->dcfg);
				DWC_WRITE_REG32(&core_if->dev_if->dev_global_regs->dctl, core_if->dr_backup->dctl);
				dwc_udelay(50);

				dctl.b.pwronprgdone = 1;
				DWC_MODIFY_REG32(&core_if->dev_if->dev_global_regs->dctl, 0, dctl.d32);
				dwc_udelay(10);

				dwc_otg_restore_global_regs(core_if);
				dwc_otg_restore_dev_regs(core_if, 0);

				dctl.d32 = 0;
				dctl.b.pwronprgdone = 1;
				DWC_MODIFY_REG32(&core_if->dev_if->dev_global_regs->dctl, dctl.d32, 0);
				dwc_udelay(10);

				pcgcctl.d32 = 0;
				pcgcctl.b.enbl_extnd_hiber = 1;
				DWC_MODIFY_REG32(core_if->pcgcctl, pcgcctl.d32, 0);

				/* The core will be in ON STATE */
				core_if->lx_state = DWC_OTG_L0;
				core_if->xhib = 0;

				DWC_SPINUNLOCK(core_if->lock);
				if (core_if->pcd_cb && core_if->pcd_cb->resume_wakeup) {
					core_if->pcd_cb->resume_wakeup(core_if->pcd_cb->p);
				}
				DWC_SPINLOCK(core_if->lock);

			}

			gintsts.b.restoredone = 1;
			DWC_WRITE_REG32(&core_if->core_global_regs->gintsts,gintsts.d32);
			DWC_PRINTF(" --Restore done interrupt received-- \n");
			retval |= 1;
		}
		if (gintsts.b.portintr && dwc_otg_is_device_mode(core_if)) {
			/* The port interrupt occurs while in device mode with HPRT0
			 * Port Enable/Disable.
			 */
			gintsts.d32 = 0;
			gintsts.b.portintr = 1;
			DWC_WRITE_REG32(&core_if->core_global_regs->gintsts,gintsts.d32);
			retval |= 1;
			gintmsk_reenable.b.portintr = 1;

		}
		/* Did we actually handle anything? if so, unmask the interrupt */
//		fiq_print(FIQDBG_INT, otg_dev->hcd->fiq_state, "CILOUT %1d", retval);
//		fiq_print(FIQDBG_INT, otg_dev->hcd->fiq_state, "%08x", gintsts.d32);
//		fiq_print(FIQDBG_INT, otg_dev->hcd->fiq_state, "%08x", gintmsk_reenable.d32);
		if (retval && fiq_enable) {
			DWC_WRITE_REG32(&core_if->core_global_regs->gintmsk, gintmsk_reenable.d32);
		}

	} else {
		DWC_DEBUGPL(DBG_ANY, "gpwrdn=%08x\n", gpwrdn.d32);

		if (gpwrdn.b.disconn_det && gpwrdn.b.disconn_det_msk) {
			CLEAR_GPWRDN_INTR(core_if, disconn_det);
			if (gpwrdn.b.linestate == 0) {
				dwc_otg_handle_pwrdn_disconnect_intr(core_if);
			} else {
				DWC_PRINTF("Disconnect detected while linestate is not 0\n");
			}

			retval |= 1;
		}
		if (gpwrdn.b.lnstschng && gpwrdn.b.lnstchng_msk) {
			CLEAR_GPWRDN_INTR(core_if, lnstschng);
			/* remote wakeup from hibernation */
			if (gpwrdn.b.linestate == 2 || gpwrdn.b.linestate == 1) {
				dwc_otg_handle_pwrdn_wakeup_detected_intr(core_if);
			} else {
				DWC_PRINTF("gpwrdn.linestate = %d\n", gpwrdn.b.linestate);
			}
			retval |= 1;
		}
		if (gpwrdn.b.rst_det && gpwrdn.b.rst_det_msk) {
			CLEAR_GPWRDN_INTR(core_if, rst_det);
			if (gpwrdn.b.linestate == 0) {
				DWC_PRINTF("Reset detected\n");
				retval |= dwc_otg_device_hibernation_restore(core_if, 0, 1);
			}
		}
		if (gpwrdn.b.srp_det && gpwrdn.b.srp_det_msk) {
			CLEAR_GPWRDN_INTR(core_if, srp_det);
			dwc_otg_handle_pwrdn_srp_intr(core_if);
			retval |= 1;
		}
	}
	/* Handle ADP interrupt here */
	if (gpwrdn.b.adp_int) {
		DWC_PRINTF("ADP interrupt\n");
		CLEAR_GPWRDN_INTR(core_if, adp_int);
		dwc_otg_adp_handle_intr(core_if);
		retval |= 1;
	}
	if (gpwrdn.b.sts_chngint && gpwrdn.b.sts_chngint_msk) {
		DWC_PRINTF("STS CHNG interrupt asserted\n");
		CLEAR_GPWRDN_INTR(core_if, sts_chngint);
		dwc_otg_handle_pwrdn_stschng_intr(otg_dev);

		retval |= 1;
	}
	if (core_if->lock)
		DWC_SPINUNLOCK(core_if->lock);
	return retval;
}