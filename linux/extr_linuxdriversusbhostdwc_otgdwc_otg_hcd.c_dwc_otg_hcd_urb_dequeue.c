#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_20__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_19__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_29__ {scalar_t__ in_process; TYPE_6__* qh; } ;
typedef  TYPE_5__ dwc_otg_qtd_t ;
struct TYPE_30__ {int nak_frame; int /*<<< orphan*/  qtd_list; TYPE_20__* channel; scalar_t__ do_split; } ;
typedef  TYPE_6__ dwc_otg_qh_t ;
struct TYPE_31__ {TYPE_5__* qtd; } ;
typedef  TYPE_7__ dwc_otg_hcd_urb_t ;
struct TYPE_24__ {scalar_t__ port_connect_status; } ;
struct TYPE_26__ {TYPE_1__ b; } ;
struct TYPE_32__ {TYPE_19__* core_if; TYPE_4__* fiq_state; TYPE_2__ flags; } ;
typedef  TYPE_8__ dwc_otg_hcd_t ;
struct TYPE_28__ {int /*<<< orphan*/  lock; TYPE_3__* channel; } ;
struct TYPE_27__ {scalar_t__ fsm; } ;
struct TYPE_25__ {int hc_num; int halt_pending; int /*<<< orphan*/  halt_status; } ;
struct TYPE_23__ {scalar_t__ dma_desc_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CHK_DEBUG_LEVEL (int) ; 
 int /*<<< orphan*/  DBG_HCD ; 
 int DBG_HCDV ; 
 int DBG_HCD_URB ; 
 scalar_t__ DWC_CIRCLEQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_URB_DEQUEUE ; 
 scalar_t__ FIQ_HS_ISOC_ABORTED ; 
 scalar_t__ FIQ_HS_ISOC_SLEEPING ; 
 scalar_t__ FIQ_HS_ISOC_TURBO ; 
 scalar_t__ FIQ_PASSTHROUGH ; 
 int /*<<< orphan*/  dump_channel_info (TYPE_8__*,TYPE_6__*) ; 
 int /*<<< orphan*/  dwc_otg_hc_halt (TYPE_19__*,TYPE_20__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_hcd_qh_deactivate (TYPE_8__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_hcd_qh_remove (TYPE_8__*,TYPE_6__*) ; 
 int /*<<< orphan*/  dwc_otg_hcd_qtd_remove_and_free (TYPE_8__*,TYPE_5__*,TYPE_6__*) ; 
 scalar_t__ dwc_qh_is_non_per (TYPE_6__*) ; 
 scalar_t__ fiq_fsm_enable ; 
 int /*<<< orphan*/  fiq_fsm_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fiq_fsm_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_fiq_disable () ; 
 int /*<<< orphan*/  local_fiq_enable () ; 
 scalar_t__ nak_holdoff ; 

int dwc_otg_hcd_urb_dequeue(dwc_otg_hcd_t * hcd,
			    dwc_otg_hcd_urb_t * dwc_otg_urb)
{
	dwc_otg_qh_t *qh;
	dwc_otg_qtd_t *urb_qtd;
	BUG_ON(!hcd);
	BUG_ON(!dwc_otg_urb);

#ifdef DEBUG /* integrity checks (Broadcom) */

	if (hcd == NULL) {
		DWC_ERROR("**** DWC OTG HCD URB Dequeue has NULL HCD\n");
		return -DWC_E_INVALID;
	}
	if (dwc_otg_urb == NULL) {
		DWC_ERROR("**** DWC OTG HCD URB Dequeue has NULL URB\n");
		return -DWC_E_INVALID;
	}
	if (dwc_otg_urb->qtd == NULL) {
		DWC_ERROR("**** DWC OTG HCD URB Dequeue with NULL QTD\n");
		return -DWC_E_INVALID;
	}
	urb_qtd = dwc_otg_urb->qtd;
	BUG_ON(!urb_qtd);
	if (urb_qtd->qh == NULL) {
		DWC_ERROR("**** DWC OTG HCD URB Dequeue with QTD with NULL Q handler\n");
		return -DWC_E_INVALID;
	}
#else
	urb_qtd = dwc_otg_urb->qtd;
	BUG_ON(!urb_qtd);
#endif
	qh = urb_qtd->qh;
	BUG_ON(!qh);
	if (CHK_DEBUG_LEVEL(DBG_HCDV | DBG_HCD_URB)) {
		if (urb_qtd->in_process) {
			dump_channel_info(hcd, qh);
		}
	}
#ifdef DEBUG /* integrity checks (Broadcom) */
	if (hcd->core_if == NULL) {
		DWC_ERROR("**** DWC OTG HCD URB Dequeue HCD has NULL core_if\n");
		return -DWC_E_INVALID;
	}
#endif
	if (urb_qtd->in_process && qh->channel) {
		/* The QTD is in process (it has been assigned to a channel). */
		if (hcd->flags.b.port_connect_status) {
			int n = qh->channel->hc_num;
			/*
			 * If still connected (i.e. in host mode), halt the
			 * channel so it can be used for other transfers. If
			 * no longer connected, the host registers can't be
			 * written to halt the channel since the core is in
			 * device mode.
			 */
			/* In FIQ FSM mode, we need to shut down carefully.
			 * The FIQ may attempt to restart a disabled channel */
			if (fiq_fsm_enable && (hcd->fiq_state->channel[n].fsm != FIQ_PASSTHROUGH)) {
				local_fiq_disable();
				fiq_fsm_spin_lock(&hcd->fiq_state->lock);
				qh->channel->halt_status = DWC_OTG_HC_XFER_URB_DEQUEUE;
				qh->channel->halt_pending = 1;
				if (hcd->fiq_state->channel[n].fsm == FIQ_HS_ISOC_TURBO ||
					hcd->fiq_state->channel[n].fsm == FIQ_HS_ISOC_SLEEPING)
					hcd->fiq_state->channel[n].fsm = FIQ_HS_ISOC_ABORTED;
				fiq_fsm_spin_unlock(&hcd->fiq_state->lock);
				local_fiq_enable();
			} else {
				dwc_otg_hc_halt(hcd->core_if, qh->channel,
						DWC_OTG_HC_XFER_URB_DEQUEUE);
			}
		}
	}

	/*
	 * Free the QTD and clean up the associated QH. Leave the QH in the
	 * schedule if it has any remaining QTDs.
	 */

	DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD URB Dequeue - "
                    "delete %sQueue handler\n",
                    hcd->core_if->dma_desc_enable?"DMA ":"");
	if (!hcd->core_if->dma_desc_enable) {
		uint8_t b = urb_qtd->in_process;
		if (nak_holdoff && qh->do_split && dwc_qh_is_non_per(qh))
			qh->nak_frame = 0xFFFF;
		dwc_otg_hcd_qtd_remove_and_free(hcd, urb_qtd, qh);
		if (b) {
			dwc_otg_hcd_qh_deactivate(hcd, qh, 0);
			qh->channel = NULL;
		} else if (DWC_CIRCLEQ_EMPTY(&qh->qtd_list)) {
			dwc_otg_hcd_qh_remove(hcd, qh);
		}
	} else {
		dwc_otg_hcd_qtd_remove_and_free(hcd, urb_qtd, qh);
	}
	return 0;
}