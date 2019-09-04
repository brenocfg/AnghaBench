#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ bmRequestType; int /*<<< orphan*/  wValue; } ;
typedef  TYPE_4__ usb_device_request_t ;
struct TYPE_17__ {TYPE_1__* setup_pkt; } ;
typedef  TYPE_5__ dwc_otg_pcd_t ;
struct TYPE_18__ {TYPE_3__* dev_global_regs; } ;
typedef  TYPE_6__ dwc_otg_dev_if_t ;
struct TYPE_14__ {int /*<<< orphan*/  devaddr; } ;
struct TYPE_19__ {int /*<<< orphan*/  d32; TYPE_2__ b; } ;
typedef  TYPE_7__ dcfg_data_t ;
struct TYPE_15__ {int /*<<< orphan*/  dcfg; } ;
struct TYPE_13__ {TYPE_4__ req; } ;
struct TYPE_12__ {TYPE_6__* dev_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_10__* GET_CORE_IF (TYPE_5__*) ; 
 int /*<<< orphan*/  UGETW (int /*<<< orphan*/ ) ; 
 scalar_t__ UT_DEVICE ; 
 int /*<<< orphan*/  do_setup_in_status_phase (TYPE_5__*) ; 

__attribute__((used)) static inline void do_set_address(dwc_otg_pcd_t * pcd)
{
	dwc_otg_dev_if_t *dev_if = GET_CORE_IF(pcd)->dev_if;
	usb_device_request_t ctrl = pcd->setup_pkt->req;

	if (ctrl.bmRequestType == UT_DEVICE) {
		dcfg_data_t dcfg = {.d32 = 0 };

#ifdef DEBUG_EP0
//                      DWC_DEBUGPL(DBG_PCDV, "SET_ADDRESS:%d\n", ctrl.wValue);
#endif
		dcfg.b.devaddr = UGETW(ctrl.wValue);
		DWC_MODIFY_REG32(&dev_if->dev_global_regs->dcfg, 0, dcfg.d32);
		do_setup_in_status_phase(pcd);
	}
}