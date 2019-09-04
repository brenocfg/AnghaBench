#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_17__ {int pmuintsel; int pmuactv; } ;
struct TYPE_20__ {int /*<<< orphan*/  d32; TYPE_2__ b; } ;
typedef  TYPE_5__ gpwrdn_data_t ;
struct TYPE_16__ {scalar_t__ bsesvld; } ;
struct TYPE_21__ {TYPE_1__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_6__ gotgctl_data_t ;
struct TYPE_19__ {int adp_started; int initial_probe; } ;
struct TYPE_22__ {int /*<<< orphan*/  op_state; TYPE_4__ adp; TYPE_3__* core_global_regs; } ;
typedef  TYPE_7__ dwc_otg_core_if_t ;
struct TYPE_18__ {int /*<<< orphan*/  gpwrdn; int /*<<< orphan*/  gotgctl; int /*<<< orphan*/  gintsts; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_PERIPHERAL ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_PRINTF (char*) ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cil_pcd_start (TYPE_7__*) ; 
 int /*<<< orphan*/  dwc_otg_adp_probe_start (TYPE_7__*) ; 
 int /*<<< orphan*/  dwc_otg_core_init (TYPE_7__*) ; 
 int /*<<< orphan*/  dwc_otg_disable_global_interrupts (TYPE_7__*) ; 
 int /*<<< orphan*/  dwc_otg_dump_dev_registers (TYPE_7__*) ; 
 int /*<<< orphan*/  dwc_otg_dump_global_registers (TYPE_7__*) ; 
 int /*<<< orphan*/  dwc_otg_enable_global_interrupts (TYPE_7__*) ; 

void dwc_otg_adp_start(dwc_otg_core_if_t * core_if, uint8_t is_host)
{
	gpwrdn_data_t gpwrdn;

	DWC_PRINTF("ADP Initial Start\n");
	core_if->adp.adp_started = 1;

	DWC_WRITE_REG32(&core_if->core_global_regs->gintsts, 0xFFFFFFFF);
	dwc_otg_disable_global_interrupts(core_if);
	if (is_host) {
		DWC_PRINTF("HOST MODE\n");
		/* Enable Power Down Logic Interrupt*/
		gpwrdn.d32 = 0;
		gpwrdn.b.pmuintsel = 1;
		gpwrdn.b.pmuactv = 1;
		DWC_MODIFY_REG32(&core_if->core_global_regs->gpwrdn, 0, gpwrdn.d32);
		/* Initialize first ADP probe to obtain Ramp Time value */
		core_if->adp.initial_probe = 1;
		dwc_otg_adp_probe_start(core_if);
	} else {
		gotgctl_data_t gotgctl;
		gotgctl.d32 = DWC_READ_REG32(&core_if->core_global_regs->gotgctl);
		DWC_PRINTF("DEVICE MODE\n");
		if (gotgctl.b.bsesvld == 0) {
			/* Enable Power Down Logic Interrupt*/
			gpwrdn.d32 = 0;
			DWC_PRINTF("VBUS is not valid - start ADP probe\n");
			gpwrdn.b.pmuintsel = 1;
			gpwrdn.b.pmuactv = 1;
			DWC_MODIFY_REG32(&core_if->core_global_regs->gpwrdn, 0, gpwrdn.d32);
			core_if->adp.initial_probe = 1;
			dwc_otg_adp_probe_start(core_if);
		} else {
			DWC_PRINTF("VBUS is valid - initialize core as a Device\n");
			core_if->op_state = B_PERIPHERAL;
			dwc_otg_core_init(core_if);
			dwc_otg_enable_global_interrupts(core_if);
			cil_pcd_start(core_if);
			dwc_otg_dump_global_registers(core_if);
			dwc_otg_dump_dev_registers(core_if);
		}
	}
}