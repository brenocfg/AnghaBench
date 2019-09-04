#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ desc_list; scalar_t__ ntd; TYPE_3__* channel; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;
typedef  int /*<<< orphan*/  dwc_otg_host_dma_desc_t ;
struct TYPE_13__ {int /*<<< orphan*/  free_hc_list; int /*<<< orphan*/  core_if; int /*<<< orphan*/  available_host_channels; int /*<<< orphan*/  non_periodic_channels; } ;
typedef  TYPE_2__ dwc_otg_hcd_t ;
struct TYPE_14__ {int /*<<< orphan*/ * qh; } ;
typedef  TYPE_3__ dwc_hc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_CIRCLEQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_memset (scalar_t__,int,int) ; 
 int /*<<< orphan*/  dwc_otg_hc_cleanup (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ dwc_qh_is_non_per (TYPE_1__*) ; 
 int /*<<< orphan*/  hc_list_entry ; 
 int max_desc_num (TYPE_1__*) ; 
 int /*<<< orphan*/  microframe_schedule ; 
 int /*<<< orphan*/  update_frame_list (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_channel_ddma(dwc_otg_hcd_t * hcd, dwc_otg_qh_t * qh)
{
	dwc_hc_t *hc = qh->channel;
	if (dwc_qh_is_non_per(qh)) {
		if (!microframe_schedule)
			hcd->non_periodic_channels--;
		else
			hcd->available_host_channels++;
	} else
		update_frame_list(hcd, qh, 0);

	/*
	 * The condition is added to prevent double cleanup try in case of device
	 * disconnect. See channel cleanup in dwc_otg_hcd_disconnect_cb().
	 */
	if (hc->qh) {
		dwc_otg_hc_cleanup(hcd->core_if, hc);
		DWC_CIRCLEQ_INSERT_TAIL(&hcd->free_hc_list, hc, hc_list_entry);
		hc->qh = NULL;
	}

	qh->channel = NULL;
	qh->ntd = 0;

	if (qh->desc_list) {
		dwc_memset(qh->desc_list, 0x00,
			   sizeof(dwc_otg_host_dma_desc_t) * max_desc_num(qh));
	}
}