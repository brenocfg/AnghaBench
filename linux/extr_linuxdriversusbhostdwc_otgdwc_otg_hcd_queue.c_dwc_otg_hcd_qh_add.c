#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int sofintr; } ;
struct TYPE_17__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_5__ gintmsk_data_t ;
struct TYPE_18__ {int /*<<< orphan*/  qh_list_entry; } ;
typedef  TYPE_6__ dwc_otg_qh_t ;
struct TYPE_19__ {int /*<<< orphan*/  periodic_qh_count; TYPE_4__* core_if; TYPE_2__* fiq_state; int /*<<< orphan*/  non_periodic_sched_inactive; } ;
typedef  TYPE_7__ dwc_otg_hcd_t ;
struct TYPE_16__ {TYPE_3__* core_global_regs; } ;
struct TYPE_15__ {int /*<<< orphan*/  gintmsk; } ;
struct TYPE_14__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_LIST_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dwc_qh_is_non_per (TYPE_6__*) ; 
 scalar_t__ fiq_enable ; 
 int /*<<< orphan*/  fiq_fsm_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fiq_fsm_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_fiq_disable () ; 
 int /*<<< orphan*/  local_fiq_enable () ; 
 int schedule_periodic (TYPE_7__*,TYPE_6__*) ; 

int dwc_otg_hcd_qh_add(dwc_otg_hcd_t * hcd, dwc_otg_qh_t * qh)
{
	int status = 0;
	gintmsk_data_t intr_mask = {.d32 = 0 };

	if (!DWC_LIST_EMPTY(&qh->qh_list_entry)) {
		/* QH already in a schedule. */
		return status;
	}

	/* Add the new QH to the appropriate schedule */
	if (dwc_qh_is_non_per(qh)) {
		/* Always start in the inactive schedule. */
		DWC_LIST_INSERT_TAIL(&hcd->non_periodic_sched_inactive,
				     &qh->qh_list_entry);
		//hcd->fiq_state->kick_np_queues = 1;
	} else {
		status = schedule_periodic(hcd, qh);
		if ( !hcd->periodic_qh_count ) {
			intr_mask.b.sofintr = 1;
			if (fiq_enable) {
				local_fiq_disable();
				fiq_fsm_spin_lock(&hcd->fiq_state->lock);
				DWC_MODIFY_REG32(&hcd->core_if->core_global_regs->gintmsk, intr_mask.d32, intr_mask.d32);
				fiq_fsm_spin_unlock(&hcd->fiq_state->lock);
				local_fiq_enable();
			} else {
				DWC_MODIFY_REG32(&hcd->core_if->core_global_regs->gintmsk, intr_mask.d32, intr_mask.d32);
			}
		}
		hcd->periodic_qh_count++;
	}

	return status;
}