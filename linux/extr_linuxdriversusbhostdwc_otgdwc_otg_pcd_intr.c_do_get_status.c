#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  bmRequestType; } ;
typedef  TYPE_3__ usb_device_request_t ;
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_15__ {int* start_xfer_buff; int* xfer_buff; int xfer_len; int total_len; scalar_t__ xfer_count; int /*<<< orphan*/  dma_addr; } ;
struct TYPE_20__ {int stopped; TYPE_11__ dwc_ep; } ;
struct TYPE_19__ {int* status_buf; int ep0_pending; int remote_wakeup_enable; int /*<<< orphan*/  status_buf_dma_handle; TYPE_5__ ep0; TYPE_1__* setup_pkt; } ;
typedef  TYPE_4__ dwc_otg_pcd_t ;
typedef  TYPE_5__ dwc_otg_pcd_ep_t ;
struct TYPE_21__ {int otg_ver; int otg_sts; TYPE_2__* core_params; } ;
typedef  TYPE_6__ dwc_otg_core_if_t ;
struct TYPE_17__ {int /*<<< orphan*/  otg_cap; } ;
struct TYPE_16__ {TYPE_3__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_E_NOT_SUPPORTED ; 
 int /*<<< orphan*/  DWC_OTG_CAP_PARAM_HNP_SRP_CAPABLE ; 
 int /*<<< orphan*/  DWC_PRINTF (char*,int,...) ; 
 TYPE_6__* GET_CORE_IF (TYPE_4__*) ; 
 int UGETW (int /*<<< orphan*/ ) ; 
#define  UT_DEVICE 130 
#define  UT_ENDPOINT 129 
 int UT_GET_RECIPIENT (int /*<<< orphan*/ ) ; 
#define  UT_INTERFACE 128 
 int /*<<< orphan*/  dwc_otg_ep0_start_transfer (TYPE_6__*,TYPE_11__*) ; 
 int /*<<< orphan*/  ep0_do_stall (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* get_ep_by_addr (TYPE_4__*,int) ; 

__attribute__((used)) static inline void do_get_status(dwc_otg_pcd_t * pcd)
{
	usb_device_request_t ctrl = pcd->setup_pkt->req;
	dwc_otg_pcd_ep_t *ep;
	dwc_otg_pcd_ep_t *ep0 = &pcd->ep0;
	uint16_t *status = pcd->status_buf;
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);

#ifdef DEBUG_EP0
	DWC_DEBUGPL(DBG_PCD,
		    "GET_STATUS %02x.%02x v%04x i%04x l%04x\n",
		    ctrl.bmRequestType, ctrl.bRequest,
		    UGETW(ctrl.wValue), UGETW(ctrl.wIndex),
		    UGETW(ctrl.wLength));
#endif

	switch (UT_GET_RECIPIENT(ctrl.bmRequestType)) {
	case UT_DEVICE:
		if(UGETW(ctrl.wIndex) == 0xF000) { /* OTG Status selector */
			DWC_PRINTF("wIndex - %d\n", UGETW(ctrl.wIndex));
			DWC_PRINTF("OTG VERSION - %d\n", core_if->otg_ver);
			DWC_PRINTF("OTG CAP - %d, %d\n",
				   core_if->core_params->otg_cap,
						DWC_OTG_CAP_PARAM_HNP_SRP_CAPABLE);
			if (core_if->otg_ver == 1
			    && core_if->core_params->otg_cap ==
			    DWC_OTG_CAP_PARAM_HNP_SRP_CAPABLE) {
				uint8_t *otgsts = (uint8_t*)pcd->status_buf;
				*otgsts = (core_if->otg_sts & 0x1);
				pcd->ep0_pending = 1;
				ep0->dwc_ep.start_xfer_buff =
				    (uint8_t *) otgsts;
				ep0->dwc_ep.xfer_buff = (uint8_t *) otgsts;
				ep0->dwc_ep.dma_addr =
				    pcd->status_buf_dma_handle;
				ep0->dwc_ep.xfer_len = 1;
				ep0->dwc_ep.xfer_count = 0;
				ep0->dwc_ep.total_len = ep0->dwc_ep.xfer_len;
				dwc_otg_ep0_start_transfer(GET_CORE_IF(pcd),
							   &ep0->dwc_ep);
				return;
			} else {
				ep0_do_stall(pcd, -DWC_E_NOT_SUPPORTED);
				return;
			}
			break;
		} else {
			*status = 0x1;	/* Self powered */
			*status |= pcd->remote_wakeup_enable << 1;
			break;
		}
	case UT_INTERFACE:
		*status = 0;
		break;

	case UT_ENDPOINT:
		ep = get_ep_by_addr(pcd, UGETW(ctrl.wIndex));
		if (ep == 0 || UGETW(ctrl.wLength) > 2) {
			ep0_do_stall(pcd, -DWC_E_NOT_SUPPORTED);
			return;
		}
		/** @todo check for EP stall */
		*status = ep->stopped;
		break;
	}
	pcd->ep0_pending = 1;
	ep0->dwc_ep.start_xfer_buff = (uint8_t *) status;
	ep0->dwc_ep.xfer_buff = (uint8_t *) status;
	ep0->dwc_ep.dma_addr = pcd->status_buf_dma_handle;
	ep0->dwc_ep.xfer_len = 2;
	ep0->dwc_ep.xfer_count = 0;
	ep0->dwc_ep.total_len = ep0->dwc_ep.xfer_len;
	dwc_otg_ep0_start_transfer(GET_CORE_IF(pcd), &ep0->dwc_ep);
}