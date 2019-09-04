#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_19__ {int incomplisoin; } ;
struct TYPE_21__ {scalar_t__ d32; TYPE_4__ b; } ;
typedef  TYPE_6__ gintsts_data_t ;
struct TYPE_22__ {TYPE_1__* in_ep; } ;
typedef  TYPE_7__ dwc_otg_pcd_t ;
struct TYPE_23__ {int num_in_eps; TYPE_3__** in_ep_regs; } ;
typedef  TYPE_8__ dwc_otg_dev_if_t ;
struct TYPE_24__ {scalar_t__ type; int /*<<< orphan*/  frm_overrun; int /*<<< orphan*/  frame_num; } ;
typedef  TYPE_9__ dwc_ep_t ;
struct TYPE_17__ {int snak; int epdis; scalar_t__ epena; } ;
struct TYPE_14__ {void* d32; TYPE_2__ b; } ;
typedef  TYPE_10__ depctl_data_t ;
struct TYPE_20__ {int /*<<< orphan*/  gintsts; } ;
struct TYPE_18__ {int /*<<< orphan*/  diepctl; } ;
struct TYPE_16__ {TYPE_9__ dwc_ep; } ;
struct TYPE_15__ {TYPE_5__* core_global_regs; int /*<<< orphan*/  frame_num; TYPE_8__* dev_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,void*,void*) ; 
 scalar_t__ DWC_OTG_EP_TYPE_ISOC ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_12__* GET_CORE_IF (TYPE_7__*) ; 
 scalar_t__ drop_transfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t dwc_otg_pcd_handle_incomplete_isoc_in_intr(dwc_otg_pcd_t * pcd)
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

	for (i = 1; i <= dev_if->num_in_eps; ++i) {
		dwc_ep = &pcd->in_ep[i].dwc_ep;
		if (dwc_ep->active && dwc_ep->type == DWC_OTG_EP_TYPE_ISOC) {
			deptsiz.d32 =
			    DWC_READ_REG32(&dev_if->in_ep_regs[i]->dieptsiz);
			depctl.d32 =
			    DWC_READ_REG32(&dev_if->in_ep_regs[i]->diepctl);

			if (depctl.b.epdis && deptsiz.d32) {
				set_current_pkt_info(GET_CORE_IF(pcd), dwc_ep);
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
	depctl_data_t depctl = {.d32 = 0 };
	dwc_ep_t *dwc_ep;
	dwc_otg_dev_if_t *dev_if;
	int i;
	dev_if = GET_CORE_IF(pcd)->dev_if;

	DWC_DEBUGPL(DBG_PCD,"Incomplete ISO IN \n");

	for (i = 1; i <= dev_if->num_in_eps; ++i) {
		dwc_ep = &pcd->in_ep[i-1].dwc_ep;
		depctl.d32 =
			DWC_READ_REG32(&dev_if->in_ep_regs[i]->diepctl);
		if (depctl.b.epena && dwc_ep->type == DWC_OTG_EP_TYPE_ISOC) {
			if (drop_transfer(dwc_ep->frame_num, GET_CORE_IF(pcd)->frame_num,
							dwc_ep->frm_overrun))
			{
				depctl.d32 =
					DWC_READ_REG32(&dev_if->in_ep_regs[i]->diepctl);
				depctl.b.snak = 1;
				depctl.b.epdis = 1;
				DWC_MODIFY_REG32(&dev_if->in_ep_regs[i]->diepctl, depctl.d32, depctl.d32);
			}
		}
	}

	/*intr_mask.b.incomplisoin = 1;
	DWC_MODIFY_REG32(&GET_CORE_IF(pcd)->core_global_regs->gintmsk,
			 intr_mask.d32, 0);	 */
#endif				//DWC_EN_ISOC

	/* Clear interrupt */
	gintsts.d32 = 0;
	gintsts.b.incomplisoin = 1;
	DWC_WRITE_REG32(&GET_CORE_IF(pcd)->core_global_regs->gintsts,
			gintsts.d32);

	return 1;
}