#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
struct TYPE_16__ {int nptxfempty; int ptxfempty; } ;
struct TYPE_18__ {int /*<<< orphan*/  d32; TYPE_2__ b; } ;
typedef  TYPE_4__ gintmsk_data_t ;
typedef  int /*<<< orphan*/  dwc_otg_qtd_t ;
struct TYPE_19__ {TYPE_3__* fiq_state; int /*<<< orphan*/  periodic_sched_assigned; TYPE_12__* core_if; } ;
typedef  TYPE_5__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_halt_status_e ;
struct TYPE_20__ {int /*<<< orphan*/  gintmsk; } ;
typedef  TYPE_6__ dwc_otg_core_global_regs_t ;
struct TYPE_21__ {scalar_t__ ep_type; TYPE_1__* qh; scalar_t__ halt_on_queue; } ;
typedef  TYPE_7__ dwc_hc_t ;
struct TYPE_17__ {int /*<<< orphan*/  lock; } ;
struct TYPE_15__ {int /*<<< orphan*/  qh_list_entry; } ;
struct TYPE_14__ {TYPE_6__* core_global_regs; scalar_t__ dma_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_LIST_MOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DWC_OTG_EP_TYPE_BULK ; 
 scalar_t__ DWC_OTG_EP_TYPE_CONTROL ; 
 int /*<<< orphan*/  dwc_otg_hc_halt (TYPE_12__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ fiq_enable ; 
 int /*<<< orphan*/  fiq_fsm_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fiq_fsm_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_fiq_disable () ; 
 int /*<<< orphan*/  local_fiq_enable () ; 
 int /*<<< orphan*/  release_channel (TYPE_5__*,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void halt_channel(dwc_otg_hcd_t * hcd,
			 dwc_hc_t * hc,
			 dwc_otg_qtd_t * qtd, dwc_otg_halt_status_e halt_status)
{
	if (hcd->core_if->dma_enable) {
		release_channel(hcd, hc, qtd, halt_status);
		return;
	}

	/* Slave mode processing... */
	dwc_otg_hc_halt(hcd->core_if, hc, halt_status);

	if (hc->halt_on_queue) {
		gintmsk_data_t gintmsk = {.d32 = 0 };
		dwc_otg_core_global_regs_t *global_regs;
		global_regs = hcd->core_if->core_global_regs;

		if (hc->ep_type == DWC_OTG_EP_TYPE_CONTROL ||
		    hc->ep_type == DWC_OTG_EP_TYPE_BULK) {
			/*
			 * Make sure the Non-periodic Tx FIFO empty interrupt
			 * is enabled so that the non-periodic schedule will
			 * be processed.
			 */
			gintmsk.b.nptxfempty = 1;
			if (fiq_enable) {
				local_fiq_disable();
				fiq_fsm_spin_lock(&hcd->fiq_state->lock);
				DWC_MODIFY_REG32(&global_regs->gintmsk, 0, gintmsk.d32);
				fiq_fsm_spin_unlock(&hcd->fiq_state->lock);
				local_fiq_enable();
			} else {
				DWC_MODIFY_REG32(&global_regs->gintmsk, 0, gintmsk.d32);
			}
		} else {
			/*
			 * Move the QH from the periodic queued schedule to
			 * the periodic assigned schedule. This allows the
			 * halt to be queued when the periodic schedule is
			 * processed.
			 */
			DWC_LIST_MOVE_HEAD(&hcd->periodic_sched_assigned,
					   &hc->qh->qh_list_entry);

			/*
			 * Make sure the Periodic Tx FIFO Empty interrupt is
			 * enabled so that the periodic schedule will be
			 * processed.
			 */
			gintmsk.b.ptxfempty = 1;
			if (fiq_enable) {
				local_fiq_disable();
				fiq_fsm_spin_lock(&hcd->fiq_state->lock);
				DWC_MODIFY_REG32(&global_regs->gintmsk, 0, gintmsk.d32);
				fiq_fsm_spin_unlock(&hcd->fiq_state->lock);
				local_fiq_enable();
			} else {
				DWC_MODIFY_REG32(&global_regs->gintmsk, 0, gintmsk.d32);
			}
		}
	}
}