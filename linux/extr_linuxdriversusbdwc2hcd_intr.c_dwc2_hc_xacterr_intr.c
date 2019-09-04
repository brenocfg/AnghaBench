#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dwc2_qtd {int /*<<< orphan*/  complete_split; int /*<<< orphan*/  error_count; TYPE_3__* urb; } ;
struct TYPE_4__ {scalar_t__ dma_desc_enable; } ;
struct dwc2_hsotg {TYPE_1__ params; int /*<<< orphan*/  dev; } ;
struct dwc2_host_chan {int /*<<< orphan*/  complete_split; int /*<<< orphan*/  do_split; TYPE_2__* qh; int /*<<< orphan*/  speed; int /*<<< orphan*/  ep_is_in; } ;
typedef  enum dwc2_halt_status { ____Placeholder_dwc2_halt_status } dwc2_halt_status ;
struct TYPE_6__ {int /*<<< orphan*/  pipe_info; } ;
struct TYPE_5__ {int ping_state; } ;

/* Variables and functions */
 int DWC2_HC_XFER_XACT_ERR ; 
 int /*<<< orphan*/  HCINTMSK_XACTERR ; 
#define  USB_ENDPOINT_XFER_BULK 131 
#define  USB_ENDPOINT_XFER_CONTROL 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  disable_hc_int (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_halt_channel (struct dwc2_hsotg*,struct dwc2_host_chan*,struct dwc2_qtd*,int) ; 
 int /*<<< orphan*/  dwc2_hc_handle_tt_clear (struct dwc2_hsotg*,struct dwc2_host_chan*,struct dwc2_qtd*) ; 
 int /*<<< orphan*/  dwc2_hcd_complete_xfer_ddma (struct dwc2_hsotg*,struct dwc2_host_chan*,int,int) ; 
 int dwc2_hcd_get_pipe_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc2_hcd_save_data_toggle (struct dwc2_hsotg*,struct dwc2_host_chan*,int,struct dwc2_qtd*) ; 
 int dwc2_update_isoc_urb_state (struct dwc2_hsotg*,struct dwc2_host_chan*,int,struct dwc2_qtd*,int) ; 
 int /*<<< orphan*/  dwc2_update_urb_state_abn (struct dwc2_hsotg*,struct dwc2_host_chan*,int,TYPE_3__*,struct dwc2_qtd*,int) ; 

__attribute__((used)) static void dwc2_hc_xacterr_intr(struct dwc2_hsotg *hsotg,
				 struct dwc2_host_chan *chan, int chnum,
				 struct dwc2_qtd *qtd)
{
	dev_dbg(hsotg->dev,
		"--Host Channel %d Interrupt: Transaction Error--\n", chnum);

	dwc2_hc_handle_tt_clear(hsotg, chan, qtd);

	if (hsotg->params.dma_desc_enable) {
		dwc2_hcd_complete_xfer_ddma(hsotg, chan, chnum,
					    DWC2_HC_XFER_XACT_ERR);
		goto handle_xacterr_done;
	}

	switch (dwc2_hcd_get_pipe_type(&qtd->urb->pipe_info)) {
	case USB_ENDPOINT_XFER_CONTROL:
	case USB_ENDPOINT_XFER_BULK:
		qtd->error_count++;
		if (!chan->qh->ping_state) {
			dwc2_update_urb_state_abn(hsotg, chan, chnum, qtd->urb,
						  qtd, DWC2_HC_XFER_XACT_ERR);
			dwc2_hcd_save_data_toggle(hsotg, chan, chnum, qtd);
			if (!chan->ep_is_in && chan->speed == USB_SPEED_HIGH)
				chan->qh->ping_state = 1;
		}

		/*
		 * Halt the channel so the transfer can be re-started from
		 * the appropriate point or the PING protocol will start
		 */
		dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_XACT_ERR);
		break;
	case USB_ENDPOINT_XFER_INT:
		qtd->error_count++;
		if (chan->do_split && chan->complete_split)
			qtd->complete_split = 0;
		dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_XACT_ERR);
		break;
	case USB_ENDPOINT_XFER_ISOC:
		{
			enum dwc2_halt_status halt_status;

			halt_status = dwc2_update_isoc_urb_state(hsotg, chan,
					 chnum, qtd, DWC2_HC_XFER_XACT_ERR);
			dwc2_halt_channel(hsotg, chan, qtd, halt_status);
		}
		break;
	}

handle_xacterr_done:
	disable_hc_int(hsotg, chnum, HCINTMSK_XACTERR);
}