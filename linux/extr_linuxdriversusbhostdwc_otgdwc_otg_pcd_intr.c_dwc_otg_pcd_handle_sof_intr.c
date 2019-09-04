#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_6__ {int sofintr; } ;
struct TYPE_8__ {scalar_t__ d32; TYPE_1__ b; } ;
typedef  TYPE_3__ gintsts_data_t ;
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
struct TYPE_9__ {TYPE_2__* core_global_regs; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_7__ {int /*<<< orphan*/  gintsts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_4__* GET_CORE_IF (int /*<<< orphan*/ *) ; 

int32_t dwc_otg_pcd_handle_sof_intr(dwc_otg_pcd_t * pcd)
{
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);

	gintsts_data_t gintsts;

	DWC_DEBUGPL(DBG_PCD, "SOF\n");

	/* Clear interrupt */
	gintsts.d32 = 0;
	gintsts.b.sofintr = 1;
	DWC_WRITE_REG32(&core_if->core_global_regs->gintsts, gintsts.d32);

	return 1;
}