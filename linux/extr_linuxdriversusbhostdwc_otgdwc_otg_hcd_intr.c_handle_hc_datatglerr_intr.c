#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_18__ {scalar_t__ error_count; int /*<<< orphan*/  urb; } ;
typedef  TYPE_3__ dwc_otg_qtd_t ;
struct TYPE_19__ {TYPE_1__* core_if; } ;
typedef  TYPE_4__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hc_regs_t ;
struct TYPE_20__ {scalar_t__ ep_is_in; TYPE_2__* qh; int /*<<< orphan*/  hc_num; } ;
typedef  TYPE_5__ dwc_hc_t ;
struct TYPE_17__ {scalar_t__ do_split; } ;
struct TYPE_16__ {scalar_t__ dma_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCDI ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_XACT_ERR ; 
 int /*<<< orphan*/  ack ; 
 int /*<<< orphan*/  datatglerr ; 
 int /*<<< orphan*/  disable_hc_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_hcd_save_data_toggle (TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  halt_channel (TYPE_4__*,TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nak ; 
 int /*<<< orphan*/  update_urb_state_xfer_intr (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t handle_hc_datatglerr_intr(dwc_otg_hcd_t * hcd,
					 dwc_hc_t * hc,
					 dwc_otg_hc_regs_t * hc_regs,
					 dwc_otg_qtd_t * qtd)
{
	DWC_DEBUGPL(DBG_HCDI, "--Host Channel %d Interrupt: "
		"Data Toggle Error on %s transfer--\n",
		hc->hc_num, (hc->ep_is_in ? "IN" : "OUT"));

	/* Data toggles on split transactions cause the hc to halt.
	 * restart transfer */
	if(hc->qh->do_split)
	{
		qtd->error_count++;
		dwc_otg_hcd_save_data_toggle(hc, hc_regs, qtd);
		update_urb_state_xfer_intr(hc, hc_regs,
			qtd->urb, qtd, DWC_OTG_HC_XFER_XACT_ERR);
		halt_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_XACT_ERR);
	} else if (hc->ep_is_in) {
		/* An unmasked data toggle error on a non-split DMA transaction is
		 * for the sole purpose of resetting error counts. Disable other
		 * interrupts unmasked for the same reason.
		 */
		if(hcd->core_if->dma_enable) {
			disable_hc_int(hc_regs, ack);
			disable_hc_int(hc_regs, nak);
		}
		qtd->error_count = 0;
	}

	disable_hc_int(hc_regs, datatglerr);

	return 1;
}