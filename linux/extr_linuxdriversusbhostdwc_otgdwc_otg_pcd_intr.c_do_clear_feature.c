#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bmRequestType; int /*<<< orphan*/  wLength; int /*<<< orphan*/  bRequest; } ;
typedef  TYPE_2__ usb_device_request_t ;
struct TYPE_11__ {int /*<<< orphan*/  remote_wakeup_enable; TYPE_1__* setup_pkt; } ;
typedef  TYPE_3__ dwc_otg_pcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_pcd_ep_t ;
struct TYPE_9__ {TYPE_2__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_E_NOT_SUPPORTED ; 
#define  UF_DEVICE_REMOTE_WAKEUP 131 
#define  UF_TEST_MODE 130 
 int /*<<< orphan*/  UGETW (int /*<<< orphan*/ ) ; 
#define  UT_DEVICE 129 
#define  UT_ENDPOINT 128 
 int UT_GET_RECIPIENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_setup_in_status_phase (TYPE_3__*) ; 
 int /*<<< orphan*/  ep0_do_stall (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_ep_by_addr (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcd_clear_halt (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void do_clear_feature(dwc_otg_pcd_t * pcd)
{
	usb_device_request_t ctrl = pcd->setup_pkt->req;
	dwc_otg_pcd_ep_t *ep = 0;

	DWC_DEBUGPL(DBG_PCD,
		    "CLEAR_FEATURE:%02x.%02x v%04x i%04x l%04x\n",
		    ctrl.bmRequestType, ctrl.bRequest,
		    UGETW(ctrl.wValue), UGETW(ctrl.wIndex),
		    UGETW(ctrl.wLength));

	switch (UT_GET_RECIPIENT(ctrl.bmRequestType)) {
	case UT_DEVICE:
		switch (UGETW(ctrl.wValue)) {
		case UF_DEVICE_REMOTE_WAKEUP:
			pcd->remote_wakeup_enable = 0;
			break;

		case UF_TEST_MODE:
			/** @todo Add CLEAR_FEATURE for TEST modes. */
			break;

		default:
			ep0_do_stall(pcd, -DWC_E_NOT_SUPPORTED);
			return;
		}
		do_setup_in_status_phase(pcd);
		break;

	case UT_ENDPOINT:
		ep = get_ep_by_addr(pcd, UGETW(ctrl.wIndex));
		if (ep == 0) {
			ep0_do_stall(pcd, -DWC_E_NOT_SUPPORTED);
			return;
		}

		pcd_clear_halt(pcd, ep);

		break;
	}
}