#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct dwc_otg_hcd_iso_packet_desc {void* actual_length; scalar_t__ offset; int /*<<< orphan*/  status; } ;
struct TYPE_18__ {size_t isoc_frame_index; scalar_t__ isoc_split_offset; int /*<<< orphan*/  complete_split; TYPE_5__* urb; } ;
typedef  TYPE_4__ dwc_otg_qtd_t ;
struct TYPE_19__ {size_t packet_count; int /*<<< orphan*/  priv; scalar_t__ buf; int /*<<< orphan*/  error_count; struct dwc_otg_hcd_iso_packet_desc* iso_descs; } ;
typedef  TYPE_5__ dwc_otg_hcd_urb_t ;
struct TYPE_20__ {TYPE_3__* fops; TYPE_2__* core_if; } ;
typedef  TYPE_6__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hc_regs_t ;
typedef  int dwc_otg_halt_status_e ;
struct TYPE_21__ {int /*<<< orphan*/  ep_is_in; int /*<<< orphan*/  ep_type; TYPE_1__* qh; int /*<<< orphan*/  align_buff; } ;
typedef  TYPE_7__ dwc_hc_t ;
struct TYPE_17__ {int /*<<< orphan*/  (* complete ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {int /*<<< orphan*/  dma_enable; } ;
struct TYPE_15__ {int /*<<< orphan*/  do_split; int /*<<< orphan*/  dw_align_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ASSERT (int,char*,int) ; 
 int /*<<< orphan*/  DWC_E_COMMUNICATION ; 
 int /*<<< orphan*/  DWC_E_NO_STREAM_RES ; 
 int /*<<< orphan*/  DWC_E_OVERFLOW ; 
 int /*<<< orphan*/  DWC_E_PROTOCOL ; 
 int /*<<< orphan*/  DWC_OTG_EP_TYPE_ISOC ; 
#define  DWC_OTG_HC_XFER_BABBLE_ERR 131 
#define  DWC_OTG_HC_XFER_COMPLETE 130 
#define  DWC_OTG_HC_XFER_FRAME_OVERRUN 129 
 int DWC_OTG_HC_XFER_URB_COMPLETE ; 
#define  DWC_OTG_HC_XFER_XACT_ERR 128 
 int /*<<< orphan*/  dwc_memcpy (scalar_t__,int /*<<< orphan*/ ,void*) ; 
 void* get_actual_xfer_length (TYPE_7__*,int /*<<< orphan*/ *,TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dwc_otg_halt_status_e
update_isoc_urb_state(dwc_otg_hcd_t * hcd,
		      dwc_hc_t * hc,
		      dwc_otg_hc_regs_t * hc_regs,
		      dwc_otg_qtd_t * qtd, dwc_otg_halt_status_e halt_status)
{
	dwc_otg_hcd_urb_t *urb = qtd->urb;
	dwc_otg_halt_status_e ret_val = halt_status;
	struct dwc_otg_hcd_iso_packet_desc *frame_desc;

	frame_desc = &urb->iso_descs[qtd->isoc_frame_index];
	switch (halt_status) {
	case DWC_OTG_HC_XFER_COMPLETE:
		frame_desc->status = 0;
		frame_desc->actual_length =
		    get_actual_xfer_length(hc, hc_regs, qtd, halt_status, NULL);

		/* non DWORD-aligned buffer case handling. */
		if (hc->align_buff && frame_desc->actual_length && hc->ep_is_in) {
			dwc_memcpy(urb->buf + frame_desc->offset + qtd->isoc_split_offset,
				   hc->qh->dw_align_buf, frame_desc->actual_length);
		}

		break;
	case DWC_OTG_HC_XFER_FRAME_OVERRUN:
		urb->error_count++;
		if (hc->ep_is_in) {
			frame_desc->status = -DWC_E_NO_STREAM_RES;
		} else {
			frame_desc->status = -DWC_E_COMMUNICATION;
		}
		frame_desc->actual_length = 0;
		break;
	case DWC_OTG_HC_XFER_BABBLE_ERR:
		urb->error_count++;
		frame_desc->status = -DWC_E_OVERFLOW;
		/* Don't need to update actual_length in this case. */
		break;
	case DWC_OTG_HC_XFER_XACT_ERR:
		urb->error_count++;
		frame_desc->status = -DWC_E_PROTOCOL;
		frame_desc->actual_length =
		    get_actual_xfer_length(hc, hc_regs, qtd, halt_status, NULL);

		/* non DWORD-aligned buffer case handling. */
		if (hc->align_buff && frame_desc->actual_length && hc->ep_is_in) {
			dwc_memcpy(urb->buf + frame_desc->offset + qtd->isoc_split_offset,
				   hc->qh->dw_align_buf, frame_desc->actual_length);
		}
		/* Skip whole frame */
		if (hc->qh->do_split && (hc->ep_type == DWC_OTG_EP_TYPE_ISOC) &&
		    hc->ep_is_in && hcd->core_if->dma_enable) {
			qtd->complete_split = 0;
			qtd->isoc_split_offset = 0;
		}

		break;
	default:
		DWC_ASSERT(1, "Unhandled _halt_status (%d)\n", halt_status);
		break;
	}
	if (++qtd->isoc_frame_index == urb->packet_count) {
		/*
		 * urb->status is not used for isoc transfers.
		 * The individual frame_desc statuses are used instead.
		 */
		hcd->fops->complete(hcd, urb->priv, urb, 0);
		ret_val = DWC_OTG_HC_XFER_URB_COMPLETE;
	} else {
		ret_val = DWC_OTG_HC_XFER_COMPLETE;
	}
	return ret_val;
}