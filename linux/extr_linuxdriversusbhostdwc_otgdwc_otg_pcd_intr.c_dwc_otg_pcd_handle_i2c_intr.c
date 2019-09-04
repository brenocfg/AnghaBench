#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_7__ {int i2cintr; } ;
struct TYPE_10__ {scalar_t__ d32; TYPE_1__ b; } ;
typedef  TYPE_4__ gintsts_data_t ;
struct TYPE_8__ {int i2cintr; } ;
struct TYPE_11__ {int /*<<< orphan*/  d32; TYPE_2__ b; } ;
typedef  TYPE_5__ gintmsk_data_t ;
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
struct TYPE_12__ {TYPE_3__* core_global_regs; } ;
struct TYPE_9__ {int /*<<< orphan*/  gintsts; int /*<<< orphan*/  gintmsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_PRINTF (char*,char*) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_6__* GET_CORE_IF (int /*<<< orphan*/ *) ; 

int32_t dwc_otg_pcd_handle_i2c_intr(dwc_otg_pcd_t * pcd)
{
	gintmsk_data_t intr_mask = {.d32 = 0 };
	gintsts_data_t gintsts;

	DWC_PRINTF("INTERRUPT Handler not implemented for %s\n", "i2cintr");
	intr_mask.b.i2cintr = 1;
	DWC_MODIFY_REG32(&GET_CORE_IF(pcd)->core_global_regs->gintmsk,
			 intr_mask.d32, 0);

	/* Clear interrupt */
	gintsts.d32 = 0;
	gintsts.b.i2cintr = 1;
	DWC_WRITE_REG32(&GET_CORE_IF(pcd)->core_global_regs->gintsts,
			gintsts.d32);
	return 1;
}