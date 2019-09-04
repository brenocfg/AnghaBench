#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_19__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_25__ {int /*<<< orphan*/  is_in; int /*<<< orphan*/  sent_zlp; scalar_t__ total_len; scalar_t__ xfer_count; scalar_t__ dma_addr; scalar_t__ xfer_buff; scalar_t__ maxpacket; scalar_t__ xfer_len; } ;
struct TYPE_34__ {int stopped; TYPE_19__ dwc_ep; } ;
struct TYPE_33__ {int ep0state; int /*<<< orphan*/  request_config; TYPE_9__ ep0; } ;
typedef  TYPE_8__ dwc_otg_pcd_t ;
typedef  TYPE_9__ dwc_otg_pcd_ep_t ;
struct TYPE_22__ {int /*<<< orphan*/  dma_enable; TYPE_6__* dev_if; int /*<<< orphan*/  dma_desc_enable; } ;
typedef  TYPE_10__ dwc_otg_core_if_t ;
struct TYPE_32__ {scalar_t__ bytes; } ;
struct TYPE_23__ {TYPE_7__ b; } ;
typedef  TYPE_11__ dev_dma_desc_sts_t ;
struct TYPE_29__ {scalar_t__ xfersize; } ;
struct TYPE_24__ {TYPE_4__ b; void* d32; } ;
typedef  TYPE_12__ deptsiz0_data_t ;
struct TYPE_31__ {TYPE_5__* out_desc_addr; TYPE_3__** out_ep_regs; TYPE_2__* in_desc_addr; TYPE_1__** in_ep_regs; } ;
struct TYPE_30__ {TYPE_11__ status; } ;
struct TYPE_28__ {int /*<<< orphan*/  doeptsiz; } ;
struct TYPE_27__ {TYPE_11__ status; } ;
struct TYPE_26__ {int /*<<< orphan*/  dieptsiz; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
#define  EP0_DISCONNECT 134 
#define  EP0_IDLE 133 
#define  EP0_IN_DATA_PHASE 132 
#define  EP0_IN_STATUS_PHASE 131 
#define  EP0_OUT_DATA_PHASE 130 
#define  EP0_OUT_STATUS_PHASE 129 
#define  EP0_STALL 128 
 TYPE_10__* GET_CORE_IF (TYPE_8__*) ; 
 int /*<<< orphan*/  dwc_otg_ep0_continue_transfer (TYPE_10__*,TYPE_19__*) ; 
 int /*<<< orphan*/  ep0_complete_request (TYPE_9__*) ; 
 int /*<<< orphan*/  ep0_out_start (TYPE_10__*,TYPE_8__*) ; 
 int /*<<< orphan*/  pcd_setup (TYPE_8__*) ; 

__attribute__((used)) static void handle_ep0(dwc_otg_pcd_t * pcd)
{
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);
	dwc_otg_pcd_ep_t *ep0 = &pcd->ep0;
	dev_dma_desc_sts_t desc_sts;
	deptsiz0_data_t deptsiz;
	uint32_t byte_count;

#ifdef DEBUG_EP0
	DWC_DEBUGPL(DBG_PCDV, "%s()\n", __func__);
	print_ep0_state(pcd);
#endif

//      DWC_PRINTF("HANDLE EP0\n");

