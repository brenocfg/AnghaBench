#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_16__ {int /*<<< orphan*/  ntd; TYPE_3__* channel; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;
struct TYPE_17__ {int /*<<< orphan*/  core_if; } ;
typedef  TYPE_2__ dwc_otg_hcd_t ;
struct TYPE_18__ {int ep_type; int /*<<< orphan*/  ntd; int /*<<< orphan*/  xfer_started; } ;
typedef  TYPE_3__ dwc_hc_t ;

/* Variables and functions */
#define  DWC_OTG_EP_TYPE_BULK 131 
#define  DWC_OTG_EP_TYPE_CONTROL 130 
#define  DWC_OTG_EP_TYPE_INTR 129 
#define  DWC_OTG_EP_TYPE_ISOC 128 
 int /*<<< orphan*/  dwc_otg_hc_start_transfer_ddma (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  init_isoc_dma_desc (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_non_isoc_dma_desc (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  max_desc_num (TYPE_1__*) ; 
 int /*<<< orphan*/  recalc_initial_desc_idx (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  update_frame_list (TYPE_2__*,TYPE_1__*,int) ; 

void dwc_otg_hcd_start_xfer_ddma(dwc_otg_hcd_t * hcd, dwc_otg_qh_t * qh)
{
	/* Channel is already assigned */
	dwc_hc_t *hc = qh->channel;
	uint8_t skip_frames = 0;

	switch (hc->ep_type) {
	case DWC_OTG_EP_TYPE_CONTROL:
	case DWC_OTG_EP_TYPE_BULK:
		init_non_isoc_dma_desc(hcd, qh);

		dwc_otg_hc_start_transfer_ddma(hcd->core_if, hc);
		break;
	case DWC_OTG_EP_TYPE_INTR:
		init_non_isoc_dma_desc(hcd, qh);

		update_frame_list(hcd, qh, 1);

		dwc_otg_hc_start_transfer_ddma(hcd->core_if, hc);
		break;
	case DWC_OTG_EP_TYPE_ISOC:

		if (!qh->ntd)
			skip_frames = recalc_initial_desc_idx(hcd, qh);

		init_isoc_dma_desc(hcd, qh, skip_frames);

		if (!hc->xfer_started) {

			update_frame_list(hcd, qh, 1);

			/*
			 * Always set to max, instead of actual size.
			 * Otherwise ntd will be changed with
			 * channel being enabled. Not recommended.
			 *
			 */
			hc->ntd = max_desc_num(qh);
			/* Enable channel only once for ISOC */
			dwc_otg_hc_start_transfer_ddma(hcd->core_if, hc);
		}

		break;
	default:

		break;
	}
}