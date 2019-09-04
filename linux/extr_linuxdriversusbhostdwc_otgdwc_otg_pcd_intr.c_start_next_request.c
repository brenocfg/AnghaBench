#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {scalar_t__ length; scalar_t__ sent_zlp; scalar_t__ buf; int /*<<< orphan*/  dma; scalar_t__ dw_align_buf; int /*<<< orphan*/  dw_align_buf_dma; } ;
typedef  TYPE_2__ dwc_otg_pcd_request_t ;
struct TYPE_13__ {int sent_zlp; scalar_t__ total_len; int maxxfer; int maxpacket; scalar_t__ type; int frame_num; scalar_t__ is_in; scalar_t__ xfer_count; scalar_t__ xfer_len; scalar_t__ xfer_buff; scalar_t__ start_xfer_buff; int /*<<< orphan*/  dma_addr; } ;
struct TYPE_11__ {TYPE_6__ dwc_ep; int /*<<< orphan*/  pcd; int /*<<< orphan*/  queue; } ;
typedef  TYPE_3__ dwc_otg_pcd_ep_t ;
struct TYPE_12__ {scalar_t__ dma_desc_enable; TYPE_1__* core_params; } ;
struct TYPE_9__ {scalar_t__ max_transfer_size; } ;

/* Variables and functions */
 int DDMA_MAX_TRANSFER_SIZE ; 
 int /*<<< orphan*/  DWC_CIRCLEQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_2__* DWC_CIRCLEQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ DWC_OTG_EP_TYPE_ISOC ; 
 int /*<<< orphan*/  DWC_PRINTF (char*) ; 
 TYPE_5__* GET_CORE_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_ep_start_transfer (TYPE_5__*,TYPE_6__*) ; 

void start_next_request(dwc_otg_pcd_ep_t * ep)
{
	dwc_otg_pcd_request_t *req = 0;
	uint32_t max_transfer =
	    GET_CORE_IF(ep->pcd)->core_params->max_transfer_size;

#ifdef DWC_UTE_CFI
	struct dwc_otg_pcd *pcd;
	pcd = ep->pcd;
#endif

	if (!DWC_CIRCLEQ_EMPTY(&ep->queue)) {
		req = DWC_CIRCLEQ_FIRST(&ep->queue);

#ifdef DWC_UTE_CFI
		if (ep->dwc_ep.buff_mode != BM_STANDARD) {
			ep->dwc_ep.cfi_req_len = req->length;
			pcd->cfi->ops.build_descriptors(pcd->cfi, pcd, ep, req);
		} else {
#endif
			/* Setup and start the Transfer */
			if (req->dw_align_buf) {
				ep->dwc_ep.dma_addr = req->dw_align_buf_dma;
				ep->dwc_ep.start_xfer_buff = req->dw_align_buf;
				ep->dwc_ep.xfer_buff = req->dw_align_buf;
			} else {
				ep->dwc_ep.dma_addr = req->dma;
				ep->dwc_ep.start_xfer_buff = req->buf;
				ep->dwc_ep.xfer_buff = req->buf;
			}
			ep->dwc_ep.sent_zlp = 0;
			ep->dwc_ep.total_len = req->length;
			ep->dwc_ep.xfer_len = 0;
			ep->dwc_ep.xfer_count = 0;

			ep->dwc_ep.maxxfer = max_transfer;
			if (GET_CORE_IF(ep->pcd)->dma_desc_enable) {
				uint32_t out_max_xfer = DDMA_MAX_TRANSFER_SIZE
				    - (DDMA_MAX_TRANSFER_SIZE % 4);
				if (ep->dwc_ep.is_in) {
					if (ep->dwc_ep.maxxfer >
					    DDMA_MAX_TRANSFER_SIZE) {
						ep->dwc_ep.maxxfer =
						    DDMA_MAX_TRANSFER_SIZE;
					}
				} else {
					if (ep->dwc_ep.maxxfer > out_max_xfer) {
						ep->dwc_ep.maxxfer =
						    out_max_xfer;
					}
				}
			}
			if (ep->dwc_ep.maxxfer < ep->dwc_ep.total_len) {
				ep->dwc_ep.maxxfer -=
				    (ep->dwc_ep.maxxfer % ep->dwc_ep.maxpacket);
			}
			if (req->sent_zlp) {
				if ((ep->dwc_ep.total_len %
				     ep->dwc_ep.maxpacket == 0)
				    && (ep->dwc_ep.total_len != 0)) {
					ep->dwc_ep.sent_zlp = 1;
				}

			}
#ifdef DWC_UTE_CFI
		}
#endif
		dwc_otg_ep_start_transfer(GET_CORE_IF(ep->pcd), &ep->dwc_ep);
	} else if (ep->dwc_ep.type == DWC_OTG_EP_TYPE_ISOC) {
		DWC_PRINTF("There are no more ISOC requests \n");
		ep->dwc_ep.frame_num = 0xFFFFFFFF;
	}
}