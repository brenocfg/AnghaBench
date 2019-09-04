#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_19__ {TYPE_9__* core_if; TYPE_2__* fiq_state; } ;
typedef  TYPE_3__ dwc_otg_hcd_t ;
struct TYPE_20__ {scalar_t__ ep_type; size_t hc_num; scalar_t__ data_pid_start; int max_packet; int /*<<< orphan*/  xfer_started; int /*<<< orphan*/  ep_is_in; scalar_t__ do_ping; int /*<<< orphan*/  halt_status; scalar_t__ halt_on_queue; scalar_t__ halt_pending; TYPE_8__* qh; scalar_t__ error_state; } ;
typedef  TYPE_4__ dwc_hc_t ;
struct TYPE_22__ {scalar_t__ dma_desc_enable; scalar_t__ dma_enable; } ;
struct TYPE_21__ {scalar_t__ ping_state; int /*<<< orphan*/  qtd_list; } ;
struct TYPE_18__ {TYPE_1__* channel; } ;
struct TYPE_17__ {int /*<<< orphan*/  fsm; int /*<<< orphan*/  nr_errors; } ;
struct TYPE_16__ {int /*<<< orphan*/  error_count; } ;

/* Variables and functions */
 TYPE_15__* DWC_CIRCLEQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ DWC_OTG_EP_TYPE_ISOC ; 
 scalar_t__ DWC_OTG_HC_PID_SETUP ; 
 int /*<<< orphan*/  FIQ_PASSTHROUGH_ERRORSTATE ; 
 int dwc_otg_hc_continue_transfer (TYPE_9__*,TYPE_4__*) ; 
 int /*<<< orphan*/  dwc_otg_hc_halt (TYPE_9__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_hc_start_transfer (TYPE_9__*,TYPE_4__*) ; 
 int /*<<< orphan*/  dwc_otg_hcd_start_xfer_ddma (TYPE_3__*,TYPE_8__*) ; 
 scalar_t__ fiq_fsm_enable ; 

__attribute__((used)) static int queue_transaction(dwc_otg_hcd_t * hcd,
			     dwc_hc_t * hc, uint16_t fifo_dwords_avail)
{
	int retval;

	if (hcd->core_if->dma_enable) {
		if (hcd->core_if->dma_desc_enable) {
			if (!hc->xfer_started
			    || (hc->ep_type == DWC_OTG_EP_TYPE_ISOC)) {
				dwc_otg_hcd_start_xfer_ddma(hcd, hc->qh);
				hc->qh->ping_state = 0;
			}
		} else if (!hc->xfer_started) {
			if (fiq_fsm_enable && hc->error_state) {
				hcd->fiq_state->channel[hc->hc_num].nr_errors =
					DWC_CIRCLEQ_FIRST(&hc->qh->qtd_list)->error_count;
				hcd->fiq_state->channel[hc->hc_num].fsm =
					FIQ_PASSTHROUGH_ERRORSTATE;
			}
			dwc_otg_hc_start_transfer(hcd->core_if, hc);
			hc->qh->ping_state = 0;
		}
		retval = 0;
	} else if (hc->halt_pending) {
		/* Don't queue a request if the channel has been halted. */
		retval = 0;
	} else if (hc->halt_on_queue) {
		dwc_otg_hc_halt(hcd->core_if, hc, hc->halt_status);
		retval = 0;
	} else if (hc->do_ping) {
		if (!hc->xfer_started) {
			dwc_otg_hc_start_transfer(hcd->core_if, hc);
		}
		retval = 0;
	} else if (!hc->ep_is_in || hc->data_pid_start == DWC_OTG_HC_PID_SETUP) {
		if ((fifo_dwords_avail * 4) >= hc->max_packet) {
			if (!hc->xfer_started) {
				dwc_otg_hc_start_transfer(hcd->core_if, hc);
				retval = 1;
			} else {
				retval =
				    dwc_otg_hc_continue_transfer(hcd->core_if,
								 hc);
			}
		} else {
			retval = -1;
		}
	} else {
		if (!hc->xfer_started) {
			dwc_otg_hc_start_transfer(hcd->core_if, hc);
			retval = 1;
		} else {
			retval = dwc_otg_hc_continue_transfer(hcd->core_if, hc);
		}
	}

	return retval;
}