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
typedef  int int32_t ;
struct TYPE_14__ {int prtpwr; } ;
struct TYPE_16__ {scalar_t__ d32; TYPE_3__ b; } ;
typedef  TYPE_5__ hprt0_data_t ;
struct TYPE_12__ {int sessreqintr; } ;
struct TYPE_17__ {scalar_t__ d32; TYPE_1__ b; } ;
typedef  TYPE_6__ gintsts_data_t ;
struct TYPE_18__ {TYPE_2__* core_global_regs; TYPE_4__* host_if; } ;
typedef  TYPE_7__ dwc_otg_core_if_t ;
struct TYPE_15__ {int /*<<< orphan*/ * hprt0; } ;
struct TYPE_13__ {int /*<<< orphan*/  gintsts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ANY ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DWC_PRINTF (char*) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cil_hcd_session_start (TYPE_7__*) ; 
 scalar_t__ dwc_otg_is_device_mode (TYPE_7__*) ; 
 scalar_t__ dwc_otg_read_hprt0 (TYPE_7__*) ; 

int32_t dwc_otg_handle_session_req_intr(dwc_otg_core_if_t * core_if)
{
	gintsts_data_t gintsts;

#ifndef DWC_HOST_ONLY
	DWC_DEBUGPL(DBG_ANY, "++Session Request Interrupt++\n");

	if (dwc_otg_is_device_mode(core_if)) {
		DWC_PRINTF("SRP: Device mode\n");
	} else {
		hprt0_data_t hprt0;
		DWC_PRINTF("SRP: Host mode\n");

		/* Turn on the port power bit. */
		hprt0.d32 = dwc_otg_read_hprt0(core_if);
		hprt0.b.prtpwr = 1;
		DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);

		/* Start the Connection timer. So a message can be displayed
		 * if connect does not occur within 10 seconds. */
		cil_hcd_session_start(core_if);
	}
#endif

	/* Clear interrupt */
	gintsts.d32 = 0;
	gintsts.b.sessreqintr = 1;
	DWC_WRITE_REG32(&core_if->core_global_regs->gintsts, gintsts.d32);

	return 1;
}