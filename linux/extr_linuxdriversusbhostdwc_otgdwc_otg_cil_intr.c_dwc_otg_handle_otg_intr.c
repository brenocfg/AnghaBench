#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_24__ {int pwrdnswtch; int pmuintsel; int pmuactv; } ;
struct TYPE_29__ {void* d32; TYPE_1__ b; } ;
typedef  TYPE_6__ gpwrdn_data_t ;
struct TYPE_27__ {scalar_t__ debdone; scalar_t__ adevtoutchng; scalar_t__ hstnegdet; scalar_t__ hstnegsucstschng; scalar_t__ sesreqsucstschng; scalar_t__ sesenddet; } ;
struct TYPE_30__ {void* d32; TYPE_4__ b; } ;
typedef  TYPE_7__ gotgint_data_t ;
struct TYPE_26__ {int devhnpen; int sesreq; int hnpreq; scalar_t__ hstnegscs; scalar_t__ sesreqscs; } ;
struct TYPE_31__ {void* d32; TYPE_3__ b; } ;
typedef  TYPE_8__ gotgctl_data_t ;
struct TYPE_28__ {int sofintr; } ;
struct TYPE_32__ {void* d32; TYPE_5__ b; } ;
typedef  TYPE_9__ gintmsk_data_t ;
struct TYPE_22__ {scalar_t__ op_state; int power_down; int srp_success; scalar_t__ snpsid; TYPE_11__* core_global_regs; int /*<<< orphan*/  lock; TYPE_2__* core_params; scalar_t__ adp_enable; int /*<<< orphan*/  lx_state; } ;
typedef  TYPE_10__ dwc_otg_core_if_t ;
struct TYPE_23__ {int /*<<< orphan*/  gotgint; int /*<<< orphan*/  gintmsk; int /*<<< orphan*/  gotgctl; int /*<<< orphan*/  gpwrdn; } ;
typedef  TYPE_11__ dwc_otg_core_global_regs_t ;
struct TYPE_25__ {scalar_t__ phy_type; scalar_t__ i2c_enable; } ;

/* Variables and functions */
 scalar_t__ A_HOST ; 
 scalar_t__ A_PERIPHERAL ; 
 scalar_t__ B_HOST ; 
 scalar_t__ B_PERIPHERAL ; 
 int /*<<< orphan*/  DBG_ANY ; 
 int /*<<< orphan*/  DBG_CIL ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  DWC_OTG_L0 ; 
 scalar_t__ DWC_PHY_TYPE_PARAM_FS ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ OTG_CORE_REV_3_00a ; 
 int /*<<< orphan*/  __DWC_ERROR (char*) ; 
 int /*<<< orphan*/  cil_hcd_disconnect (TYPE_10__*) ; 
 int /*<<< orphan*/  cil_hcd_start (TYPE_10__*) ; 
 int /*<<< orphan*/  cil_pcd_resume (TYPE_10__*) ; 
 int /*<<< orphan*/  cil_pcd_start (TYPE_10__*) ; 
 int /*<<< orphan*/  cil_pcd_stop (TYPE_10__*) ; 
 int /*<<< orphan*/  dwc_otg_adp_sense_start (TYPE_10__*) ; 
 scalar_t__ dwc_otg_is_device_mode (TYPE_10__*) ; 
 scalar_t__ dwc_otg_is_host_mode (TYPE_10__*) ; 
 int /*<<< orphan*/  dwc_udelay (int) ; 
 int /*<<< orphan*/  op_state_str (TYPE_10__*) ; 

