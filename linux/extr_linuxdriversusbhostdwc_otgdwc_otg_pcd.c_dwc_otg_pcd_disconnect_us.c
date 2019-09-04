#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
struct TYPE_11__ {TYPE_2__* dev_if; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_8__ {int sftdiscon; } ;
struct TYPE_12__ {int /*<<< orphan*/  d32; TYPE_1__ b; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ dctl_data_t ;
struct TYPE_10__ {int /*<<< orphan*/  dctl; } ;
struct TYPE_9__ {TYPE_3__* dev_global_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_PRINTF (char*,...) ; 
 TYPE_4__* GET_CORE_IF (int /*<<< orphan*/ *) ; 
 scalar_t__ dwc_otg_is_device_mode (TYPE_4__*) ; 
 int /*<<< orphan*/  dwc_udelay (int) ; 

void dwc_otg_pcd_disconnect_us(dwc_otg_pcd_t * pcd, int no_of_usecs)
{
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);
	dctl_data_t dctl = { 0 };

	if (dwc_otg_is_device_mode(core_if)) {
		dctl.b.sftdiscon = 1;
		DWC_PRINTF("Soft disconnect for %d useconds\n",no_of_usecs);
		DWC_MODIFY_REG32(&core_if->dev_if->dev_global_regs->dctl, 0, dctl.d32);
		dwc_udelay(no_of_usecs);
		DWC_MODIFY_REG32(&core_if->dev_if->dev_global_regs->dctl, dctl.d32,0);

	} else{
		DWC_PRINTF("NOT SUPPORTED IN HOST MODE\n");
	}
	return;

}