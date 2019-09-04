#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_24__ {int /*<<< orphan*/  complete_split; int /*<<< orphan*/  error_count; TYPE_7__* urb; } ;
typedef  TYPE_3__ dwc_otg_qtd_t ;
struct TYPE_25__ {TYPE_1__* core_if; } ;
typedef  TYPE_4__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hc_regs_t ;
typedef  int /*<<< orphan*/  dwc_otg_halt_status_e ;
struct TYPE_26__ {int /*<<< orphan*/  complete_split; int /*<<< orphan*/  do_split; TYPE_2__* qh; int /*<<< orphan*/  speed; int /*<<< orphan*/  ep_is_in; int /*<<< orphan*/  hc_num; } ;
typedef  TYPE_5__ dwc_hc_t ;
struct TYPE_27__ {int /*<<< orphan*/  pipe_info; } ;
struct TYPE_23__ {int ping_state; } ;
struct TYPE_22__ {scalar_t__ dma_desc_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCDI ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_OTG_EP_SPEED_HIGH ; 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_XACT_ERR ; 
#define  UE_BULK 131 
#define  UE_CONTROL 130 
#define  UE_INTERRUPT 129 
#define  UE_ISOCHRONOUS 128 
 int /*<<< orphan*/  disable_hc_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_hcd_complete_xfer_ddma (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dwc_otg_hcd_get_pipe_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_hcd_save_data_toggle (TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  halt_channel (TYPE_4__*,TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_isoc_urb_state (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_urb_state_xfer_intr (TYPE_5__*,int /*<<< orphan*/ *,TYPE_7__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xacterr ; 

__attribute__((used)) static int32_t handle_hc_xacterr_intr(dwc_otg_hcd_t * hcd,
				      dwc_hc_t * hc,
				      dwc_otg_hc_regs_t * hc_regs,
				      dwc_otg_qtd_t * qtd)
{
	DWC_DEBUGPL(DBG_HCDI, "--Host Channel %d Interrupt: "
		    "Transaction Error--\n", hc->hc_num);

	if (hcd->core_if->dma_desc_enable) {
		dwc_otg_hcd_complete_xfer_ddma(hcd, hc, hc_regs,
					       DWC_OTG_HC_XFER_XACT_ERR);
		goto handle_xacterr_done;
	}

	switch (dwc_otg_hcd_get_pipe_type(&qtd->urb->pipe_info)) {
	case UE_CONTROL:
	case UE_BULK:
		qtd->error_count++;
		if (!hc->qh->ping_state) {

			update_urb_state_xfer_intr(hc, hc_regs,
						   qtd->urb, qtd,
						   DWC_OTG_HC_XFER_XACT_ERR);
			dwc_otg_hcd_save_data_toggle(hc, hc_regs, qtd);
			if (!hc->ep_is_in && hc->speed == DWC_OTG_EP_SPEED_HIGH) {
				hc->qh->ping_state = 1;
			}
		}

		/*
		 * Halt the channel so the transfer can be re-started from
		 * the appropriate point or the PING protocol will start.
		 */
		halt_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_XACT_ERR);
		break;
	case UE_INTERRUPT:
		qtd->error_count++;
		if (hc->do_split && hc->complete_split) {
			qtd->complete_split = 0;
		}
		halt_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_XACT_ERR);
		break;
	case UE_ISOCHRONOUS:
		{
			dwc_otg_halt_status_e halt_status;
			halt_status =
			    update_isoc_urb_state(hcd, hc, hc_regs, qtd,
						  DWC_OTG_HC_XFER_XACT_ERR);

			halt_channel(hcd, hc, qtd, halt_status);
		}
		break;
	}
handle_xacterr_done:
	disable_hc_int(hc_regs, xacterr);

	return 1;
}