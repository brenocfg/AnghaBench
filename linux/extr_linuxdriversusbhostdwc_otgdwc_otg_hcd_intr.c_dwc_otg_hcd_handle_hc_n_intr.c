#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_73__   TYPE_9__ ;
typedef  struct TYPE_72__   TYPE_8__ ;
typedef  struct TYPE_71__   TYPE_7__ ;
typedef  struct TYPE_70__   TYPE_6__ ;
typedef  struct TYPE_69__   TYPE_5__ ;
typedef  struct TYPE_68__   TYPE_58__ ;
typedef  struct TYPE_67__   TYPE_4__ ;
typedef  struct TYPE_66__   TYPE_3__ ;
typedef  struct TYPE_65__   TYPE_2__ ;
typedef  struct TYPE_64__   TYPE_1__ ;
typedef  struct TYPE_63__   TYPE_11__ ;
typedef  struct TYPE_62__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int int32_t ;
struct TYPE_70__ {int d32; } ;
typedef  TYPE_6__ hcintmsk_data_t ;
struct TYPE_69__ {scalar_t__ datatglerr; scalar_t__ frmovrun; scalar_t__ bblerr; scalar_t__ xacterr; scalar_t__ nyet; scalar_t__ chhltd; scalar_t__ ack; scalar_t__ nak; scalar_t__ stall; scalar_t__ ahberr; scalar_t__ xfercomp; } ;
struct TYPE_71__ {int d32; TYPE_5__ b; } ;
typedef  TYPE_7__ hcint_data_t ;
struct TYPE_72__ {int /*<<< orphan*/  error_count; } ;
typedef  TYPE_8__ dwc_otg_qtd_t ;
struct TYPE_73__ {TYPE_4__* core_if; TYPE_58__* fiq_state; TYPE_11__** hc_ptr_array; } ;
typedef  TYPE_9__ dwc_otg_hcd_t ;
struct TYPE_62__ {int /*<<< orphan*/  hcintmsk; int /*<<< orphan*/  hcint; } ;
typedef  TYPE_10__ dwc_otg_hc_regs_t ;
struct TYPE_63__ {scalar_t__ halt_status; TYPE_2__* qh; } ;
typedef  TYPE_11__ dwc_hc_t ;
struct TYPE_68__ {TYPE_3__* channel; } ;
struct TYPE_67__ {int /*<<< orphan*/  dma_enable; TYPE_1__* host_if; } ;
struct TYPE_66__ {int fsm; int /*<<< orphan*/  nr_errors; } ;
struct TYPE_65__ {int /*<<< orphan*/  qtd_list; } ;
struct TYPE_64__ {TYPE_10__** hc_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCDV ; 
 TYPE_8__* DWC_CIRCLEQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ DWC_OTG_HC_XFER_URB_DEQUEUE ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIQDBG_ERR ; 
#define  FIQ_PASSTHROUGH 129 
#define  FIQ_PASSTHROUGH_ERRORSTATE 128 
 int /*<<< orphan*/  dwc_otg_hcd_handle_hc_fsm (TYPE_9__*,size_t) ; 
 scalar_t__ fiq_fsm_enable ; 
 int /*<<< orphan*/  fiq_print (int /*<<< orphan*/ ,TYPE_58__*,char*,...) ; 
 int handle_hc_ack_intr (TYPE_9__*,TYPE_11__*,TYPE_10__*,TYPE_8__*) ; 
 int handle_hc_ahberr_intr (TYPE_9__*,TYPE_11__*,TYPE_10__*,TYPE_8__*) ; 
 int handle_hc_babble_intr (TYPE_9__*,TYPE_11__*,TYPE_10__*,TYPE_8__*) ; 
 int handle_hc_chhltd_intr (TYPE_9__*,TYPE_11__*,TYPE_10__*,TYPE_8__*) ; 
 int handle_hc_datatglerr_intr (TYPE_9__*,TYPE_11__*,TYPE_10__*,TYPE_8__*) ; 
 int handle_hc_frmovrun_intr (TYPE_9__*,TYPE_11__*,TYPE_10__*,TYPE_8__*) ; 
 int handle_hc_nak_intr (TYPE_9__*,TYPE_11__*,TYPE_10__*,TYPE_8__*) ; 
 int handle_hc_nyet_intr (TYPE_9__*,TYPE_11__*,TYPE_10__*,TYPE_8__*) ; 
 int handle_hc_stall_intr (TYPE_9__*,TYPE_11__*,TYPE_10__*,TYPE_8__*) ; 
 int handle_hc_xacterr_intr (TYPE_9__*,TYPE_11__*,TYPE_10__*,TYPE_8__*) ; 
 int handle_hc_xfercomp_intr (TYPE_9__*,TYPE_11__*,TYPE_10__*,TYPE_8__*) ; 
 int /*<<< orphan*/  release_channel (TYPE_9__*,TYPE_11__*,int /*<<< orphan*/ *,scalar_t__) ; 

int32_t dwc_otg_hcd_handle_hc_n_intr(dwc_otg_hcd_t * dwc_otg_hcd, uint32_t num)
{
	int retval = 0;
	hcint_data_t hcint;
	hcintmsk_data_t hcintmsk;
	dwc_hc_t *hc;
	dwc_otg_hc_regs_t *hc_regs;
	dwc_otg_qtd_t *qtd;

	DWC_DEBUGPL(DBG_HCDV, "--Host Channel Interrupt--, Channel %d\n", num);

	hc = dwc_otg_hcd->hc_ptr_array[num];
	hc_regs = dwc_otg_hcd->core_if->host_if->hc_regs[num];
	if(hc->halt_status == DWC_OTG_HC_XFER_URB_DEQUEUE) {
		/* A dequeue was issued for this transfer. Our QTD has gone away
		 * but in the case of a FIQ transfer, the transfer would have run
		 * to completion.
		 */
		if (fiq_fsm_enable && dwc_otg_hcd->fiq_state->channel[num].fsm != FIQ_PASSTHROUGH) {
			dwc_otg_hcd_handle_hc_fsm(dwc_otg_hcd, num);
		} else {
			release_channel(dwc_otg_hcd, hc, NULL, hc->halt_status);
		}
		return 1;
	}
	qtd = DWC_CIRCLEQ_FIRST(&hc->qh->qtd_list);

	/*
	 * FSM mode: Check to see if this is a HC interrupt from a channel handled by the FIQ.
	 * Execution path is fundamentally different for the channels after a FIQ has completed
	 * a split transaction.
	 */
	if (fiq_fsm_enable) {
		switch (dwc_otg_hcd->fiq_state->channel[num].fsm) {
			case FIQ_PASSTHROUGH:
				break;
			case FIQ_PASSTHROUGH_ERRORSTATE:
				/* Hook into the error count */
				fiq_print(FIQDBG_ERR, dwc_otg_hcd->fiq_state, "HCDERR%02d", num);
				if (!dwc_otg_hcd->fiq_state->channel[num].nr_errors) {
					qtd->error_count = 0;
					fiq_print(FIQDBG_ERR, dwc_otg_hcd->fiq_state, "RESET   ");
				}
				break;
			default:
				dwc_otg_hcd_handle_hc_fsm(dwc_otg_hcd, num);
				return 1;
		}
	}

	hcint.d32 = DWC_READ_REG32(&hc_regs->hcint);
	hcintmsk.d32 = DWC_READ_REG32(&hc_regs->hcintmsk);
	hcint.d32 = hcint.d32 & hcintmsk.d32;
	if (!dwc_otg_hcd->core_if->dma_enable) {
		if (hcint.b.chhltd && hcint.d32 != 0x2) {
			hcint.b.chhltd = 0;
		}
	}

	if (hcint.b.xfercomp) {
		retval |=
		    handle_hc_xfercomp_intr(dwc_otg_hcd, hc, hc_regs, qtd);
		/*
		 * If NYET occurred at same time as Xfer Complete, the NYET is
		 * handled by the Xfer Complete interrupt handler. Don't want
		 * to call the NYET interrupt handler in this case.
		 */
		hcint.b.nyet = 0;
	}
	if (hcint.b.chhltd) {
		retval |= handle_hc_chhltd_intr(dwc_otg_hcd, hc, hc_regs, qtd);
	}
	if (hcint.b.ahberr) {
		retval |= handle_hc_ahberr_intr(dwc_otg_hcd, hc, hc_regs, qtd);
	}
	if (hcint.b.stall) {
		retval |= handle_hc_stall_intr(dwc_otg_hcd, hc, hc_regs, qtd);
	}
	if (hcint.b.nak) {
		retval |= handle_hc_nak_intr(dwc_otg_hcd, hc, hc_regs, qtd);
	}
	if (hcint.b.ack) {
		if(!hcint.b.chhltd)
			retval |= handle_hc_ack_intr(dwc_otg_hcd, hc, hc_regs, qtd);
	}
	if (hcint.b.nyet) {
		retval |= handle_hc_nyet_intr(dwc_otg_hcd, hc, hc_regs, qtd);
	}
	if (hcint.b.xacterr) {
		retval |= handle_hc_xacterr_intr(dwc_otg_hcd, hc, hc_regs, qtd);
	}
	if (hcint.b.bblerr) {
		retval |= handle_hc_babble_intr(dwc_otg_hcd, hc, hc_regs, qtd);
	}
	if (hcint.b.frmovrun) {
		retval |=
		    handle_hc_frmovrun_intr(dwc_otg_hcd, hc, hc_regs, qtd);
	}
	if (hcint.b.datatglerr) {
		retval |=
		    handle_hc_datatglerr_intr(dwc_otg_hcd, hc, hc_regs, qtd);
	}

	return retval;
}