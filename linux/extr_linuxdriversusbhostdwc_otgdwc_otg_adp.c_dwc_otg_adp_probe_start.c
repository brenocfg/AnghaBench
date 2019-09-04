#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_13__ {int sts_chngint_msk; int srp_det_msk; int /*<<< orphan*/  idsts; } ;
struct TYPE_16__ {scalar_t__ d32; TYPE_2__ b; } ;
typedef  TYPE_5__ gpwrdn_data_t ;
struct TYPE_12__ {int probe_enabled; } ;
struct TYPE_17__ {TYPE_3__* core_global_regs; TYPE_1__ adp; } ;
typedef  TYPE_6__ dwc_otg_core_if_t ;
struct TYPE_15__ {int adpres; int adp_tmout_int_msk; int adp_prb_int_msk; int prb_dschg; int prb_delta; int prb_per; int adpen; int enaprb; } ;
struct TYPE_18__ {scalar_t__ d32; TYPE_4__ b; } ;
typedef  TYPE_7__ adpctl_data_t ;
struct TYPE_14__ {int /*<<< orphan*/  gpwrdn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DWC_PRINTF (char*) ; 
 scalar_t__ DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 scalar_t__ dwc_otg_adp_read_reg (TYPE_6__*) ; 
 int /*<<< orphan*/  dwc_otg_adp_write_reg (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  dwc_otg_disable_global_interrupts (TYPE_6__*) ; 

uint32_t dwc_otg_adp_probe_start(dwc_otg_core_if_t * core_if)
{

	adpctl_data_t adpctl = {.d32 = 0};
	gpwrdn_data_t gpwrdn;
#if 0
	adpctl_data_t adpctl_int = {.d32 = 0, .b.adp_prb_int = 1,
								.b.adp_sns_int = 1, b.adp_tmout_int};
#endif
	dwc_otg_disable_global_interrupts(core_if);
	DWC_PRINTF("ADP Probe Start\n");
	core_if->adp.probe_enabled = 1;

	adpctl.b.adpres = 1;
	dwc_otg_adp_write_reg(core_if, adpctl.d32);

	while (adpctl.b.adpres) {
		adpctl.d32 = dwc_otg_adp_read_reg(core_if);
	}

	adpctl.d32 = 0;
	gpwrdn.d32 = DWC_READ_REG32(&core_if->core_global_regs->gpwrdn);

	/* In Host mode unmask SRP detected interrupt */
	gpwrdn.d32 = 0;
	gpwrdn.b.sts_chngint_msk = 1;
	if (!gpwrdn.b.idsts) {
		gpwrdn.b.srp_det_msk = 1;
	}
	DWC_MODIFY_REG32(&core_if->core_global_regs->gpwrdn, 0, gpwrdn.d32);

	adpctl.b.adp_tmout_int_msk = 1;
	adpctl.b.adp_prb_int_msk = 1;
	adpctl.b.prb_dschg = 1;
	adpctl.b.prb_delta = 1;
	adpctl.b.prb_per = 1;
	adpctl.b.adpen = 1;
	adpctl.b.enaprb = 1;

	dwc_otg_adp_write_reg(core_if, adpctl.d32);
	DWC_PRINTF("ADP Probe Finish\n");
	return 0;
}