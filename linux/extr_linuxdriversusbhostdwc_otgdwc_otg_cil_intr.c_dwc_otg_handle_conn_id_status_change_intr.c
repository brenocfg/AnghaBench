#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_10__ {int conidstschng; } ;
struct TYPE_13__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_4__ gintsts_data_t ;
struct TYPE_12__ {int sofintr; } ;
struct TYPE_14__ {int /*<<< orphan*/  d32; TYPE_3__ b; } ;
typedef  TYPE_5__ gintmsk_data_t ;
struct TYPE_15__ {TYPE_2__* core_global_regs; int /*<<< orphan*/  lock; int /*<<< orphan*/  wq_otg; } ;
typedef  TYPE_6__ dwc_otg_core_if_t ;
struct TYPE_11__ {int /*<<< orphan*/  gintsts; int /*<<< orphan*/  gintmsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_CIL ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_SPINLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WORKQ_SCHEDULE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,char*) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dwc_otg_is_host_mode (TYPE_6__*) ; 
 int /*<<< orphan*/  w_conn_id_status_change ; 

int32_t dwc_otg_handle_conn_id_status_change_intr(dwc_otg_core_if_t * core_if)
{

	/*
	 * Need to disable SOF interrupt immediately. If switching from device
	 * to host, the PCD interrupt handler won't handle the interrupt if
	 * host mode is already set. The HCD interrupt handler won't get
	 * called if the HCD state is HALT. This means that the interrupt does
	 * not get handled and Linux complains loudly.
	 */
	gintmsk_data_t gintmsk = {.d32 = 0 };
	gintsts_data_t gintsts = {.d32 = 0 };

	gintmsk.b.sofintr = 1;
	DWC_MODIFY_REG32(&core_if->core_global_regs->gintmsk, gintmsk.d32, 0);

	DWC_DEBUGPL(DBG_CIL,
		    " ++Connector ID Status Change Interrupt++  (%s)\n",
		    (dwc_otg_is_host_mode(core_if) ? "Host" : "Device"));

	DWC_SPINUNLOCK(core_if->lock);

	/*
	 * Need to schedule a work, as there are possible DELAY function calls
	 * Release lock before scheduling workq as it holds spinlock during scheduling
	 */

	DWC_WORKQ_SCHEDULE(core_if->wq_otg, w_conn_id_status_change,
			   core_if, "connection id status change");
	DWC_SPINLOCK(core_if->lock);

	/* Set flag and clear interrupt */
	gintsts.b.conidstschng = 1;
	DWC_WRITE_REG32(&core_if->core_global_regs->gintsts, gintsts.d32);

	return 1;
}