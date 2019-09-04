#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_22__ {scalar_t__ error_count; TYPE_8__* urb; scalar_t__ complete_split; TYPE_1__* qh; } ;
typedef  TYPE_4__ dwc_otg_qtd_t ;
struct TYPE_23__ {TYPE_2__* core_if; } ;
typedef  TYPE_5__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hc_regs_t ;
struct TYPE_24__ {TYPE_3__* qh; int /*<<< orphan*/  speed; int /*<<< orphan*/  ep_is_in; scalar_t__ complete_split; scalar_t__ do_split; int /*<<< orphan*/  hc_num; } ;
typedef  TYPE_6__ dwc_hc_t ;
struct TYPE_25__ {int /*<<< orphan*/  pipe_info; } ;
struct TYPE_21__ {int ping_state; int /*<<< orphan*/  nak_frame; } ;
struct TYPE_20__ {int /*<<< orphan*/  dma_enable; } ;
struct TYPE_19__ {int /*<<< orphan*/  do_split; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCDI ; 
 int /*<<< orphan*/  DWC_ASSERT (int,char*) ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_OTG_EP_SPEED_HIGH ; 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_NAK ; 
#define  UE_BULK 131 
#define  UE_CONTROL 130 
#define  UE_INTERRUPT 129 
#define  UE_ISOCHRONOUS 128 
 int /*<<< orphan*/  ack ; 
 int /*<<< orphan*/  datatglerr ; 
 int /*<<< orphan*/  disable_hc_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_hcd_get_frame_number (TYPE_5__*) ; 
 int dwc_otg_hcd_get_pipe_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_hcd_save_data_toggle (TYPE_6__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  halt_channel (TYPE_5__*,TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nak ; 
 int /*<<< orphan*/  nak_holdoff ; 
 int /*<<< orphan*/  update_urb_state_xfer_intr (TYPE_6__*,int /*<<< orphan*/ *,TYPE_8__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t handle_hc_nak_intr(dwc_otg_hcd_t * hcd,
				  dwc_hc_t * hc,
				  dwc_otg_hc_regs_t * hc_regs,
				  dwc_otg_qtd_t * qtd)
{
	DWC_DEBUGPL(DBG_HCDI, "--Host Channel %d Interrupt: "
		    "NAK Received--\n", hc->hc_num);

	/*
	 * When we get bulk NAKs then remember this so we holdoff on this qh until
	 * the beginning of the next frame
	 */
	switch(dwc_otg_hcd_get_pipe_type(&qtd->urb->pipe_info)) {
		case UE_BULK:
		case UE_CONTROL:
		if (nak_holdoff && qtd->qh->do_split)
			hc->qh->nak_frame = dwc_otg_hcd_get_frame_number(hcd);
	}

	/*
	 * Handle NAK for IN/OUT SSPLIT/CSPLIT transfers, bulk, control, and
	 * interrupt.  Re-start the SSPLIT transfer.
	 */
	if (hc->do_split) {
		if (hc->complete_split) {
			qtd->error_count = 0;
		}
		qtd->complete_split = 0;
		halt_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_NAK);
		goto handle_nak_done;
	}

	switch (dwc_otg_hcd_get_pipe_type(&qtd->urb->pipe_info)) {
	case UE_CONTROL:
	case UE_BULK:
		if (hcd->core_if->dma_enable && hc->ep_is_in) {
			/*
			 * NAK interrupts are enabled on bulk/control IN
			 * transfers in DMA mode for the sole purpose of
			 * resetting the error count after a transaction error
			 * occurs. The core will continue transferring data.
			 * Disable other interrupts unmasked for the same
			 * reason.
			 */
			disable_hc_int(hc_regs, datatglerr);
			disable_hc_int(hc_regs, ack);
			qtd->error_count = 0;
			goto handle_nak_done;
		}

		/*
		 * NAK interrupts normally occur during OUT transfers in DMA
		 * or Slave mode. For IN transfers, more requests will be
		 * queued as request queue space is available.
		 */
		qtd->error_count = 0;

		if (!hc->qh->ping_state) {
			update_urb_state_xfer_intr(hc, hc_regs,
						   qtd->urb, qtd,
						   DWC_OTG_HC_XFER_NAK);
			dwc_otg_hcd_save_data_toggle(hc, hc_regs, qtd);

			if (hc->speed == DWC_OTG_EP_SPEED_HIGH)
				hc->qh->ping_state = 1;
		}

		/*
		 * Halt the channel so the transfer can be re-started from
		 * the appropriate point or the PING protocol will
		 * start/continue.
		 */
		halt_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_NAK);
		break;
	case UE_INTERRUPT:
		qtd->error_count = 0;
		halt_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_NAK);
		break;
	case UE_ISOCHRONOUS:
		/* Should never get called for isochronous transfers. */
		DWC_ASSERT(1, "NACK interrupt for ISOC transfer\n");
		break;
	}

handle_nak_done:
	disable_hc_int(hc_regs, nak);

	return 1;
}