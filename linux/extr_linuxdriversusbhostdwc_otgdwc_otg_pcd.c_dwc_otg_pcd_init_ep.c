#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
struct TYPE_4__ {scalar_t__ dma_desc_addr; scalar_t__ desc_addr; scalar_t__ total_len; scalar_t__ sent_zlp; scalar_t__ xfer_count; scalar_t__ xfer_len; scalar_t__ xfer_buff; scalar_t__ start_xfer_buff; scalar_t__ dma_addr; int /*<<< orphan*/  maxpacket; int /*<<< orphan*/  type; scalar_t__ tx_fifo_num; scalar_t__ active; void* num; void* is_in; } ;
struct TYPE_5__ {int stopped; int /*<<< orphan*/  queue; TYPE_1__ dwc_ep; scalar_t__ queue_sof; int /*<<< orphan*/ * pcd; scalar_t__ desc; } ;
typedef  TYPE_2__ dwc_otg_pcd_ep_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_CIRCLEQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_OTG_EP_TYPE_CONTROL ; 
 int /*<<< orphan*/  MAX_PACKET_SIZE ; 

__attribute__((used)) static void dwc_otg_pcd_init_ep(dwc_otg_pcd_t * pcd, dwc_otg_pcd_ep_t * pcd_ep,
				uint32_t is_in, uint32_t ep_num)
{
	/* Init EP structure */
	pcd_ep->desc = 0;
	pcd_ep->pcd = pcd;
	pcd_ep->stopped = 1;
	pcd_ep->queue_sof = 0;

	/* Init DWC ep structure */
	pcd_ep->dwc_ep.is_in = is_in;
	pcd_ep->dwc_ep.num = ep_num;
	pcd_ep->dwc_ep.active = 0;
	pcd_ep->dwc_ep.tx_fifo_num = 0;
	/* Control until ep is actvated */
	pcd_ep->dwc_ep.type = DWC_OTG_EP_TYPE_CONTROL;
	pcd_ep->dwc_ep.maxpacket = MAX_PACKET_SIZE;
	pcd_ep->dwc_ep.dma_addr = 0;
	pcd_ep->dwc_ep.start_xfer_buff = 0;
	pcd_ep->dwc_ep.xfer_buff = 0;
	pcd_ep->dwc_ep.xfer_len = 0;
	pcd_ep->dwc_ep.xfer_count = 0;
	pcd_ep->dwc_ep.sent_zlp = 0;
	pcd_ep->dwc_ep.total_len = 0;
	pcd_ep->dwc_ep.desc_addr = 0;
	pcd_ep->dwc_ep.dma_desc_addr = 0;
	DWC_CIRCLEQ_INIT(&pcd_ep->queue);
}