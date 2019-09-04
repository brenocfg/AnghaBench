#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bmRequestType; int /*<<< orphan*/  wLength; int /*<<< orphan*/  bRequest; } ;
typedef  TYPE_4__ usb_device_request_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_23__ {int devhnpen; int hnpreq; } ;
struct TYPE_25__ {int /*<<< orphan*/  d32; TYPE_3__ b; } ;
typedef  TYPE_5__ gotgctl_data_t ;
struct TYPE_26__ {int remote_wakeup_enable; int test_mode; int b_hnp_enable; int a_hnp_support; int a_alt_hnp_support; int /*<<< orphan*/  test_mode_tasklet; TYPE_1__* setup_pkt; } ;
typedef  TYPE_6__ dwc_otg_pcd_t ;
struct TYPE_27__ {int stopped; int /*<<< orphan*/  dwc_ep; } ;
typedef  TYPE_7__ dwc_otg_pcd_ep_t ;
struct TYPE_28__ {TYPE_2__* core_params; TYPE_9__* core_global_regs; } ;
typedef  TYPE_8__ dwc_otg_core_if_t ;
struct TYPE_29__ {int /*<<< orphan*/  gotgctl; } ;
typedef  TYPE_9__ dwc_otg_core_global_regs_t ;
struct TYPE_22__ {int /*<<< orphan*/  otg_cap; } ;
struct TYPE_21__ {TYPE_4__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCD ; 
 int /*<<< orphan*/  DBG_PCDV ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DWC_E_NOT_SUPPORTED ; 
 int /*<<< orphan*/  DWC_OTG_CAP_PARAM_HNP_SRP_CAPABLE ; 
 int /*<<< orphan*/  DWC_TASK_SCHEDULE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_8__* GET_CORE_IF (TYPE_6__*) ; 
#define  UF_DEVICE_A_ALT_HNP_SUPPORT 135 
#define  UF_DEVICE_A_HNP_SUPPORT 134 
#define  UF_DEVICE_B_HNP_ENABLE 133 
#define  UF_DEVICE_REMOTE_WAKEUP 132 
 int UF_ENDPOINT_HALT ; 
#define  UF_TEST_MODE 131 
 int UGETW (int /*<<< orphan*/ ) ; 
#define  UT_DEVICE 130 
#define  UT_ENDPOINT 129 
 int UT_GET_RECIPIENT (int /*<<< orphan*/ ) ; 
#define  UT_INTERFACE 128 
 int /*<<< orphan*/  do_gadget_setup (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  do_setup_in_status_phase (TYPE_6__*) ; 
 int /*<<< orphan*/  dwc_otg_ep_set_stall (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_pcd_update_otg (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep0_do_stall (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* get_ep_by_addr (TYPE_6__*,int) ; 

__attribute__((used)) static inline void do_set_feature(dwc_otg_pcd_t * pcd)
{
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);
	dwc_otg_core_global_regs_t *global_regs = core_if->core_global_regs;
	usb_device_request_t ctrl = pcd->setup_pkt->req;
	dwc_otg_pcd_ep_t *ep = 0;
	int32_t otg_cap_param = core_if->core_params->otg_cap;
	gotgctl_data_t gotgctl = {.d32 = 0 };

	DWC_DEBUGPL(DBG_PCD, "SET_FEATURE:%02x.%02x v%04x i%04x l%04x\n",
		    ctrl.bmRequestType, ctrl.bRequest,
		    UGETW(ctrl.wValue), UGETW(ctrl.wIndex),
		    UGETW(ctrl.wLength));
	DWC_DEBUGPL(DBG_PCD, "otg_cap=%d\n", otg_cap_param);

	switch (UT_GET_RECIPIENT(ctrl.bmRequestType)) {
	case UT_DEVICE:
		switch (UGETW(ctrl.wValue)) {
		case UF_DEVICE_REMOTE_WAKEUP:
			pcd->remote_wakeup_enable = 1;
			break;

		case UF_TEST_MODE:
			/* Setup the Test Mode tasklet to do the Test
			 * Packet generation after the SETUP Status
			 * phase has completed. */

			/** @todo This has not been tested since the
			 * tasklet struct was put into the PCD
			 * struct! */
			pcd->test_mode = UGETW(ctrl.wIndex) >> 8;
			DWC_TASK_SCHEDULE(pcd->test_mode_tasklet);
			break;

		case UF_DEVICE_B_HNP_ENABLE:
			DWC_DEBUGPL(DBG_PCDV,
				    "SET_FEATURE: USB_DEVICE_B_HNP_ENABLE\n");

			/* dev may initiate HNP */
			if (otg_cap_param == DWC_OTG_CAP_PARAM_HNP_SRP_CAPABLE) {
				pcd->b_hnp_enable = 1;
				dwc_otg_pcd_update_otg(pcd, 0);
				DWC_DEBUGPL(DBG_PCD, "Request B HNP\n");
				/**@todo Is the gotgctl.devhnpen cleared
				 * by a USB Reset? */
				gotgctl.b.devhnpen = 1;
				gotgctl.b.hnpreq = 1;
				DWC_WRITE_REG32(&global_regs->gotgctl,
						gotgctl.d32);
			} else {
				ep0_do_stall(pcd, -DWC_E_NOT_SUPPORTED);
				return;
			}
			break;

		case UF_DEVICE_A_HNP_SUPPORT:
			/* RH port supports HNP */
			DWC_DEBUGPL(DBG_PCDV,
				    "SET_FEATURE: USB_DEVICE_A_HNP_SUPPORT\n");
			if (otg_cap_param == DWC_OTG_CAP_PARAM_HNP_SRP_CAPABLE) {
				pcd->a_hnp_support = 1;
				dwc_otg_pcd_update_otg(pcd, 0);
			} else {
				ep0_do_stall(pcd, -DWC_E_NOT_SUPPORTED);
				return;
			}
			break;

		case UF_DEVICE_A_ALT_HNP_SUPPORT:
			/* other RH port does */
			DWC_DEBUGPL(DBG_PCDV,
				    "SET_FEATURE: USB_DEVICE_A_ALT_HNP_SUPPORT\n");
			if (otg_cap_param == DWC_OTG_CAP_PARAM_HNP_SRP_CAPABLE) {
				pcd->a_alt_hnp_support = 1;
				dwc_otg_pcd_update_otg(pcd, 0);
			} else {
				ep0_do_stall(pcd, -DWC_E_NOT_SUPPORTED);
				return;
			}
			break;

		default:
			ep0_do_stall(pcd, -DWC_E_NOT_SUPPORTED);
			return;

		}
		do_setup_in_status_phase(pcd);
		break;

	case UT_INTERFACE:
		do_gadget_setup(pcd, &ctrl);
		break;

	case UT_ENDPOINT:
		if (UGETW(ctrl.wValue) == UF_ENDPOINT_HALT) {
			ep = get_ep_by_addr(pcd, UGETW(ctrl.wIndex));
			if (ep == 0) {
				ep0_do_stall(pcd, -DWC_E_NOT_SUPPORTED);
				return;
			}
			ep->stopped = 1;
			dwc_otg_ep_set_stall(core_if, &ep->dwc_ep);
		}
		do_setup_in_status_phase(pcd);
		break;
	}
}