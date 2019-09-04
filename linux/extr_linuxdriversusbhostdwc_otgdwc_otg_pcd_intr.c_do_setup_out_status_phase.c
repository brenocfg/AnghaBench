#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  dma_addr; scalar_t__ is_in; scalar_t__ xfer_count; scalar_t__ xfer_len; } ;
struct TYPE_11__ {TYPE_6__ dwc_ep; } ;
struct TYPE_10__ {scalar_t__ ep0state; int /*<<< orphan*/  setup_pkt_dma_handle; TYPE_2__ ep0; } ;
typedef  TYPE_1__ dwc_otg_pcd_t ;
typedef  TYPE_2__ dwc_otg_pcd_ep_t ;
struct TYPE_12__ {scalar_t__ dma_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ EP0_OUT_STATUS_PHASE ; 
 scalar_t__ EP0_STALL ; 
 TYPE_3__* GET_CORE_IF (TYPE_1__*) ; 
 int /*<<< orphan*/  dwc_otg_ep0_start_transfer (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ep0_out_start (TYPE_3__*,TYPE_1__*) ; 

__attribute__((used)) static inline void do_setup_out_status_phase(dwc_otg_pcd_t * pcd)
{
	dwc_otg_pcd_ep_t *ep0 = &pcd->ep0;
	if (pcd->ep0state == EP0_STALL) {
		DWC_DEBUGPL(DBG_PCD, "EP0 STALLED\n");
		return;
	}
	pcd->ep0state = EP0_OUT_STATUS_PHASE;

	DWC_DEBUGPL(DBG_PCD, "EP0 OUT ZLP\n");
	ep0->dwc_ep.xfer_len = 0;
	ep0->dwc_ep.xfer_count = 0;
	ep0->dwc_ep.is_in = 0;
	ep0->dwc_ep.dma_addr = pcd->setup_pkt_dma_handle;
	dwc_otg_ep0_start_transfer(GET_CORE_IF(pcd), &ep0->dwc_ep);

	/* Prepare for more SETUP Packets */
	if (GET_CORE_IF(pcd)->dma_enable == 0) {
		ep0_out_start(GET_CORE_IF(pcd), pcd);
	}
}