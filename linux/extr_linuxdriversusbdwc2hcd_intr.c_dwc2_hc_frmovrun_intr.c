#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dwc2_qtd {TYPE_1__* urb; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; } ;
struct dwc2_host_chan {int dummy; } ;
typedef  enum dwc2_halt_status { ____Placeholder_dwc2_halt_status } dwc2_halt_status ;
struct TYPE_2__ {int /*<<< orphan*/  pipe_info; } ;

/* Variables and functions */
 int DWC2_HC_XFER_FRAME_OVERRUN ; 
 int /*<<< orphan*/  HCINTMSK_FRMOVRUN ; 
#define  USB_ENDPOINT_XFER_BULK 131 
#define  USB_ENDPOINT_XFER_CONTROL 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 scalar_t__ dbg_hc (struct dwc2_host_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  disable_hc_int (struct dwc2_hsotg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_halt_channel (struct dwc2_hsotg*,struct dwc2_host_chan*,struct dwc2_qtd*,int) ; 
 int /*<<< orphan*/  dwc2_hc_handle_tt_clear (struct dwc2_hsotg*,struct dwc2_host_chan*,struct dwc2_qtd*) ; 
 int dwc2_hcd_get_pipe_type (int /*<<< orphan*/ *) ; 
 int dwc2_update_isoc_urb_state (struct dwc2_hsotg*,struct dwc2_host_chan*,int,struct dwc2_qtd*,int) ; 

__attribute__((used)) static void dwc2_hc_frmovrun_intr(struct dwc2_hsotg *hsotg,
				  struct dwc2_host_chan *chan, int chnum,
				  struct dwc2_qtd *qtd)
{
	enum dwc2_halt_status halt_status;

	if (dbg_hc(chan))
		dev_dbg(hsotg->dev, "--Host Channel %d Interrupt: Frame Overrun--\n",
			chnum);

	dwc2_hc_handle_tt_clear(hsotg, chan, qtd);

	switch (dwc2_hcd_get_pipe_type(&qtd->urb->pipe_info)) {
	case USB_ENDPOINT_XFER_CONTROL:
	case USB_ENDPOINT_XFER_BULK:
		break;
	case USB_ENDPOINT_XFER_INT:
		dwc2_halt_channel(hsotg, chan, qtd, DWC2_HC_XFER_FRAME_OVERRUN);
		break;
	case USB_ENDPOINT_XFER_ISOC:
		halt_status = dwc2_update_isoc_urb_state(hsotg, chan, chnum,
					qtd, DWC2_HC_XFER_FRAME_OVERRUN);
		dwc2_halt_channel(hsotg, chan, qtd, halt_status);
		break;
	}

	disable_hc_int(hsotg, chnum, HCINTMSK_FRMOVRUN);
}