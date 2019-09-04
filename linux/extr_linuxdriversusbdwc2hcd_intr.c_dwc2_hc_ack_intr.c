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
struct dwc2_qtd {int complete_split; int isoc_split_pos; int isoc_split_offset; size_t isoc_frame_index; scalar_t__ error_count; TYPE_1__* urb; int /*<<< orphan*/  ssplit_out_xfer_count; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; } ;
struct dwc2_host_chan {scalar_t__ data_pid_start; scalar_t__ ep_type; int xact_pos; TYPE_2__* qh; scalar_t__ ep_is_in; int /*<<< orphan*/  xfer_len; scalar_t__ do_split; } ;
struct dwc2_hcd_iso_packet_desc {int length; } ;
struct TYPE_4__ {scalar_t__ ping_state; } ;
struct TYPE_3__ {struct dwc2_hcd_iso_packet_desc* iso_descs; } ;

/* Variables and functions */
#define  DWC2_HCSPLT_XACTPOS_ALL 131 
#define  DWC2_HCSPLT_XACTPOS_BEGIN 130 
#define  DWC2_HCSPLT_XACTPOS_END 129 
#define  DWC2_HCSPLT_XACTPOS_MID 128 
 scalar_t__ DWC2_HC_PID_SETUP ; 
 int /*<<< orphan*/  DWC2_HC_XFER_ACK ; 
 int /*<<< orphan*/  HCINTMSK_ACK ; 
 scalar_t__ USB_ENDPOINT_XFER_ISOC ; 
 scalar_t__ dbg_hc (struct dwc2_host_chan*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  disable_hc_int (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_halt_channel (struct dwc2_hsotg*,struct dwc2_host_chan*,struct dwc2_qtd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_hc_ack_intr(struct dwc2_hsotg *hsotg,
			     struct dwc2_host_chan *chan, int chnum,
			     struct dwc2_qtd *qtd)
{
	struct dwc2_hcd_iso_packet_desc *frame_desc;

	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "--Host Channel %d Interrupt: ACK Received--\n",
			 chnum);

	if (chan->do_split) {
		/* Handle ACK on SSPLIT. ACK should not occur in CSPLIT. */
		if (!chan->ep_is_in &&
		    chan->data_pid_start != DWC2_HC_PID_SETUP)
			qtd->ssplit_out_xfer_count = chan->xfer_len;

		if (chan->ep_type != USB_ENDPOINT_XFER_ISOC || chan->ep_is_in) {
			qtd->complete_split = 1;
			dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_ACK);
		} else {
			/* ISOC OUT */
			switch (chan->xact_pos) {
			case DWC2_HCSPLT_XACTPOS_ALL:
				break;
			case DWC2_HCSPLT_XACTPOS_END:
				qtd->isoc_split_pos = DWC2_HCSPLT_XACTPOS_ALL;
				qtd->isoc_split_offset = 0;
				break;
			case DWC2_HCSPLT_XACTPOS_BEGIN:
			case DWC2_HCSPLT_XACTPOS_MID:
				/*
				 * For BEGIN or MID, calculate the length for
				 * the next microframe to determine the correct
				 * SSPLIT token, either MID or END
				 */
				frame_desc = &qtd->urb->iso_descs[
						qtd->isoc_frame_index];
				qtd->isoc_split_offset += 188;

				if (frame_desc->length - qtd->isoc_split_offset
							<= 188)
					qtd->isoc_split_pos =
							DWC2_HCSPLT_XACTPOS_END;
				else
					qtd->isoc_split_pos =
							DWC2_HCSPLT_XACTPOS_MID;
				break;
			}
		}
	} else {
		qtd->error_count = 0;

		if (chan->qh->ping_state) {
			chan->qh->ping_state = 0;
			/*
			 * Halt the channel so the transfer can be re-started
			 * from the appropriate point. This only happens in
			 * Slave mode. In DMA mode, the ping_state is cleared
			 * when the transfer is started because the core
			 * automatically executes the PING, then the transfer.
			 */
			dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_ACK);
		}
	}

	/*
	 * If the ACK occurred when _not_ in the PING state, let the channel
	 * continue transferring data after clearing the error count
	 */
	disable_hc_int(hsotg, chnum, HCINTMSK_ACK);
}