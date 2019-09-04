#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct dwc_otg_hcd_iso_packet_desc {int length; } ;
typedef  int int32_t ;
struct TYPE_16__ {int complete_split; int isoc_split_pos; int isoc_split_offset; size_t isoc_frame_index; scalar_t__ error_count; TYPE_1__* urb; int /*<<< orphan*/  ssplit_out_xfer_count; } ;
typedef  TYPE_4__ dwc_otg_qtd_t ;
struct TYPE_17__ {TYPE_2__* core_if; } ;
typedef  TYPE_5__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hc_regs_t ;
struct TYPE_18__ {scalar_t__ data_pid_start; scalar_t__ ep_type; int xact_pos; TYPE_3__* qh; int /*<<< orphan*/  ep_is_in; int /*<<< orphan*/  xfer_len; scalar_t__ do_split; int /*<<< orphan*/  hc_num; } ;
typedef  TYPE_6__ dwc_hc_t ;
struct TYPE_15__ {scalar_t__ ping_state; } ;
struct TYPE_14__ {scalar_t__ dma_enable; } ;
struct TYPE_13__ {struct dwc_otg_hcd_iso_packet_desc* iso_descs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCDI ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
#define  DWC_HCSPLIT_XACTPOS_ALL 131 
#define  DWC_HCSPLIT_XACTPOS_BEGIN 130 
#define  DWC_HCSPLIT_XACTPOS_END 129 
#define  DWC_HCSPLIT_XACTPOS_MID 128 
 scalar_t__ DWC_OTG_EP_TYPE_ISOC ; 
 scalar_t__ DWC_OTG_HC_PID_SETUP ; 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_ACK ; 
 int /*<<< orphan*/  ack ; 
 int /*<<< orphan*/  datatglerr ; 
 int /*<<< orphan*/  disable_hc_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halt_channel (TYPE_5__*,TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nak ; 

__attribute__((used)) static int32_t handle_hc_ack_intr(dwc_otg_hcd_t * hcd,
				  dwc_hc_t * hc,
				  dwc_otg_hc_regs_t * hc_regs,
				  dwc_otg_qtd_t * qtd)
{
	DWC_DEBUGPL(DBG_HCDI, "--Host Channel %d Interrupt: "
		    "ACK Received--\n", hc->hc_num);

	if (hc->do_split) {
		/*
		 * Handle ACK on SSPLIT.
		 * ACK should not occur in CSPLIT.
		 */
		if (!hc->ep_is_in && hc->data_pid_start != DWC_OTG_HC_PID_SETUP) {
			qtd->ssplit_out_xfer_count = hc->xfer_len;
		}
		if (!(hc->ep_type == DWC_OTG_EP_TYPE_ISOC && !hc->ep_is_in)) {
			/* Don't need complete for isochronous out transfers. */
			qtd->complete_split = 1;
		}

		/* ISOC OUT */
		if (hc->ep_type == DWC_OTG_EP_TYPE_ISOC && !hc->ep_is_in) {
			switch (hc->xact_pos) {
			case DWC_HCSPLIT_XACTPOS_ALL:
				break;
			case DWC_HCSPLIT_XACTPOS_END:
				qtd->isoc_split_pos = DWC_HCSPLIT_XACTPOS_ALL;
				qtd->isoc_split_offset = 0;
				break;
			case DWC_HCSPLIT_XACTPOS_BEGIN:
			case DWC_HCSPLIT_XACTPOS_MID:
				/*
				 * For BEGIN or MID, calculate the length for
				 * the next microframe to determine the correct
				 * SSPLIT token, either MID or END.
				 */
				{
					struct dwc_otg_hcd_iso_packet_desc
					*frame_desc;

					frame_desc =
					    &qtd->urb->
					    iso_descs[qtd->isoc_frame_index];
					qtd->isoc_split_offset += 188;

					if ((frame_desc->length -
					     qtd->isoc_split_offset) <= 188) {
						qtd->isoc_split_pos =
						    DWC_HCSPLIT_XACTPOS_END;
					} else {
						qtd->isoc_split_pos =
						    DWC_HCSPLIT_XACTPOS_MID;
					}

				}
				break;
			}
		} else {
			halt_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_ACK);
		}
	} else {
		/*
		 * An unmasked ACK on a non-split DMA transaction is
		 * for the sole purpose of resetting error counts. Disable other
		 * interrupts unmasked for the same reason.
		 */
		if(hcd->core_if->dma_enable) {
			disable_hc_int(hc_regs, datatglerr);
			disable_hc_int(hc_regs, nak);
		}
		qtd->error_count = 0;

		if (hc->qh->ping_state) {
			hc->qh->ping_state = 0;
			/*
			 * Halt the channel so the transfer can be re-started
			 * from the appropriate point. This only happens in
			 * Slave mode. In DMA mode, the ping_state is cleared
			 * when the transfer is started because the core
			 * automatically executes the PING, then the transfer.
			 */
			halt_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_ACK);
		}
	}

	/*
	 * If the ACK occurred when _not_ in the PING state, let the channel
	 * continue transferring data after clearing the error count.
	 */

	disable_hc_int(hc_regs, ack);

	return 1;
}