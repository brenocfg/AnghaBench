#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_27__ {scalar_t__ isoc_frame_index; TYPE_8__* urb; scalar_t__ error_count; scalar_t__ complete_split; scalar_t__ isoc_split_offset; } ;
typedef  TYPE_4__ dwc_otg_qtd_t ;
struct TYPE_28__ {TYPE_2__* fops; TYPE_1__* core_if; } ;
typedef  TYPE_5__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hc_regs_t ;
struct TYPE_29__ {scalar_t__ ep_type; TYPE_3__* qh; scalar_t__ ep_is_in; scalar_t__ complete_split; scalar_t__ do_split; int /*<<< orphan*/  hc_num; } ;
typedef  TYPE_6__ dwc_hc_t ;
struct TYPE_30__ {scalar_t__ packet_count; int /*<<< orphan*/  priv; } ;
struct TYPE_26__ {int sched_frame; int ping_state; } ;
struct TYPE_25__ {int /*<<< orphan*/  (* complete ) (TYPE_5__*,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_24__ {scalar_t__ dma_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCDI ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ DWC_OTG_EP_TYPE_INTR ; 
 scalar_t__ DWC_OTG_EP_TYPE_ISOC ; 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_NO_HALT_STATUS ; 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_NYET ; 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_URB_COMPLETE ; 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_XACT_ERR ; 
 int /*<<< orphan*/  disable_hc_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dwc_full_frame_num (int) ; 
 int dwc_otg_hcd_get_frame_number (TYPE_5__*) ; 
 int /*<<< orphan*/  dwc_otg_hcd_save_data_toggle (TYPE_6__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ fiq_fsm_enable ; 
 int /*<<< orphan*/  halt_channel (TYPE_5__*,TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nyet ; 
 int /*<<< orphan*/  release_channel (TYPE_5__*,TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_urb_state_xfer_intr (TYPE_6__*,int /*<<< orphan*/ *,TYPE_8__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t handle_hc_nyet_intr(dwc_otg_hcd_t * hcd,
				   dwc_hc_t * hc,
				   dwc_otg_hc_regs_t * hc_regs,
				   dwc_otg_qtd_t * qtd)
{
	DWC_DEBUGPL(DBG_HCDI, "--Host Channel %d Interrupt: "
		    "NYET Received--\n", hc->hc_num);

	/*
	 * NYET on CSPLIT
	 * re-do the CSPLIT immediately on non-periodic
	 */
	if (hc->do_split && hc->complete_split) {
		if (hc->ep_is_in && (hc->ep_type == DWC_OTG_EP_TYPE_ISOC)
		    && hcd->core_if->dma_enable) {
			qtd->complete_split = 0;
			qtd->isoc_split_offset = 0;
			if (++qtd->isoc_frame_index == qtd->urb->packet_count) {
				hcd->fops->complete(hcd, qtd->urb->priv, qtd->urb, 0);
				release_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_URB_COMPLETE);
			}
			else
				release_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_NO_HALT_STATUS);
			goto handle_nyet_done;
		}

		if (hc->ep_type == DWC_OTG_EP_TYPE_INTR ||
		    hc->ep_type == DWC_OTG_EP_TYPE_ISOC) {
			int frnum = dwc_otg_hcd_get_frame_number(hcd);

			// With the FIQ running we only ever see the failed NYET
			if (dwc_full_frame_num(frnum) !=
			    dwc_full_frame_num(hc->qh->sched_frame) ||
			    fiq_fsm_enable) {
				/*
				 * No longer in the same full speed frame.
				 * Treat this as a transaction error.
				 */
#if 0
				/** @todo Fix system performance so this can
				 * be treated as an error. Right now complete
				 * splits cannot be scheduled precisely enough
				 * due to other system activity, so this error
				 * occurs regularly in Slave mode.
				 */
				qtd->error_count++;
#endif
				qtd->complete_split = 0;
				halt_channel(hcd, hc, qtd,
					     DWC_OTG_HC_XFER_XACT_ERR);
				/** @todo add support for isoc release */
				goto handle_nyet_done;
			}
		}

		halt_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_NYET);
		goto handle_nyet_done;
	}

	hc->qh->ping_state = 1;
	qtd->error_count = 0;

	update_urb_state_xfer_intr(hc, hc_regs, qtd->urb, qtd,
				   DWC_OTG_HC_XFER_NYET);
	dwc_otg_hcd_save_data_toggle(hc, hc_regs, qtd);

	/*
	 * Halt the channel and re-start the transfer so the PING
	 * protocol will start.
	 */
	halt_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_NYET);

handle_nyet_done:
	disable_hc_int(hc_regs, nyet);
	return 1;
}