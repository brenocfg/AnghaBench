#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int restoremode; } ;
struct TYPE_11__ {TYPE_1__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_4__ pcgcctl_data_t ;
typedef  int int32_t ;
struct TYPE_9__ {int wkupintr; } ;
struct TYPE_12__ {int /*<<< orphan*/  d32; TYPE_2__ b; } ;
typedef  TYPE_5__ gintmsk_data_t ;
struct TYPE_13__ {TYPE_3__* core_global_regs; int /*<<< orphan*/  pcgcctl; } ;
typedef  TYPE_6__ dwc_otg_core_if_t ;
struct TYPE_10__ {int /*<<< orphan*/  gintmsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ANY ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ ) ; 

int32_t dwc_otg_handle_restore_done_intr(dwc_otg_core_if_t * core_if)
{
	pcgcctl_data_t pcgcctl;
	DWC_DEBUGPL(DBG_ANY, "++Restore Done Interrupt++\n");

	//TODO De-assert restore signal. 8.a
	pcgcctl.d32 = DWC_READ_REG32(core_if->pcgcctl);
	if (pcgcctl.b.restoremode == 1) {
		gintmsk_data_t gintmsk = {.d32 = 0 };
		/*
		 * If restore mode is Remote Wakeup,
		 * unmask Remote Wakeup interrupt.
		 */
		gintmsk.b.wkupintr = 1;
		DWC_MODIFY_REG32(&core_if->core_global_regs->gintmsk,
				 0, gintmsk.d32);
	}

	return 1;
}