int32_t dwc_otg_handle_otg_intr(dwc_otg_core_if_t * core_if)
{
	dwc_otg_core_global_regs_t *global_regs = core_if->core_global_regs;
	gotgint_data_t gotgint;
	gotgctl_data_t gotgctl;
	gintmsk_data_t gintmsk;
	gpwrdn_data_t gpwrdn;

	gotgint.d32 = DWC_READ_REG32(&global_regs->gotgint);
	gotgctl.d32 = DWC_READ_REG32(&global_regs->gotgctl);
	DWC_DEBUGPL(DBG_CIL, "++OTG Interrupt gotgint=%0x [%s]\n", gotgint.d32,
		    op_state_str(core_if));

	if (gotgint.b.sesenddet) {
		DWC_DEBUGPL(DBG_ANY, " ++OTG Interrupt: "
			    "Session End Detected++ (%s)\n",
			    op_state_str(core_if));
		gotgctl.d32 = DWC_READ_REG32(&global_regs->gotgctl);

		if (core_if->op_state == B_HOST) {
			cil_pcd_start(core_if);
			core_if->op_state = B_PERIPHERAL;
		} else {
			/* If not B_HOST and Device HNP still set. HNP
			 * Did not succeed!*/
			if (gotgctl.b.devhnpen) {
				DWC_DEBUGPL(DBG_ANY, "Session End Detected\n");
				__DWC_ERROR("Device Not Connected/Responding!\n");
			}

			/* If Session End Detected the B-Cable has
			 * been disconnected. */
			/* Reset PCD and Gadget driver to a
			 * clean state. */
			core_if->lx_state = DWC_OTG_L0;
			DWC_SPINUNLOCK(core_if->lock);
			cil_pcd_stop(core_if);
			DWC_SPINLOCK(core_if->lock);

			if (core_if->adp_enable) {
				if (core_if->power_down == 2) {
					gpwrdn.d32 = 0;
					gpwrdn.b.pwrdnswtch = 1;
					DWC_MODIFY_REG32(&core_if->
							 core_global_regs->
							 gpwrdn, gpwrdn.d32, 0);
				}

				gpwrdn.d32 = 0;
				gpwrdn.b.pmuintsel = 1;
				gpwrdn.b.pmuactv = 1;
				DWC_MODIFY_REG32(&core_if->core_global_regs->
						 gpwrdn, 0, gpwrdn.d32);

				dwc_otg_adp_sense_start(core_if);
			}
		}

		gotgctl.d32 = 0;
		gotgctl.b.devhnpen = 1;
		DWC_MODIFY_REG32(&global_regs->gotgctl, gotgctl.d32, 0);
	}
	if (gotgint.b.sesreqsucstschng) {
		DWC_DEBUGPL(DBG_ANY, " ++OTG Interrupt: "
			    "Session Reqeust Success Status Change++\n");
		gotgctl.d32 = DWC_READ_REG32(&global_regs->gotgctl);
		if (gotgctl.b.sesreqscs) {

			if ((core_if->core_params->phy_type ==
			     DWC_PHY_TYPE_PARAM_FS) && (core_if->core_params->i2c_enable)) {
				core_if->srp_success = 1;
			} else {
				DWC_SPINUNLOCK(core_if->lock);
				cil_pcd_resume(core_if);
				DWC_SPINLOCK(core_if->lock);
				/* Clear Session Request */
				gotgctl.d32 = 0;
				gotgctl.b.sesreq = 1;
				DWC_MODIFY_REG32(&global_regs->gotgctl,
						 gotgctl.d32, 0);
			}
		}
	}
	if (gotgint.b.hstnegsucstschng) {
		/* Print statements during the HNP interrupt handling
		 * can cause it to fail.*/
		gotgctl.d32 = DWC_READ_REG32(&global_regs->gotgctl);
		/* WA for 3.00a- HW is not setting cur_mode, even sometimes
		 * this does not help*/
		if (core_if->snpsid >= OTG_CORE_REV_3_00a)
			dwc_udelay(100);
		if (gotgctl.b.hstnegscs) {
			if (dwc_otg_is_host_mode(core_if)) {
				core_if->op_state = B_HOST;
				/*
				 * Need to disable SOF interrupt immediately.
				 * When switching from device to host, the PCD
				 * interrupt handler won't handle the
				 * interrupt if host mode is already set. The
				 * HCD interrupt handler won't get called if
				 * the HCD state is HALT. This means that the
				 * interrupt does not get handled and Linux
				 * complains loudly.
				 */
				gintmsk.d32 = 0;
				gintmsk.b.sofintr = 1;
				DWC_MODIFY_REG32(&global_regs->gintmsk,
						 gintmsk.d32, 0);
				/* Call callback function with spin lock released */
				DWC_SPINUNLOCK(core_if->lock);
				cil_pcd_stop(core_if);
				/*
				 * Initialize the Core for Host mode.
				 */
				cil_hcd_start(core_if);
				DWC_SPINLOCK(core_if->lock);
				core_if->op_state = B_HOST;
			}
		} else {
			gotgctl.d32 = 0;
			gotgctl.b.hnpreq = 1;
			gotgctl.b.devhnpen = 1;
			DWC_MODIFY_REG32(&global_regs->gotgctl, gotgctl.d32, 0);
			DWC_DEBUGPL(DBG_ANY, "HNP Failed\n");
			__DWC_ERROR("Device Not Connected/Responding\n");
		}
	}
	if (gotgint.b.hstnegdet) {
		/* The disconnect interrupt is set at the same time as
		 * Host Negotiation Detected.  During the mode
		 * switch all interrupts are cleared so the disconnect
		 * interrupt handler will not get executed.
		 */
		DWC_DEBUGPL(DBG_ANY, " ++OTG Interrupt: "
			    "Host Negotiation Detected++ (%s)\n",
			    (dwc_otg_is_host_mode(core_if) ? "Host" :
			     "Device"));
		if (dwc_otg_is_device_mode(core_if)) {
			DWC_DEBUGPL(DBG_ANY, "a_suspend->a_peripheral (%d)\n",
				    core_if->op_state);
			DWC_SPINUNLOCK(core_if->lock);
			cil_hcd_disconnect(core_if);
			cil_pcd_start(core_if);
			DWC_SPINLOCK(core_if->lock);
			core_if->op_state = A_PERIPHERAL;
		} else {
			/*
			 * Need to disable SOF interrupt immediately. When
			 * switching from device to host, the PCD interrupt
			 * handler won't handle the interrupt if host mode is
			 * already set. The HCD interrupt handler won't get
			 * called if the HCD state is HALT. This means that
			 * the interrupt does not get handled and Linux
			 * complains loudly.
			 */
			gintmsk.d32 = 0;
			gintmsk.b.sofintr = 1;
			DWC_MODIFY_REG32(&global_regs->gintmsk, gintmsk.d32, 0);
			DWC_SPINUNLOCK(core_if->lock);
			cil_pcd_stop(core_if);
			cil_hcd_start(core_if);
			DWC_SPINLOCK(core_if->lock);
			core_if->op_state = A_HOST;
		}
	}
	if (gotgint.b.adevtoutchng) {
		DWC_DEBUGPL(DBG_ANY, " ++OTG Interrupt: "
			    "A-Device Timeout Change++\n");
	}
	if (gotgint.b.debdone) {
		DWC_DEBUGPL(DBG_ANY, " ++OTG Interrupt: " "Debounce Done++\n");
	}

	/* Clear GOTGINT */
	DWC_WRITE_REG32(&core_if->core_global_regs->gotgint, gotgint.d32);

	return 1;
}