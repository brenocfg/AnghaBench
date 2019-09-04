#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ dwc_otg_transaction_type_e ;
struct TYPE_19__ {int /*<<< orphan*/  qtd_list; int /*<<< orphan*/  qh_list_entry; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;
struct TYPE_20__ {int /*<<< orphan*/  periodic_sched_assigned; int /*<<< orphan*/  core_if; } ;
typedef  TYPE_2__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hc_regs_t ;
typedef  scalar_t__ dwc_otg_halt_status_e ;
struct TYPE_21__ {scalar_t__ ep_type; TYPE_1__* qh; } ;
typedef  TYPE_3__ dwc_hc_t ;

/* Variables and functions */
 scalar_t__ DWC_CIRCLEQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_LIST_MOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ DWC_OTG_EP_TYPE_ISOC ; 
 scalar_t__ DWC_OTG_HC_XFER_COMPLETE ; 
 scalar_t__ DWC_OTG_TRANSACTION_ALL ; 
 scalar_t__ DWC_OTG_TRANSACTION_NONE ; 
 scalar_t__ DWC_OTG_TRANSACTION_NON_PERIODIC ; 
 scalar_t__ DWC_OTG_TRANSACTION_PERIODIC ; 
 int /*<<< orphan*/  complete_isoc_xfer_ddma (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  complete_non_isoc_xfer_ddma (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dwc_otg_hc_halt (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  dwc_otg_hcd_qh_add (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  dwc_otg_hcd_qh_remove (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  dwc_otg_hcd_queue_transactions (TYPE_2__*,scalar_t__) ; 
 scalar_t__ dwc_otg_hcd_select_transactions (TYPE_2__*) ; 
 int /*<<< orphan*/  release_channel_ddma (TYPE_2__*,TYPE_1__*) ; 

void dwc_otg_hcd_complete_xfer_ddma(dwc_otg_hcd_t * hcd,
				    dwc_hc_t * hc,
				    dwc_otg_hc_regs_t * hc_regs,
				    dwc_otg_halt_status_e halt_status)
{
	uint8_t continue_isoc_xfer = 0;
	dwc_otg_transaction_type_e tr_type;
	dwc_otg_qh_t *qh = hc->qh;

	if (hc->ep_type == DWC_OTG_EP_TYPE_ISOC) {

		complete_isoc_xfer_ddma(hcd, hc, hc_regs, halt_status);

		/* Release the channel if halted or session completed */
		if (halt_status != DWC_OTG_HC_XFER_COMPLETE ||
		    DWC_CIRCLEQ_EMPTY(&qh->qtd_list)) {

			/* Halt the channel if session completed */
			if (halt_status == DWC_OTG_HC_XFER_COMPLETE) {
				dwc_otg_hc_halt(hcd->core_if, hc, halt_status);
			}

			release_channel_ddma(hcd, qh);
			dwc_otg_hcd_qh_remove(hcd, qh);
		} else {
			/* Keep in assigned schedule to continue transfer */
			DWC_LIST_MOVE_HEAD(&hcd->periodic_sched_assigned,
					   &qh->qh_list_entry);
			continue_isoc_xfer = 1;

		}
		/** @todo Consider the case when period exceeds FrameList size.
		 *  Frame Rollover interrupt should be used.
		 */
	} else {
		/* Scan descriptor list to complete the URB(s), then release the channel */
		complete_non_isoc_xfer_ddma(hcd, hc, hc_regs, halt_status);

		release_channel_ddma(hcd, qh);
		dwc_otg_hcd_qh_remove(hcd, qh);

		if (!DWC_CIRCLEQ_EMPTY(&qh->qtd_list)) {
			/* Add back to inactive non-periodic schedule on normal completion */
			dwc_otg_hcd_qh_add(hcd, qh);
		}

	}
	tr_type = dwc_otg_hcd_select_transactions(hcd);
	if (tr_type != DWC_OTG_TRANSACTION_NONE || continue_isoc_xfer) {
		if (continue_isoc_xfer) {
			if (tr_type == DWC_OTG_TRANSACTION_NONE) {
				tr_type = DWC_OTG_TRANSACTION_PERIODIC;
			} else if (tr_type == DWC_OTG_TRANSACTION_NON_PERIODIC) {
				tr_type = DWC_OTG_TRANSACTION_ALL;
			}
		}
		dwc_otg_hcd_queue_transactions(hcd, tr_type);
	}
}