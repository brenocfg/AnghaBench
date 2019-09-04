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
struct dwc2_qtd {scalar_t__ isoc_frame_index; TYPE_2__* urb; scalar_t__ error_count; scalar_t__ complete_split; scalar_t__ isoc_split_offset; } ;
struct dwc2_qh {int next_active_frame; int start_active_frame; int num_hs_transfers; scalar_t__ ep_type; int ping_state; scalar_t__ ep_is_in; } ;
struct TYPE_3__ {int /*<<< orphan*/  uframe_sched; scalar_t__ host_dma; } ;
struct dwc2_hsotg {TYPE_1__ params; int /*<<< orphan*/  dev; } ;
struct dwc2_host_chan {scalar_t__ ep_type; struct dwc2_qh* qh; scalar_t__ ep_is_in; scalar_t__ complete_split; scalar_t__ do_split; } ;
struct TYPE_4__ {scalar_t__ packet_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC2_HC_XFER_NO_HALT_STATUS ; 
 int /*<<< orphan*/  DWC2_HC_XFER_NYET ; 
 int /*<<< orphan*/  DWC2_HC_XFER_URB_COMPLETE ; 
 int /*<<< orphan*/  DWC2_HC_XFER_XACT_ERR ; 
 int /*<<< orphan*/  HCINTMSK_NYET ; 
 scalar_t__ USB_ENDPOINT_XFER_INT ; 
 scalar_t__ USB_ENDPOINT_XFER_ISOC ; 
 scalar_t__ dbg_hc (struct dwc2_host_chan*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  disable_hc_int (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int dwc2_frame_num_inc (int,int) ; 
 int dwc2_frame_num_le (int,int) ; 
 scalar_t__ dwc2_full_frame_num (int) ; 
 int /*<<< orphan*/  dwc2_halt_channel (struct dwc2_hsotg*,struct dwc2_host_chan*,struct dwc2_qtd*,int /*<<< orphan*/ ) ; 
 int dwc2_hcd_get_frame_number (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_hcd_save_data_toggle (struct dwc2_hsotg*,struct dwc2_host_chan*,int,struct dwc2_qtd*) ; 
 int /*<<< orphan*/  dwc2_host_complete (struct dwc2_hsotg*,struct dwc2_qtd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_release_channel (struct dwc2_hsotg*,struct dwc2_host_chan*,struct dwc2_qtd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_update_urb_state_abn (struct dwc2_hsotg*,struct dwc2_host_chan*,int,TYPE_2__*,struct dwc2_qtd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_hc_nyet_intr(struct dwc2_hsotg *hsotg,
			      struct dwc2_host_chan *chan, int chnum,
			      struct dwc2_qtd *qtd)
{
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "--Host Channel %d Interrupt: NYET Received--\n",
			 chnum);

	/*
	 * NYET on CSPLIT
	 * re-do the CSPLIT immediately on non-periodic
	 */
	if (chan->do_split && chan->complete_split) {
		if (chan->ep_is_in && chan->ep_type == USB_ENDPOINT_XFER_ISOC &&
		    hsotg->params.host_dma) {
			qtd->complete_split = 0;
			qtd->isoc_split_offset = 0;
			qtd->isoc_frame_index++;
			if (qtd->urb &&
			    qtd->isoc_frame_index == qtd->urb->packet_count) {
				dwc2_host_complete(hsotg, qtd, 0);
				dwc2_release_channel(hsotg, chan, qtd,
						     DWC2_HC_XFER_URB_COMPLETE);
			} else {
				dwc2_release_channel(hsotg, chan, qtd,
						DWC2_HC_XFER_NO_HALT_STATUS);
			}
			goto handle_nyet_done;
		}

		if (chan->ep_type == USB_ENDPOINT_XFER_INT ||
		    chan->ep_type == USB_ENDPOINT_XFER_ISOC) {
			struct dwc2_qh *qh = chan->qh;
			bool past_end;

			if (!hsotg->params.uframe_sched) {
				int frnum = dwc2_hcd_get_frame_number(hsotg);

				/* Don't have num_hs_transfers; simple logic */
				past_end = dwc2_full_frame_num(frnum) !=
				     dwc2_full_frame_num(qh->next_active_frame);
			} else {
				int end_frnum;

				/*
				 * Figure out the end frame based on
				 * schedule.
				 *
				 * We don't want to go on trying again
				 * and again forever. Let's stop when
				 * we've done all the transfers that
				 * were scheduled.
				 *
				 * We're going to be comparing
				 * start_active_frame and
				 * next_active_frame, both of which
				 * are 1 before the time the packet
				 * goes on the wire, so that cancels
				 * out. Basically if had 1 transfer
				 * and we saw 1 NYET then we're done.
				 * We're getting a NYET here so if
				 * next >= (start + num_transfers)
				 * we're done. The complexity is that
				 * for all but ISOC_OUT we skip one
				 * slot.
				 */
				end_frnum = dwc2_frame_num_inc(
					qh->start_active_frame,
					qh->num_hs_transfers);

				if (qh->ep_type != USB_ENDPOINT_XFER_ISOC ||
				    qh->ep_is_in)
					end_frnum =
					       dwc2_frame_num_inc(end_frnum, 1);

				past_end = dwc2_frame_num_le(
					end_frnum, qh->next_active_frame);
			}

			if (past_end) {
				/* Treat this as a transaction error. */
#if 0
				/*
				 * Todo: Fix system performance so this can
				 * be treated as an error. Right now complete
				 * splits cannot be scheduled precisely enough
				 * due to other system activity, so this error
				 * occurs regularly in Slave mode.
				 */
				qtd->error_count++;
#endif
				qtd->complete_split = 0;
				dwc2_halt_channel(hsotg, chan, qtd,
						  DWC2_HC_XFER_XACT_ERR);
				/* Todo: add support for isoc release */
				goto handle_nyet_done;
			}
		}

		dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_NYET);
		goto handle_nyet_done;
	}

	chan->qh->ping_state = 1;
	qtd->error_count = 0;

	dwc2_update_urb_state_abn(hsotg, chan, chnum, qtd->urb, qtd,
				  DWC2_HC_XFER_NYET);
	dwc2_hcd_save_data_toggle(hsotg, chan, chnum, qtd);

	/*
	 * Halt the channel and re-start the transfer so the PING protocol
	 * will start
	 */
	dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_NYET);

handle_nyet_done:
	disable_hc_int(hsotg, chnum, HCINTMSK_NYET);
}