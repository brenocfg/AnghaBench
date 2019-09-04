#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_22__ {TYPE_10__* urb; } ;
typedef  TYPE_3__ dwc_otg_qtd_t ;
struct TYPE_23__ {TYPE_1__* fops; TYPE_2__* core_if; } ;
typedef  TYPE_4__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hc_regs_t ;
typedef  int /*<<< orphan*/  dwc_otg_halt_status_e ;
struct TYPE_24__ {scalar_t__ ep_type; int /*<<< orphan*/  hc_num; } ;
typedef  TYPE_5__ dwc_hc_t ;
struct TYPE_21__ {scalar_t__ dma_desc_enable; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* complete ) (TYPE_4__*,int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCDI ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_E_OVERFLOW ; 
 scalar_t__ DWC_OTG_EP_TYPE_ISOC ; 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_BABBLE_ERR ; 
 int /*<<< orphan*/  bblerr ; 
 int /*<<< orphan*/  disable_hc_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_hcd_complete_xfer_ddma (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halt_channel (TYPE_4__*,TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_isoc_urb_state (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t handle_hc_babble_intr(dwc_otg_hcd_t * hcd,
				     dwc_hc_t * hc,
				     dwc_otg_hc_regs_t * hc_regs,
				     dwc_otg_qtd_t * qtd)
{
	DWC_DEBUGPL(DBG_HCDI, "--Host Channel %d Interrupt: "
		    "Babble Error--\n", hc->hc_num);

	if (hcd->core_if->dma_desc_enable) {
		dwc_otg_hcd_complete_xfer_ddma(hcd, hc, hc_regs,
					       DWC_OTG_HC_XFER_BABBLE_ERR);
		goto handle_babble_done;
	}

	if (hc->ep_type != DWC_OTG_EP_TYPE_ISOC) {
		hcd->fops->complete(hcd, qtd->urb->priv,
				    qtd->urb, -DWC_E_OVERFLOW);
		halt_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_BABBLE_ERR);
	} else {
		dwc_otg_halt_status_e halt_status;
		halt_status = update_isoc_urb_state(hcd, hc, hc_regs, qtd,
						    DWC_OTG_HC_XFER_BABBLE_ERR);
		halt_channel(hcd, hc, qtd, halt_status);
	}

handle_babble_done:
	disable_hc_int(hc_regs, bblerr);
	return 1;
}