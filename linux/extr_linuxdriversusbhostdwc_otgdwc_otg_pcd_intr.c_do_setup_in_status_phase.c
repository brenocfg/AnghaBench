#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ xfer_count; scalar_t__ total_len; int is_in; int /*<<< orphan*/  dma_addr; scalar_t__ xfer_len; } ;
struct TYPE_11__ {TYPE_5__ dwc_ep; } ;
struct TYPE_10__ {scalar_t__ ep0state; int data_terminated; int /*<<< orphan*/  setup_pkt_dma_handle; int /*<<< orphan*/  backup_buf; TYPE_1__* core_if; TYPE_3__ ep0; } ;
typedef  TYPE_2__ dwc_otg_pcd_t ;
typedef  TYPE_3__ dwc_otg_pcd_ep_t ;
struct TYPE_12__ {scalar_t__ snpsid; } ;
struct TYPE_9__ {scalar_t__ dma_desc_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCD ; 
 int /*<<< orphan*/  DBG_PCDV ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ EP0_IN_STATUS_PHASE ; 
 scalar_t__ EP0_STALL ; 
 TYPE_4__* GET_CORE_IF (TYPE_2__*) ; 
 scalar_t__ OTG_CORE_REV_3_00a ; 
 int /*<<< orphan*/  dwc_otg_ep0_start_transfer (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  phys_to_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void do_setup_in_status_phase(dwc_otg_pcd_t * pcd)
{
	dwc_otg_pcd_ep_t *ep0 = &pcd->ep0;
	if (pcd->ep0state == EP0_STALL) {
		return;
	}

	pcd->ep0state = EP0_IN_STATUS_PHASE;

	/* Prepare for more SETUP Packets */
	DWC_DEBUGPL(DBG_PCD, "EP0 IN ZLP\n");
	if ((GET_CORE_IF(pcd)->snpsid >= OTG_CORE_REV_3_00a)
	    && (pcd->core_if->dma_desc_enable)
	    && (ep0->dwc_ep.xfer_count < ep0->dwc_ep.total_len)) {
		DWC_DEBUGPL(DBG_PCDV,
			    "Data terminated wait next packet in out_desc_addr\n");
		pcd->backup_buf = phys_to_virt(ep0->dwc_ep.dma_addr);
		pcd->data_terminated = 1;
	}
	ep0->dwc_ep.xfer_len = 0;
	ep0->dwc_ep.xfer_count = 0;
	ep0->dwc_ep.is_in = 1;
	ep0->dwc_ep.dma_addr = pcd->setup_pkt_dma_handle;
	dwc_otg_ep0_start_transfer(GET_CORE_IF(pcd), &ep0->dwc_ep);

	/* Prepare for more SETUP Packets */
	//ep0_out_start(GET_CORE_IF(pcd), pcd);
}