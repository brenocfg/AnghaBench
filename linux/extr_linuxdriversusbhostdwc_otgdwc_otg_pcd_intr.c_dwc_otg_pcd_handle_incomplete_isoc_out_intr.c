#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_17__ ;
typedef  struct TYPE_27__   TYPE_16__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_36__ {int incomplisoout; int /*<<< orphan*/  goutnakeff; } ;
struct TYPE_21__ {void* d32; TYPE_8__ b; } ;
typedef  TYPE_10__ gintsts_data_t ;
struct TYPE_35__ {int goutnakeff; int incomplisoout; } ;
struct TYPE_22__ {TYPE_7__ b; void* d32; } ;
typedef  TYPE_11__ gintmsk_data_t ;
struct TYPE_23__ {TYPE_1__* out_ep; } ;
typedef  TYPE_12__ dwc_otg_pcd_t ;
struct TYPE_24__ {int frame_num; TYPE_9__* core_global_regs; TYPE_6__* dev_if; } ;
typedef  TYPE_13__ dwc_otg_core_if_t ;
struct TYPE_25__ {size_t num; } ;
typedef  TYPE_14__ dwc_ep_t ;
struct TYPE_26__ {void* d32; } ;
typedef  TYPE_15__ deptsiz_data_t ;
struct TYPE_32__ {int dpid; int epdis; int snak; scalar_t__ epena; } ;
struct TYPE_27__ {void* d32; TYPE_4__ b; } ;
typedef  TYPE_16__ depctl_data_t ;
struct TYPE_30__ {int sgoutnak; } ;
struct TYPE_28__ {void* d32; TYPE_2__ b; } ;
typedef  TYPE_17__ dctl_data_t ;
struct TYPE_37__ {int /*<<< orphan*/  gintsts; int /*<<< orphan*/  gintmsk; } ;
struct TYPE_34__ {int num_out_eps; TYPE_5__** out_ep_regs; TYPE_3__* dev_global_regs; TYPE_14__* isoc_ep; } ;
struct TYPE_33__ {int /*<<< orphan*/  doepctl; int /*<<< orphan*/  doeptsiz; } ;
struct TYPE_31__ {int /*<<< orphan*/  dctl; } ;
struct TYPE_29__ {TYPE_14__ dwc_ep; } ;

/* Variables and functions */
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,void*) ; 
 TYPE_13__* GET_CORE_IF (TYPE_12__*) ; 

int32_t dwc_otg_pcd_handle_incomplete_isoc_out_intr(dwc_otg_pcd_t * pcd)
{

	gintsts_data_t gintsts;

#ifdef DWC_EN_ISOC
	dwc_otg_dev_if_t *dev_if;
	deptsiz_data_t deptsiz = {.d32 = 0 };
	depctl_data_t depctl = {.d32 = 0 };
	dsts_data_t dsts = {.d32 = 0 };
	dwc_ep_t *dwc_ep;
	int i;

	dev_if = GET_CORE_IF(pcd)->dev_if;

	for (i = 1; i <= dev_if->num_out_eps; ++i) {
		dwc_ep = &pcd->in_ep[i].dwc_ep;
		if (pcd->out_ep[i].dwc_ep.active &&
		    pcd->out_ep[i].dwc_ep.type == DWC_OTG_EP_TYPE_ISOC) {
			deptsiz.d32 =
			    DWC_READ_REG32(&dev_if->out_ep_regs[i]->doeptsiz);
			depctl.d32 =
			    DWC_READ_REG32(&dev_if->out_ep_regs[i]->doepctl);

			if (depctl.b.epdis && deptsiz.d32) {
				set_current_pkt_info(GET_CORE_IF(pcd),
						     &pcd->out_ep[i].dwc_ep);
				if (dwc_ep->cur_pkt >= dwc_ep->pkt_cnt) {
					dwc_ep->cur_pkt = 0;
					dwc_ep->proc_buf_num =
					    (dwc_ep->proc_buf_num ^ 1) & 0x1;

					if (dwc_ep->proc_buf_num) {
						dwc_ep->cur_pkt_addr =
						    dwc_ep->xfer_buff1;
						dwc_ep->cur_pkt_dma_addr =
						    dwc_ep->dma_addr1;
					} else {
						dwc_ep->cur_pkt_addr =
						    dwc_ep->xfer_buff0;
						dwc_ep->cur_pkt_dma_addr =
						    dwc_ep->dma_addr0;
					}

				}

				dsts.d32 =
				    DWC_READ_REG32(&GET_CORE_IF(pcd)->dev_if->
						   dev_global_regs->dsts);
				dwc_ep->next_frame = dsts.b.soffn;

				dwc_otg_iso_ep_start_frm_transfer(GET_CORE_IF
								  (pcd),
								  dwc_ep);
			}
		}
	}
#else
	/** @todo implement ISR */
	gintmsk_data_t intr_mask = {.d32 = 0 };
	dwc_otg_core_if_t *core_if;
	deptsiz_data_t deptsiz = {.d32 = 0 };
	depctl_data_t depctl = {.d32 = 0 };
	dctl_data_t dctl = {.d32 = 0 };
	dwc_ep_t *dwc_ep = NULL;
	int i;
	core_if = GET_CORE_IF(pcd);

	for (i = 0; i < core_if->dev_if->num_out_eps; ++i) {
		dwc_ep = &pcd->out_ep[i].dwc_ep;
		depctl.d32 =
			DWC_READ_REG32(&core_if->dev_if->out_ep_regs[dwc_ep->num]->doepctl);
		if (depctl.b.epena && depctl.b.dpid == (core_if->frame_num & 0x1)) {
			core_if->dev_if->isoc_ep = dwc_ep;
			deptsiz.d32 =
					DWC_READ_REG32(&core_if->dev_if->out_ep_regs[dwc_ep->num]->doeptsiz);
				break;
		}
	}
	dctl.d32 = DWC_READ_REG32(&core_if->dev_if->dev_global_regs->dctl);
	gintsts.d32 = DWC_READ_REG32(&core_if->core_global_regs->gintsts);
	intr_mask.d32 = DWC_READ_REG32(&core_if->core_global_regs->gintmsk);

	if (!intr_mask.b.goutnakeff) {
		/* Unmask it */
		intr_mask.b.goutnakeff = 1;
		DWC_WRITE_REG32(&core_if->core_global_regs->gintmsk, intr_mask.d32);
	}
	if (!gintsts.b.goutnakeff) {
		dctl.b.sgoutnak = 1;
	}
	DWC_WRITE_REG32(&core_if->dev_if->dev_global_regs->dctl, dctl.d32);

	depctl.d32 = DWC_READ_REG32(&core_if->dev_if->out_ep_regs[dwc_ep->num]->doepctl);
	if (depctl.b.epena) {
		depctl.b.epdis = 1;
		depctl.b.snak = 1;
	}
	DWC_WRITE_REG32(&core_if->dev_if->out_ep_regs[dwc_ep->num]->doepctl, depctl.d32);

	intr_mask.d32 = 0;
	intr_mask.b.incomplisoout = 1;

#endif /* DWC_EN_ISOC */

	/* Clear interrupt */
	gintsts.d32 = 0;
	gintsts.b.incomplisoout = 1;
	DWC_WRITE_REG32(&GET_CORE_IF(pcd)->core_global_regs->gintsts,
			gintsts.d32);

	return 1;
}