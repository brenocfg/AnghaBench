#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int test_mode; } ;
typedef  TYPE_4__ dwc_otg_pcd_t ;
struct TYPE_13__ {TYPE_3__* dev_if; } ;
typedef  TYPE_5__ dwc_otg_core_if_t ;
struct TYPE_9__ {int tstctl; } ;
struct TYPE_14__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_6__ dctl_data_t ;
struct TYPE_11__ {TYPE_2__* dev_global_regs; } ;
struct TYPE_10__ {int /*<<< orphan*/  dctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* GET_CORE_IF (TYPE_4__*) ; 

void do_test_mode(void *data)
{
	dctl_data_t dctl;
	dwc_otg_pcd_t *pcd = (dwc_otg_pcd_t *) data;
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);
	int test_mode = pcd->test_mode;

//        DWC_WARN("%s() has not been tested since being rewritten!\n", __func__);

	dctl.d32 = DWC_READ_REG32(&core_if->dev_if->dev_global_regs->dctl);
	switch (test_mode) {
	case 1:		// TEST_J
		dctl.b.tstctl = 1;
		break;

	case 2:		// TEST_K
		dctl.b.tstctl = 2;
		break;

	case 3:		// TEST_SE0_NAK
		dctl.b.tstctl = 3;
		break;

	case 4:		// TEST_PACKET
		dctl.b.tstctl = 4;
		break;

	case 5:		// TEST_FORCE_ENABLE
		dctl.b.tstctl = 5;
		break;
	}
	DWC_WRITE_REG32(&core_if->dev_if->dev_global_regs->dctl, dctl.d32);
}