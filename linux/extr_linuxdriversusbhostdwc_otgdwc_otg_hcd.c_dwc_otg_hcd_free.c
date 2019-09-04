#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_11__ {struct TYPE_11__* fiq_state; scalar_t__ dummy_send_dma; struct TYPE_11__* dummy_send; int /*<<< orphan*/  completion_tasklet; int /*<<< orphan*/  reset_tasklet; int /*<<< orphan*/  conn_timer; TYPE_1__* core_if; int /*<<< orphan*/  lock; struct TYPE_11__* status_buf; scalar_t__ status_buf_dma; struct TYPE_11__** hc_ptr_array; int /*<<< orphan*/  periodic_sched_queued; int /*<<< orphan*/  periodic_sched_assigned; int /*<<< orphan*/  periodic_sched_ready; int /*<<< orphan*/  periodic_sched_inactive; int /*<<< orphan*/  non_periodic_sched_active; int /*<<< orphan*/  non_periodic_sched_inactive; } ;
typedef  TYPE_2__ dwc_otg_hcd_t ;
typedef  TYPE_2__ dwc_hc_t ;
struct TYPE_10__ {int /*<<< orphan*/ * lock; scalar_t__ dma_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCD ; 
 int /*<<< orphan*/  DBG_HCDV ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DWC_DMA_FREE (struct device*,int,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  DWC_FREE (TYPE_2__*) ; 
 int DWC_OTG_HCD_STATUS_BUF_SIZE ; 
 int /*<<< orphan*/  DWC_SPINLOCK_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_TASK_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_TIMER_FREE (int /*<<< orphan*/ ) ; 
 int MAX_EPS_CHANNELS ; 
 int /*<<< orphan*/  del_timers (TYPE_2__*) ; 
 struct device* dwc_otg_hcd_to_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  qh_list_free (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dwc_otg_hcd_free(dwc_otg_hcd_t * dwc_otg_hcd)
{
	struct device *dev = dwc_otg_hcd_to_dev(dwc_otg_hcd);
	int i;

	DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD FREE\n");

	del_timers(dwc_otg_hcd);

	/* Free memory for QH/QTD lists */
	qh_list_free(dwc_otg_hcd, &dwc_otg_hcd->non_periodic_sched_inactive);
	qh_list_free(dwc_otg_hcd, &dwc_otg_hcd->non_periodic_sched_active);
	qh_list_free(dwc_otg_hcd, &dwc_otg_hcd->periodic_sched_inactive);
	qh_list_free(dwc_otg_hcd, &dwc_otg_hcd->periodic_sched_ready);
	qh_list_free(dwc_otg_hcd, &dwc_otg_hcd->periodic_sched_assigned);
	qh_list_free(dwc_otg_hcd, &dwc_otg_hcd->periodic_sched_queued);

	/* Free memory for the host channels. */
	for (i = 0; i < MAX_EPS_CHANNELS; i++) {
		dwc_hc_t *hc = dwc_otg_hcd->hc_ptr_array[i];

#ifdef DEBUG
		if (dwc_otg_hcd->core_if->hc_xfer_timer[i]) {
			DWC_TIMER_FREE(dwc_otg_hcd->core_if->hc_xfer_timer[i]);
		}
#endif
		if (hc != NULL) {
			DWC_DEBUGPL(DBG_HCDV, "HCD Free channel #%i, hc=%p\n",
				    i, hc);
			DWC_FREE(hc);
		}
	}

	if (dwc_otg_hcd->core_if->dma_enable) {
		if (dwc_otg_hcd->status_buf_dma) {
			DWC_DMA_FREE(dev, DWC_OTG_HCD_STATUS_BUF_SIZE,
				     dwc_otg_hcd->status_buf,
				     dwc_otg_hcd->status_buf_dma);
		}
	} else if (dwc_otg_hcd->status_buf != NULL) {
		DWC_FREE(dwc_otg_hcd->status_buf);
	}
	DWC_SPINLOCK_FREE(dwc_otg_hcd->lock);
	/* Set core_if's lock pointer to NULL */
	dwc_otg_hcd->core_if->lock = NULL;

	DWC_TIMER_FREE(dwc_otg_hcd->conn_timer);
	DWC_TASK_FREE(dwc_otg_hcd->reset_tasklet);
	DWC_TASK_FREE(dwc_otg_hcd->completion_tasklet);
	DWC_DMA_FREE(dev, 16, dwc_otg_hcd->fiq_state->dummy_send,
		     dwc_otg_hcd->fiq_state->dummy_send_dma);
	DWC_FREE(dwc_otg_hcd->fiq_state);

#ifdef DWC_DEV_SRPCAP
	if (dwc_otg_hcd->core_if->power_down == 2 &&
	    dwc_otg_hcd->core_if->pwron_timer) {
		DWC_TIMER_FREE(dwc_otg_hcd->core_if->pwron_timer);
	}
#endif
	DWC_FREE(dwc_otg_hcd);
}