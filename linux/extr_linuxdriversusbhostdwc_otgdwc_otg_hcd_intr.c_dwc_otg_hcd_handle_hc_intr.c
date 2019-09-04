#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_15__ {int chint; } ;
struct TYPE_16__ {TYPE_5__ b2; int /*<<< orphan*/  d32; } ;
typedef  TYPE_6__ haint_data_t ;
struct TYPE_17__ {TYPE_8__* core_if; TYPE_3__* fiq_state; } ;
typedef  TYPE_7__ dwc_otg_hcd_t ;
struct TYPE_18__ {TYPE_4__* core_params; } ;
struct TYPE_14__ {int host_channels; } ;
struct TYPE_11__ {int chint; } ;
struct TYPE_12__ {TYPE_1__ b2; } ;
struct TYPE_13__ {int /*<<< orphan*/  lock; TYPE_2__ haintmsk_saved; } ;

/* Variables and functions */
 int dwc_otg_hcd_handle_hc_n_intr (TYPE_7__*,int) ; 
 int /*<<< orphan*/  dwc_otg_read_host_all_channels_intr (TYPE_8__*) ; 
 scalar_t__ fiq_fsm_enable ; 
 int /*<<< orphan*/  fiq_fsm_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fiq_fsm_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_fiq_disable () ; 
 int /*<<< orphan*/  local_fiq_enable () ; 

int32_t dwc_otg_hcd_handle_hc_intr(dwc_otg_hcd_t * dwc_otg_hcd)
{
	int i;
	int retval = 0;
	haint_data_t haint = { .d32 = 0 } ;

	/* Clear appropriate bits in HCINTn to clear the interrupt bit in
	 * GINTSTS */

	if (!fiq_fsm_enable)
		haint.d32 = dwc_otg_read_host_all_channels_intr(dwc_otg_hcd->core_if);

	// Overwrite with saved interrupts from fiq handler
	if(fiq_fsm_enable)
	{
		/* check the mask? */
		local_fiq_disable();
		fiq_fsm_spin_lock(&dwc_otg_hcd->fiq_state->lock);
		haint.b2.chint |= ~(dwc_otg_hcd->fiq_state->haintmsk_saved.b2.chint);
		dwc_otg_hcd->fiq_state->haintmsk_saved.b2.chint = ~0;
		fiq_fsm_spin_unlock(&dwc_otg_hcd->fiq_state->lock);
		local_fiq_enable();
	}

	for (i = 0; i < dwc_otg_hcd->core_if->core_params->host_channels; i++) {
		if (haint.b2.chint & (1 << i)) {
			retval |= dwc_otg_hcd_handle_hc_n_intr(dwc_otg_hcd, i);
		}
	}

	return retval;
}