#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  start_xfer_tasklet; } ;
typedef  TYPE_1__ dwc_otg_pcd_t ;
struct TYPE_11__ {scalar_t__ stall_clear_flag; } ;
struct TYPE_10__ {int queue_sof; scalar_t__ stopped; TYPE_5__ dwc_ep; } ;
typedef  TYPE_2__ dwc_otg_pcd_ep_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_TASK_SCHEDULE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_CORE_IF (TYPE_1__*) ; 
 int /*<<< orphan*/  do_setup_in_status_phase (TYPE_1__*) ; 
 int /*<<< orphan*/  dwc_otg_ep_activate (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  dwc_otg_ep_clear_stall (int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static inline void pcd_clear_halt(dwc_otg_pcd_t * pcd, dwc_otg_pcd_ep_t * ep)
{
	if (ep->dwc_ep.stall_clear_flag == 0)
		dwc_otg_ep_clear_stall(GET_CORE_IF(pcd), &ep->dwc_ep);

	/* Reactive the EP */
	dwc_otg_ep_activate(GET_CORE_IF(pcd), &ep->dwc_ep);
	if (ep->stopped) {
		ep->stopped = 0;
		/* If there is a request in the EP queue start it */

		/** @todo FIXME: this causes an EP mismatch in DMA mode.
		 * epmismatch not yet implemented. */

		/*
		 * Above fixme is solved by implmenting a tasklet to call the
		 * start_next_request(), outside of interrupt context at some
		 * time after the current time, after a clear-halt setup packet.
		 * Still need to implement ep mismatch in the future if a gadget
		 * ever uses more than one endpoint at once
		 */
		ep->queue_sof = 1;
		DWC_TASK_SCHEDULE(pcd->start_xfer_tasklet);
	}
	/* Start Control Status Phase */
	do_setup_in_status_phase(pcd);
}