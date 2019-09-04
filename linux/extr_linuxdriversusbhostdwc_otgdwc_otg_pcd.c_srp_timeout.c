#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_13__ {int pwrdnswtch; int pmuintsel; int pmuactv; } ;
struct TYPE_18__ {scalar_t__ d32; TYPE_1__ b; } ;
typedef  TYPE_6__ gpwrdn_data_t ;
struct TYPE_17__ {scalar_t__ bsesvld; int sesreq; } ;
struct TYPE_19__ {scalar_t__ d32; TYPE_5__ b; } ;
typedef  TYPE_7__ gotgctl_data_t ;
struct TYPE_20__ {int power_down; scalar_t__ srp_success; TYPE_4__* core_global_regs; TYPE_3__* pcd_cb; TYPE_2__* core_params; int /*<<< orphan*/  op_state; scalar_t__ adp_enable; scalar_t__ srp_timer_started; } ;
typedef  TYPE_8__ dwc_otg_core_if_t ;
struct TYPE_16__ {int /*<<< orphan*/  gotgctl; int /*<<< orphan*/  gpwrdn; } ;
struct TYPE_15__ {int /*<<< orphan*/  p; int /*<<< orphan*/  (* resume_wakeup ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {scalar_t__ phy_type; scalar_t__ i2c_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_PERIPHERAL ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ DWC_PHY_TYPE_PARAM_FS ; 
 int /*<<< orphan*/  DWC_PRINTF (char*,...) ; 
 scalar_t__ DWC_READ_REG32 (int /*<<< orphan*/  volatile*) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/  volatile*,scalar_t__) ; 
 int /*<<< orphan*/  __DWC_ERROR (char*) ; 
 int /*<<< orphan*/  cil_pcd_start (TYPE_8__*) ; 
 int /*<<< orphan*/  dwc_otg_adp_probe_start (TYPE_8__*) ; 
 int /*<<< orphan*/  dwc_otg_core_init (TYPE_8__*) ; 
 int /*<<< orphan*/  dwc_otg_enable_global_interrupts (TYPE_8__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void srp_timeout(void *ptr)
{
	gotgctl_data_t gotgctl;
	dwc_otg_core_if_t *core_if = (dwc_otg_core_if_t *) ptr;
	volatile uint32_t *addr = &core_if->core_global_regs->gotgctl;

	gotgctl.d32 = DWC_READ_REG32(addr);

	core_if->srp_timer_started = 0;

	if (core_if->adp_enable) {
		if (gotgctl.b.bsesvld == 0) {
			gpwrdn_data_t gpwrdn = {.d32 = 0 };
			DWC_PRINTF("SRP Timeout BSESSVLD = 0\n");
			/* Power off the core */
			if (core_if->power_down == 2) {
				gpwrdn.b.pwrdnswtch = 1;
				DWC_MODIFY_REG32(&core_if->
						 core_global_regs->gpwrdn,
						 gpwrdn.d32, 0);
			}

			gpwrdn.d32 = 0;
			gpwrdn.b.pmuintsel = 1;
			gpwrdn.b.pmuactv = 1;
			DWC_MODIFY_REG32(&core_if->core_global_regs->gpwrdn, 0,
					 gpwrdn.d32);
			dwc_otg_adp_probe_start(core_if);
		} else {
			DWC_PRINTF("SRP Timeout BSESSVLD = 1\n");
			core_if->op_state = B_PERIPHERAL;
			dwc_otg_core_init(core_if);
			dwc_otg_enable_global_interrupts(core_if);
			cil_pcd_start(core_if);
		}
	}

	if ((core_if->core_params->phy_type == DWC_PHY_TYPE_PARAM_FS) &&
	    (core_if->core_params->i2c_enable)) {
		DWC_PRINTF("SRP Timeout\n");

		if ((core_if->srp_success) && (gotgctl.b.bsesvld)) {
			if (core_if->pcd_cb && core_if->pcd_cb->resume_wakeup) {
				core_if->pcd_cb->resume_wakeup(core_if->pcd_cb->p);
			}

			/* Clear Session Request */
			gotgctl.d32 = 0;
			gotgctl.b.sesreq = 1;
			DWC_MODIFY_REG32(&core_if->core_global_regs->gotgctl,
					 gotgctl.d32, 0);

			core_if->srp_success = 0;
		} else {
			__DWC_ERROR("Device not connected/responding\n");
			gotgctl.b.sesreq = 0;
			DWC_WRITE_REG32(addr, gotgctl.d32);
		}
	} else if (gotgctl.b.sesreq) {
		DWC_PRINTF("SRP Timeout\n");

		__DWC_ERROR("Device not connected/responding\n");
		gotgctl.b.sesreq = 0;
		DWC_WRITE_REG32(addr, gotgctl.d32);
	} else {
		DWC_PRINTF(" SRP GOTGCTL=%0x\n", gotgctl.d32);
	}
}