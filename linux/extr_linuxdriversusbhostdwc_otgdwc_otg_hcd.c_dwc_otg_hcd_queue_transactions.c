#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int nptxfempty; } ;
struct TYPE_14__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_5__ gintmsk_data_t ;
typedef  scalar_t__ dwc_otg_transaction_type_e ;
struct TYPE_15__ {TYPE_4__* core_if; TYPE_2__* fiq_state; int /*<<< orphan*/  non_periodic_sched_active; int /*<<< orphan*/  periodic_sched_assigned; } ;
typedef  TYPE_6__ dwc_otg_hcd_t ;
struct TYPE_13__ {TYPE_3__* core_global_regs; } ;
struct TYPE_12__ {int /*<<< orphan*/  gintmsk; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DWC_OTG_TRANSACTION_ALL ; 
 scalar_t__ DWC_OTG_TRANSACTION_NON_PERIODIC ; 
 scalar_t__ DWC_OTG_TRANSACTION_PERIODIC ; 
 scalar_t__ fiq_enable ; 
 int /*<<< orphan*/  fiq_fsm_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fiq_fsm_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_fiq_disable () ; 
 int /*<<< orphan*/  local_fiq_enable () ; 
 int /*<<< orphan*/  process_non_periodic_channels (TYPE_6__*) ; 
 int /*<<< orphan*/  process_periodic_channels (TYPE_6__*) ; 

void dwc_otg_hcd_queue_transactions(dwc_otg_hcd_t * hcd,
				    dwc_otg_transaction_type_e tr_type)
{
#ifdef DEBUG_SOF
	DWC_DEBUGPL(DBG_HCD, "Queue Transactions\n");
#endif
	/* Process host channels associated with periodic transfers. */
	if ((tr_type == DWC_OTG_TRANSACTION_PERIODIC ||
	     tr_type == DWC_OTG_TRANSACTION_ALL) &&
	    !DWC_LIST_EMPTY(&hcd->periodic_sched_assigned)) {

		process_periodic_channels(hcd);
	}

	/* Process host channels associated with non-periodic transfers. */
	if (tr_type == DWC_OTG_TRANSACTION_NON_PERIODIC ||
	    tr_type == DWC_OTG_TRANSACTION_ALL) {
		if (!DWC_LIST_EMPTY(&hcd->non_periodic_sched_active)) {
			process_non_periodic_channels(hcd);
		} else {
			/*
			 * Ensure NP Tx FIFO empty interrupt is disabled when
			 * there are no non-periodic transfers to process.
			 */
			gintmsk_data_t gintmsk = {.d32 = 0 };
			gintmsk.b.nptxfempty = 1;

			if (fiq_enable) {
				local_fiq_disable();
				fiq_fsm_spin_lock(&hcd->fiq_state->lock);
				DWC_MODIFY_REG32(&hcd->core_if->core_global_regs->gintmsk, gintmsk.d32, 0);
				fiq_fsm_spin_unlock(&hcd->fiq_state->lock);
				local_fiq_enable();
			} else {
				DWC_MODIFY_REG32(&hcd->core_if->core_global_regs->gintmsk, gintmsk.d32, 0);
			}
		}
	}
}