#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_5__ {int erlysuspend; } ;
struct TYPE_7__ {scalar_t__ d32; TYPE_1__ b; } ;
typedef  TYPE_3__ gintsts_data_t ;
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
struct TYPE_8__ {TYPE_2__* core_global_regs; } ;
struct TYPE_6__ {int /*<<< orphan*/  gintsts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_4__* GET_CORE_IF (int /*<<< orphan*/ *) ; 

int32_t dwc_otg_pcd_handle_early_suspend_intr(dwc_otg_pcd_t * pcd)
{
	gintsts_data_t gintsts;
#if defined(VERBOSE)
	DWC_PRINTF("Early Suspend Detected\n");
#endif

	/* Clear interrupt */
	gintsts.d32 = 0;
	gintsts.b.erlysuspend = 1;
	DWC_WRITE_REG32(&GET_CORE_IF(pcd)->core_global_regs->gintsts,
			gintsts.d32);
	return 1;
}