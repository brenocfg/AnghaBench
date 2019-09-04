#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_39__ {int control_phase; int /*<<< orphan*/  isoc_split_pos; scalar_t__ complete_split; TYPE_5__* urb; } ;
typedef  TYPE_4__ dwc_otg_qtd_t ;
struct TYPE_40__ {int /*<<< orphan*/  status; int /*<<< orphan*/  priv; int /*<<< orphan*/  length; int /*<<< orphan*/  pipe_info; } ;
typedef  TYPE_5__ dwc_otg_hcd_urb_t ;
struct TYPE_41__ {TYPE_3__* fops; TYPE_2__* core_if; } ;
typedef  TYPE_6__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hc_regs_t ;
typedef  int /*<<< orphan*/  dwc_otg_halt_status_e ;
struct TYPE_42__ {scalar_t__ ep_type; scalar_t__ ep_is_in; TYPE_1__* qh; int /*<<< orphan*/  hc_num; } ;
typedef  TYPE_7__ dwc_hc_t ;
struct TYPE_38__ {int /*<<< orphan*/  (* complete ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_37__ {scalar_t__ dma_enable; scalar_t__ dma_desc_enable; } ;
struct TYPE_36__ {scalar_t__ do_split; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCDI ; 
 int /*<<< orphan*/  DBG_HCDV ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DWC_E_IN_PROGRESS ; 
 int /*<<< orphan*/  DWC_HCSPLIT_XACTPOS_ALL ; 
#define  DWC_OTG_CONTROL_DATA 134 
#define  DWC_OTG_CONTROL_SETUP 133 
#define  DWC_OTG_CONTROL_STATUS 132 
 scalar_t__ DWC_OTG_EP_TYPE_ISOC ; 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_COMPLETE ; 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_URB_COMPLETE ; 
#define  UE_BULK 131 
#define  UE_CONTROL 130 
#define  UE_INTERRUPT 129 
#define  UE_ISOCHRONOUS 128 
 int /*<<< orphan*/  clear_hc_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_non_periodic_xfer (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_periodic_xfer (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_hc_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_hcd_complete_xfer_ddma (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dwc_otg_hcd_get_pipe_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_hcd_save_data_toggle (TYPE_7__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ handle_xfercomp_isoc_split_in (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_isoc_urb_state (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int update_urb_state_xfer_comp (TYPE_7__*,int /*<<< orphan*/ *,TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  xfercomp ; 
 int /*<<< orphan*/  xfercompl ; 

__attribute__((used)) static int32_t handle_hc_xfercomp_intr(dwc_otg_hcd_t * hcd,
				       dwc_hc_t * hc,
				       dwc_otg_hc_regs_t * hc_regs,
				       dwc_otg_qtd_t * qtd)
{
	int urb_xfer_done;
	dwc_otg_halt_status_e halt_status = DWC_OTG_HC_XFER_COMPLETE;
	dwc_otg_hcd_urb_t *urb = qtd->urb;
	int pipe_type = dwc_otg_hcd_get_pipe_type(&urb->pipe_info);

	DWC_DEBUGPL(DBG_HCDI, "--Host Channel %d Interrupt: "
		    "Transfer Complete--\n", hc->hc_num);

	if (hcd->core_if->dma_desc_enable) {
		dwc_otg_hcd_complete_xfer_ddma(hcd, hc, hc_regs, halt_status);
		if (pipe_type == UE_ISOCHRONOUS) {
			/* Do not disable the interrupt, just clear it */
			clear_hc_int(hc_regs, xfercomp);
			return 1;
		}
		goto handle_xfercomp_done;
	}

	/*
	 * Handle xfer complete on CSPLIT.
	 */

	if (hc->qh->do_split) {
		if ((hc->ep_type == DWC_OTG_EP_TYPE_ISOC) && hc->ep_is_in
		    && hcd->core_if->dma_enable) {
			if (qtd->complete_split
			    && handle_xfercomp_isoc_split_in(hcd, hc, hc_regs,
							     qtd))
				goto handle_xfercomp_done;
		} else {
			qtd->complete_split = 0;
		}
	}

	/* Update the QTD and URB states. */
	switch (pipe_type) {
	case UE_CONTROL:
		switch (qtd->control_phase) {
		case DWC_OTG_CONTROL_SETUP:
			if (urb->length > 0) {
				qtd->control_phase = DWC_OTG_CONTROL_DATA;
			} else {
				qtd->control_phase = DWC_OTG_CONTROL_STATUS;
			}
			DWC_DEBUGPL(DBG_HCDV,
				    "  Control setup transaction done\n");
			halt_status = DWC_OTG_HC_XFER_COMPLETE;
			break;
		case DWC_OTG_CONTROL_DATA:{
				urb_xfer_done =
				    update_urb_state_xfer_comp(hc, hc_regs, urb,
							       qtd);
				if (urb_xfer_done) {
					qtd->control_phase =
					    DWC_OTG_CONTROL_STATUS;
					DWC_DEBUGPL(DBG_HCDV,
						    "  Control data transfer done\n");
				} else {
					dwc_otg_hcd_save_data_toggle(hc, hc_regs, qtd);
				}
				halt_status = DWC_OTG_HC_XFER_COMPLETE;
				break;
			}
		case DWC_OTG_CONTROL_STATUS:
			DWC_DEBUGPL(DBG_HCDV, "  Control transfer complete\n");
			if (urb->status == -DWC_E_IN_PROGRESS) {
				urb->status = 0;
			}
			hcd->fops->complete(hcd, urb->priv, urb, urb->status);
			halt_status = DWC_OTG_HC_XFER_URB_COMPLETE;
			break;
		}

		complete_non_periodic_xfer(hcd, hc, hc_regs, qtd, halt_status);
		break;
	case UE_BULK:
		DWC_DEBUGPL(DBG_HCDV, "  Bulk transfer complete\n");
		urb_xfer_done =
		    update_urb_state_xfer_comp(hc, hc_regs, urb, qtd);
		if (urb_xfer_done) {
			hcd->fops->complete(hcd, urb->priv, urb, urb->status);
			halt_status = DWC_OTG_HC_XFER_URB_COMPLETE;
		} else {
			halt_status = DWC_OTG_HC_XFER_COMPLETE;
		}

		dwc_otg_hcd_save_data_toggle(hc, hc_regs, qtd);
		complete_non_periodic_xfer(hcd, hc, hc_regs, qtd, halt_status);
		break;
	case UE_INTERRUPT:
		DWC_DEBUGPL(DBG_HCDV, "  Interrupt transfer complete\n");
		urb_xfer_done =
			update_urb_state_xfer_comp(hc, hc_regs, urb, qtd);

		/*
		 * Interrupt URB is done on the first transfer complete
		 * interrupt.
		 */
		if (urb_xfer_done) {
				hcd->fops->complete(hcd, urb->priv, urb, urb->status);
				halt_status = DWC_OTG_HC_XFER_URB_COMPLETE;
		} else {
				halt_status = DWC_OTG_HC_XFER_COMPLETE;
		}

		dwc_otg_hcd_save_data_toggle(hc, hc_regs, qtd);
		complete_periodic_xfer(hcd, hc, hc_regs, qtd, halt_status);
		break;
	case UE_ISOCHRONOUS:
		DWC_DEBUGPL(DBG_HCDV, "  Isochronous transfer complete\n");
		if (qtd->isoc_split_pos == DWC_HCSPLIT_XACTPOS_ALL) {
			halt_status =
			    update_isoc_urb_state(hcd, hc, hc_regs, qtd,
						  DWC_OTG_HC_XFER_COMPLETE);
		}
		complete_periodic_xfer(hcd, hc, hc_regs, qtd, halt_status);
		break;
	}

handle_xfercomp_done:
	disable_hc_int(hc_regs, xfercompl);

	return 1;
}