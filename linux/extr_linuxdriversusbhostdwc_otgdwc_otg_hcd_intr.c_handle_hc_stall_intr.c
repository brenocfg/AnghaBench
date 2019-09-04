#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_23__ {TYPE_5__* urb; } ;
typedef  TYPE_4__ dwc_otg_qtd_t ;
struct TYPE_24__ {int /*<<< orphan*/  priv; int /*<<< orphan*/  pipe_info; } ;
typedef  TYPE_5__ dwc_otg_hcd_urb_t ;
struct TYPE_25__ {TYPE_2__* fops; TYPE_1__* core_if; } ;
typedef  TYPE_6__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hc_regs_t ;
struct TYPE_26__ {TYPE_3__* qh; int /*<<< orphan*/  hc_num; } ;
typedef  TYPE_7__ dwc_hc_t ;
struct TYPE_22__ {scalar_t__ data_toggle; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* complete ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_20__ {scalar_t__ dma_desc_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_E_PIPE ; 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_STALL ; 
 int UE_BULK ; 
 int UE_CONTROL ; 
 int UE_INTERRUPT ; 
 int /*<<< orphan*/  disable_hc_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_hcd_complete_xfer_ddma (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dwc_otg_hcd_get_pipe_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  halt_channel (TYPE_6__*,TYPE_7__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stall ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t handle_hc_stall_intr(dwc_otg_hcd_t * hcd,
				    dwc_hc_t * hc,
				    dwc_otg_hc_regs_t * hc_regs,
				    dwc_otg_qtd_t * qtd)
{
	dwc_otg_hcd_urb_t *urb = qtd->urb;
	int pipe_type = dwc_otg_hcd_get_pipe_type(&urb->pipe_info);

	DWC_DEBUGPL(DBG_HCD, "--Host Channel %d Interrupt: "
		    "STALL Received--\n", hc->hc_num);

	if (hcd->core_if->dma_desc_enable) {
		dwc_otg_hcd_complete_xfer_ddma(hcd, hc, hc_regs, DWC_OTG_HC_XFER_STALL);
		goto handle_stall_done;
	}

	if (pipe_type == UE_CONTROL) {
		hcd->fops->complete(hcd, urb->priv, urb, -DWC_E_PIPE);
	}

	if (pipe_type == UE_BULK || pipe_type == UE_INTERRUPT) {
		hcd->fops->complete(hcd, urb->priv, urb, -DWC_E_PIPE);
		/*
		 * USB protocol requires resetting the data toggle for bulk
		 * and interrupt endpoints when a CLEAR_FEATURE(ENDPOINT_HALT)
		 * setup command is issued to the endpoint. Anticipate the
		 * CLEAR_FEATURE command since a STALL has occurred and reset
		 * the data toggle now.
		 */
		hc->qh->data_toggle = 0;
	}

	halt_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_STALL);

handle_stall_done:
	disable_hc_int(hc_regs, stall);

	return 1;
}