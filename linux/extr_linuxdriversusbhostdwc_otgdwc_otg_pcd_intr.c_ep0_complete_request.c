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
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_30__ {scalar_t__ ep0state; scalar_t__ ep0_pending; } ;
typedef  TYPE_5__ dwc_otg_pcd_t ;
struct TYPE_31__ {scalar_t__ sent_zlp; int /*<<< orphan*/  actual; } ;
typedef  TYPE_6__ dwc_otg_pcd_request_t ;
struct TYPE_29__ {size_t num; scalar_t__ xfer_len; scalar_t__ xfer_buff; scalar_t__ start_xfer_buff; int /*<<< orphan*/  xfer_count; scalar_t__ is_in; } ;
struct TYPE_32__ {TYPE_4__ dwc_ep; int /*<<< orphan*/  queue; TYPE_5__* pcd; } ;
typedef  TYPE_7__ dwc_otg_pcd_ep_t ;
struct TYPE_33__ {int /*<<< orphan*/  dieptsiz; } ;
typedef  TYPE_8__ dwc_otg_dev_in_ep_regs_t ;
struct TYPE_34__ {TYPE_1__* in_desc_addr; TYPE_8__** in_ep_regs; } ;
typedef  TYPE_9__ dwc_otg_dev_if_t ;
struct TYPE_23__ {scalar_t__ dma_desc_enable; scalar_t__ dma_enable; scalar_t__ snpsid; TYPE_9__* dev_if; } ;
typedef  TYPE_10__ dwc_otg_core_if_t ;
struct TYPE_28__ {scalar_t__ bytes; } ;
struct TYPE_24__ {TYPE_3__ b; } ;
typedef  TYPE_11__ dev_dma_desc_sts_t ;
struct TYPE_27__ {scalar_t__ xfersize; } ;
struct TYPE_25__ {TYPE_2__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_12__ deptsiz0_data_t ;
struct TYPE_26__ {TYPE_11__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCDV ; 
 scalar_t__ DWC_CIRCLEQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_6__* DWC_CIRCLEQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 scalar_t__ EP0_IN_STATUS_PHASE ; 
 scalar_t__ EP0_OUT_STATUS_PHASE ; 
 TYPE_10__* GET_CORE_IF (TYPE_5__*) ; 
 scalar_t__ OTG_CORE_REV_2_94a ; 
 scalar_t__ OTG_CORE_REV_3_00a ; 
 int /*<<< orphan*/  do_setup_in_status_phase (TYPE_5__*) ; 
 int /*<<< orphan*/  do_setup_out_status_phase (TYPE_5__*) ; 
 int /*<<< orphan*/  dwc_otg_request_done (TYPE_7__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep0_out_start (TYPE_10__*,TYPE_5__*) ; 

__attribute__((used)) static int32_t ep0_complete_request(dwc_otg_pcd_ep_t * ep)
{
	dwc_otg_core_if_t *core_if = GET_CORE_IF(ep->pcd);
	dwc_otg_dev_if_t *dev_if = core_if->dev_if;
	dwc_otg_dev_in_ep_regs_t *in_ep_regs =
	    dev_if->in_ep_regs[ep->dwc_ep.num];
#ifdef DEBUG_EP0
	dwc_otg_dev_out_ep_regs_t *out_ep_regs =
	    dev_if->out_ep_regs[ep->dwc_ep.num];
#endif
	deptsiz0_data_t deptsiz;
	dev_dma_desc_sts_t desc_sts;
	dwc_otg_pcd_request_t *req;
	int is_last = 0;
	dwc_otg_pcd_t *pcd = ep->pcd;

#ifdef DWC_UTE_CFI
	struct cfi_usb_ctrlrequest *ctrlreq;
	int retval = -DWC_E_NOT_SUPPORTED;
#endif

        desc_sts.b.bytes = 0;

	if (pcd->ep0_pending && DWC_CIRCLEQ_EMPTY(&ep->queue)) {
		if (ep->dwc_ep.is_in) {
#ifdef DEBUG_EP0
			DWC_DEBUGPL(DBG_PCDV, "Do setup OUT status phase\n");
#endif
			do_setup_out_status_phase(pcd);
		} else {
#ifdef DEBUG_EP0
			DWC_DEBUGPL(DBG_PCDV, "Do setup IN status phase\n");
#endif

#ifdef DWC_UTE_CFI
			ctrlreq = &pcd->cfi->ctrl_req;

			if (UT_GET_TYPE(ctrlreq->bRequestType) == UT_VENDOR) {
				if (ctrlreq->bRequest > 0xB0
				    && ctrlreq->bRequest < 0xBF) {

					/* Return if the PCD failed to handle the request */
					if ((retval =
					     pcd->cfi->ops.
					     ctrl_write_complete(pcd->cfi,
								 pcd)) < 0) {
						CFI_INFO
						    ("ERROR setting a new value in the PCD(%d)\n",
						     retval);
						ep0_do_stall(pcd, retval);
						pcd->ep0_pending = 0;
						return 0;
					}

					/* If the gadget needs to be notified on the request */
					if (pcd->cfi->need_gadget_att == 1) {
						//retval = do_gadget_setup(pcd, &pcd->cfi->ctrl_req);
						retval =
						    cfi_gadget_setup(pcd,
								     &pcd->cfi->
								     ctrl_req);

						/* Return from the function if the gadget failed to process
						 * the request properly - this should never happen !!!
						 */
						if (retval < 0) {
							CFI_INFO
							    ("ERROR setting a new value in the gadget(%d)\n",
							     retval);
							pcd->ep0_pending = 0;
							return 0;
						}
					}

					CFI_INFO("%s: RETVAL=%d\n", __func__,
						 retval);
					/* If we hit here then the PCD and the gadget has properly
					 * handled the request - so send the ZLP IN to the host.
					 */
					/* @todo: MAS - decide whether we need to start the setup
					 * stage based on the need_setup value of the cfi object
					 */
					do_setup_in_status_phase(pcd);
					pcd->ep0_pending = 0;
					return 1;
				}
			}
#endif

			do_setup_in_status_phase(pcd);
		}
		pcd->ep0_pending = 0;
		return 1;
	}

	if (DWC_CIRCLEQ_EMPTY(&ep->queue)) {
		return 0;
	}
	req = DWC_CIRCLEQ_FIRST(&ep->queue);

	if (pcd->ep0state == EP0_OUT_STATUS_PHASE
	    || pcd->ep0state == EP0_IN_STATUS_PHASE) {
		is_last = 1;
	} else if (ep->dwc_ep.is_in) {
		deptsiz.d32 = DWC_READ_REG32(&in_ep_regs->dieptsiz);
		if (core_if->dma_desc_enable != 0)
			desc_sts = dev_if->in_desc_addr->status;
#ifdef DEBUG_EP0
		DWC_DEBUGPL(DBG_PCDV, "%d len=%d  xfersize=%d pktcnt=%d\n",
			    ep->dwc_ep.num, ep->dwc_ep.xfer_len,
			    deptsiz.b.xfersize, deptsiz.b.pktcnt);
#endif

		if (((core_if->dma_desc_enable == 0)
		     && (deptsiz.b.xfersize == 0))
		    || ((core_if->dma_desc_enable != 0)
			&& (desc_sts.b.bytes == 0))) {
			req->actual = ep->dwc_ep.xfer_count;
			/* Is a Zero Len Packet needed? */
			if (req->sent_zlp) {
#ifdef DEBUG_EP0
				DWC_DEBUGPL(DBG_PCD, "Setup Rx ZLP\n");
#endif
				req->sent_zlp = 0;
			}
			do_setup_out_status_phase(pcd);
		}
	} else {
		/* ep0-OUT */
#ifdef DEBUG_EP0
		deptsiz.d32 = DWC_READ_REG32(&out_ep_regs->doeptsiz);
		DWC_DEBUGPL(DBG_PCDV, "%d len=%d xsize=%d pktcnt=%d\n",
			    ep->dwc_ep.num, ep->dwc_ep.xfer_len,
			    deptsiz.b.xfersize, deptsiz.b.pktcnt);
#endif
		req->actual = ep->dwc_ep.xfer_count;

		/* Is a Zero Len Packet needed? */
		if (req->sent_zlp) {
#ifdef DEBUG_EP0
			DWC_DEBUGPL(DBG_PCDV, "Setup Tx ZLP\n");
#endif
			req->sent_zlp = 0;
		}
		/* For older cores do setup in status phase in Slave/BDMA modes,
		 * starting from 3.00 do that only in slave, and for DMA modes
		 * just re-enable ep 0 OUT here*/
		if (core_if->dma_enable == 0
		    || (core_if->dma_desc_enable == 0
			&& core_if->snpsid <= OTG_CORE_REV_2_94a)) {
			do_setup_in_status_phase(pcd);
		} else if (core_if->snpsid >= OTG_CORE_REV_3_00a) {
			DWC_DEBUGPL(DBG_PCDV,
				    "Enable out ep before in status phase\n");
			ep0_out_start(core_if, pcd);
		}
	}

	/* Complete the request */
	if (is_last) {
		dwc_otg_request_done(ep, req, 0);
		ep->dwc_ep.start_xfer_buff = 0;
		ep->dwc_ep.xfer_buff = 0;
		ep->dwc_ep.xfer_len = 0;
		return 1;
	}
	return 0;
}