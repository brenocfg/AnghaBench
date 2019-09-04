#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {scalar_t__ conidsts; } ;
struct TYPE_13__ {TYPE_2__ b; scalar_t__ d32; } ;
typedef  TYPE_3__ gotgctl_data_t ;
struct TYPE_14__ {int /*<<< orphan*/  op_state; TYPE_1__* core_global_regs; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_11__ {int /*<<< orphan*/  gotgctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_HOST ; 
 int /*<<< orphan*/  B_PERIPHERAL ; 
 int /*<<< orphan*/  DBG_CIL ; 
 int /*<<< orphan*/  DWC_ASSERT (int,char*) ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  DWC_PRINTF (char*,char*) ; 
 scalar_t__ DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cil_hcd_start (TYPE_4__*) ; 
 int /*<<< orphan*/  cil_pcd_start (TYPE_4__*) ; 
 int /*<<< orphan*/  dwc_mdelay (int) ; 
 int /*<<< orphan*/  dwc_otg_core_init (TYPE_4__*) ; 
 int /*<<< orphan*/  dwc_otg_enable_global_interrupts (TYPE_4__*) ; 
 int /*<<< orphan*/  dwc_otg_is_device_mode (TYPE_4__*) ; 
 scalar_t__ dwc_otg_is_host_mode (TYPE_4__*) ; 

void w_conn_id_status_change(void *p)
{
	dwc_otg_core_if_t *core_if = p;
	uint32_t count = 0;
	gotgctl_data_t gotgctl = {.d32 = 0 };

	gotgctl.d32 = DWC_READ_REG32(&core_if->core_global_regs->gotgctl);
	DWC_DEBUGPL(DBG_CIL, "gotgctl=%0x\n", gotgctl.d32);
	DWC_DEBUGPL(DBG_CIL, "gotgctl.b.conidsts=%d\n", gotgctl.b.conidsts);

	/* B-Device connector (Device Mode) */
	if (gotgctl.b.conidsts) {
		/* Wait for switch to device mode. */
		while (!dwc_otg_is_device_mode(core_if)) {
			DWC_PRINTF("Waiting for Peripheral Mode, Mode=%s\n",
				   (dwc_otg_is_host_mode(core_if) ? "Host" :
				    "Peripheral"));
			dwc_mdelay(100);
			if (++count > 10000)
				break;
		}
		DWC_ASSERT(++count < 10000,
			   "Connection id status change timed out");
		core_if->op_state = B_PERIPHERAL;
		dwc_otg_core_init(core_if);
		dwc_otg_enable_global_interrupts(core_if);
		cil_pcd_start(core_if);
	} else {
		/* A-Device connector (Host Mode) */
		while (!dwc_otg_is_host_mode(core_if)) {
			DWC_PRINTF("Waiting for Host Mode, Mode=%s\n",
				   (dwc_otg_is_host_mode(core_if) ? "Host" :
				    "Peripheral"));
			dwc_mdelay(100);
			if (++count > 10000)
				break;
		}
		DWC_ASSERT(++count < 10000,
			   "Connection id status change timed out");
		core_if->op_state = A_HOST;
		/*
		 * Initialize the Core for Host mode.
		 */
		dwc_otg_core_init(core_if);
		dwc_otg_enable_global_interrupts(core_if);
		cil_hcd_start(core_if);
	}
}