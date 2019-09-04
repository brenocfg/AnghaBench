#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ prtres; } ;
struct TYPE_9__ {int /*<<< orphan*/  d32; TYPE_2__ b; } ;
typedef  TYPE_3__ hprt0_data_t ;
struct TYPE_10__ {int /*<<< orphan*/  lx_state; TYPE_1__* host_if; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_7__ {int /*<<< orphan*/  hprt0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ANY ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_OTG_L0 ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cil_hcd_resume (TYPE_4__*) ; 
 int /*<<< orphan*/  dwc_otg_read_hprt0 (TYPE_4__*) ; 

void w_wakeup_detected(void *p)
{
	dwc_otg_core_if_t *core_if = (dwc_otg_core_if_t *) p;
	/*
	 * Clear the Resume after 70ms. (Need 20 ms minimum. Use 70 ms
	 * so that OPT tests pass with all PHYs).
	 */
	hprt0_data_t hprt0 = {.d32 = 0 };
#if 0
	pcgcctl_data_t pcgcctl = {.d32 = 0 };
	/* Restart the Phy Clock */
	pcgcctl.b.stoppclk = 1;
	DWC_MODIFY_REG32(core_if->pcgcctl, pcgcctl.d32, 0);
	dwc_udelay(10);
#endif //0
	hprt0.d32 = dwc_otg_read_hprt0(core_if);
	DWC_DEBUGPL(DBG_ANY, "Resume: HPRT0=%0x\n", hprt0.d32);
//      dwc_mdelay(70);
	hprt0.b.prtres = 0;	/* Resume */
	DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
	DWC_DEBUGPL(DBG_ANY, "Clear Resume: HPRT0=%0x\n",
		    DWC_READ_REG32(core_if->host_if->hprt0));

	cil_hcd_resume(core_if);

	/** Change to L0 state*/
	core_if->lx_state = DWC_OTG_L0;
}