	switch (pcd->ep0state) {
	case EP0_DISCONNECT:
		break;

	case EP0_IDLE:
		pcd->request_config = 0;

		pcd_setup(pcd);
		break;

	case EP0_IN_DATA_PHASE:
#ifdef DEBUG_EP0
		DWC_DEBUGPL(DBG_PCD, "DATA_IN EP%d-%s: type=%d, mps=%d\n",
			    ep0->dwc_ep.num, (ep0->dwc_ep.is_in ? "IN" : "OUT"),
			    ep0->dwc_ep.type, ep0->dwc_ep.maxpacket);
#endif

		if (core_if->dma_enable != 0) {
			/*
			 * For EP0 we can only program 1 packet at a time so we
			 * need to do the make calculations after each complete.
			 * Call write_packet to make the calculations, as in
			 * slave mode, and use those values to determine if we
			 * can complete.
			 */
			if (core_if->dma_desc_enable == 0) {
				deptsiz.d32 =
				    DWC_READ_REG32(&core_if->
						   dev_if->in_ep_regs[0]->
						   dieptsiz);
				byte_count =
				    ep0->dwc_ep.xfer_len - deptsiz.b.xfersize;
			} else {
				desc_sts =
				    core_if->dev_if->in_desc_addr->status;
				byte_count =
				    ep0->dwc_ep.xfer_len - desc_sts.b.bytes;
			}
			ep0->dwc_ep.xfer_count += byte_count;
			ep0->dwc_ep.xfer_buff += byte_count;
			ep0->dwc_ep.dma_addr += byte_count;
		}
		if (ep0->dwc_ep.xfer_count < ep0->dwc_ep.total_len) {
			dwc_otg_ep0_continue_transfer(GET_CORE_IF(pcd),
						      &ep0->dwc_ep);
			DWC_DEBUGPL(DBG_PCD, "CONTINUE TRANSFER\n");
		} else if (ep0->dwc_ep.sent_zlp) {
			dwc_otg_ep0_continue_transfer(GET_CORE_IF(pcd),
						      &ep0->dwc_ep);
			ep0->dwc_ep.sent_zlp = 0;
			DWC_DEBUGPL(DBG_PCD, "CONTINUE TRANSFER sent zlp\n");
		} else {
			ep0_complete_request(ep0);
			DWC_DEBUGPL(DBG_PCD, "COMPLETE TRANSFER\n");
		}
		break;
	case EP0_OUT_DATA_PHASE:
#ifdef DEBUG_EP0
		DWC_DEBUGPL(DBG_PCD, "DATA_OUT EP%d-%s: type=%d, mps=%d\n",
			    ep0->dwc_ep.num, (ep0->dwc_ep.is_in ? "IN" : "OUT"),
			    ep0->dwc_ep.type, ep0->dwc_ep.maxpacket);
#endif
		if (core_if->dma_enable != 0) {
			if (core_if->dma_desc_enable == 0) {
				deptsiz.d32 =
				    DWC_READ_REG32(&core_if->
						   dev_if->out_ep_regs[0]->
						   doeptsiz);
				byte_count =
				    ep0->dwc_ep.maxpacket - deptsiz.b.xfersize;
			} else {
				desc_sts =
				    core_if->dev_if->out_desc_addr->status;
				byte_count =
				    ep0->dwc_ep.maxpacket - desc_sts.b.bytes;
			}
			ep0->dwc_ep.xfer_count += byte_count;
			ep0->dwc_ep.xfer_buff += byte_count;
			ep0->dwc_ep.dma_addr += byte_count;
		}
		if (ep0->dwc_ep.xfer_count < ep0->dwc_ep.total_len) {
			dwc_otg_ep0_continue_transfer(GET_CORE_IF(pcd),
						      &ep0->dwc_ep);
			DWC_DEBUGPL(DBG_PCD, "CONTINUE TRANSFER\n");
		} else if (ep0->dwc_ep.sent_zlp) {
			dwc_otg_ep0_continue_transfer(GET_CORE_IF(pcd),
						      &ep0->dwc_ep);
			ep0->dwc_ep.sent_zlp = 0;
			DWC_DEBUGPL(DBG_PCD, "CONTINUE TRANSFER sent zlp\n");
		} else {
			ep0_complete_request(ep0);
			DWC_DEBUGPL(DBG_PCD, "COMPLETE TRANSFER\n");
		}
		break;

	case EP0_IN_STATUS_PHASE:
	case EP0_OUT_STATUS_PHASE:
		DWC_DEBUGPL(DBG_PCD, "CASE: EP0_STATUS\n");
		ep0_complete_request(ep0);
		pcd->ep0state = EP0_IDLE;
		ep0->stopped = 1;
		ep0->dwc_ep.is_in = 0;	/* OUT for next SETUP */

		/* Prepare for more SETUP Packets */
		if (core_if->dma_enable) {
			ep0_out_start(core_if, pcd);
		}
		break;

	case EP0_STALL:
		DWC_ERROR("EP0 STALLed, should not get here pcd_setup()\n");
		break;
	}
#ifdef DEBUG_EP0
	print_ep0_state(pcd);
#endif
}