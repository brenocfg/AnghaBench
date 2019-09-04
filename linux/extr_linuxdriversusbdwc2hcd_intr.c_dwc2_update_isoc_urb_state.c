#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dwc2_qtd {size_t isoc_frame_index; int /*<<< orphan*/  isoc_split_offset; int /*<<< orphan*/  complete_split; struct dwc2_hcd_urb* urb; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_dma; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; TYPE_2__ params; } ;
struct dwc2_host_chan {int /*<<< orphan*/  ep_is_in; int /*<<< orphan*/  ep_type; TYPE_1__* qh; } ;
struct dwc2_hcd_urb {size_t packet_count; int /*<<< orphan*/  error_count; struct dwc2_hcd_iso_packet_desc* iso_descs; } ;
struct dwc2_hcd_iso_packet_desc {void* actual_length; int /*<<< orphan*/  status; } ;
typedef  enum dwc2_halt_status { ____Placeholder_dwc2_halt_status } dwc2_halt_status ;
struct TYPE_3__ {int /*<<< orphan*/  do_split; } ;

/* Variables and functions */
#define  DWC2_HC_XFER_BABBLE_ERR 131 
#define  DWC2_HC_XFER_COMPLETE 130 
#define  DWC2_HC_XFER_FRAME_OVERRUN 129 
 int DWC2_HC_XFER_NO_HALT_STATUS ; 
 int DWC2_HC_XFER_URB_COMPLETE ; 
#define  DWC2_HC_XFER_XACT_ERR 128 
 int /*<<< orphan*/  ECOMM ; 
 int /*<<< orphan*/  ENOSR ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  EPROTO ; 
 int /*<<< orphan*/  USB_ENDPOINT_XFER_ISOC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 void* dwc2_get_actual_xfer_length (struct dwc2_hsotg*,struct dwc2_host_chan*,int,struct dwc2_qtd*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc2_host_complete (struct dwc2_hsotg*,struct dwc2_qtd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum dwc2_halt_status dwc2_update_isoc_urb_state(
		struct dwc2_hsotg *hsotg, struct dwc2_host_chan *chan,
		int chnum, struct dwc2_qtd *qtd,
		enum dwc2_halt_status halt_status)
{
	struct dwc2_hcd_iso_packet_desc *frame_desc;
	struct dwc2_hcd_urb *urb = qtd->urb;

	if (!urb)
		return DWC2_HC_XFER_NO_HALT_STATUS;

	frame_desc = &urb->iso_descs[qtd->isoc_frame_index];

	switch (halt_status) {
	case DWC2_HC_XFER_COMPLETE:
		frame_desc->status = 0;
		frame_desc->actual_length = dwc2_get_actual_xfer_length(hsotg,
					chan, chnum, qtd, halt_status, NULL);
		break;
	case DWC2_HC_XFER_FRAME_OVERRUN:
		urb->error_count++;
		if (chan->ep_is_in)
			frame_desc->status = -ENOSR;
		else
			frame_desc->status = -ECOMM;
		frame_desc->actual_length = 0;
		break;
	case DWC2_HC_XFER_BABBLE_ERR:
		urb->error_count++;
		frame_desc->status = -EOVERFLOW;
		/* Don't need to update actual_length in this case */
		break;
	case DWC2_HC_XFER_XACT_ERR:
		urb->error_count++;
		frame_desc->status = -EPROTO;
		frame_desc->actual_length = dwc2_get_actual_xfer_length(hsotg,
					chan, chnum, qtd, halt_status, NULL);

		/* Skip whole frame */
		if (chan->qh->do_split &&
		    chan->ep_type == USB_ENDPOINT_XFER_ISOC && chan->ep_is_in &&
		    hsotg->params.host_dma) {
			qtd->complete_split = 0;
			qtd->isoc_split_offset = 0;
		}

		break;
	default:
		dev_err(hsotg->dev, "Unhandled halt_status (%d)\n",
			halt_status);
		break;
	}

	if (++qtd->isoc_frame_index == urb->packet_count) {
		/*
		 * urb->status is not used for isoc transfers. The individual
		 * frame_desc statuses are used instead.
		 */
		dwc2_host_complete(hsotg, qtd, 0);
		halt_status = DWC2_HC_XFER_URB_COMPLETE;
	} else {
		halt_status = DWC2_HC_XFER_COMPLETE;
	}

	return halt_status;
}