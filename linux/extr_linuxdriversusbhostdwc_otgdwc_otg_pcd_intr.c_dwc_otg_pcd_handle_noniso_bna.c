#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_18__ ;
typedef  struct TYPE_26__   TYPE_16__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_36__ {TYPE_13__* core_if; } ;
typedef  TYPE_9__ dwc_otg_pcd_t ;
struct TYPE_24__ {int desc_cnt; size_t num; scalar_t__ is_in; scalar_t__ type; int dma_desc_addr; TYPE_12__* desc_addr; } ;
struct TYPE_20__ {TYPE_9__* pcd; TYPE_14__ dwc_ep; } ;
typedef  TYPE_10__ dwc_otg_pcd_ep_t ;
struct TYPE_21__ {int /*<<< orphan*/  doepdma; } ;
typedef  TYPE_11__ dwc_otg_dev_out_ep_regs_t ;
struct TYPE_31__ {int /*<<< orphan*/  d32; } ;
struct TYPE_22__ {TYPE_4__ status; } ;
typedef  TYPE_12__ dwc_otg_dev_dma_desc_t ;
struct TYPE_23__ {TYPE_2__* dev_if; TYPE_1__* core_params; } ;
typedef  TYPE_13__ dwc_otg_core_if_t ;
typedef  TYPE_14__ dwc_ep_t ;
struct TYPE_30__ {int /*<<< orphan*/  bs; } ;
struct TYPE_25__ {int /*<<< orphan*/  d32; TYPE_3__ b; } ;
typedef  TYPE_15__ dev_dma_desc_sts_t ;
struct TYPE_35__ {int epena; int cnak; } ;
struct TYPE_26__ {int /*<<< orphan*/  d32; TYPE_8__ b; } ;
typedef  TYPE_16__ depctl_data_t ;
struct TYPE_34__ {TYPE_6__** in_ep_regs; TYPE_5__** out_ep_regs; } ;
struct TYPE_33__ {int diepctl; } ;
struct TYPE_32__ {int doepctl; } ;
struct TYPE_29__ {TYPE_11__** out_ep_regs; } ;
struct TYPE_28__ {scalar_t__ cont_on_bna; } ;
struct TYPE_27__ {TYPE_7__* dev_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  BS_HOST_READY ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int volatile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DWC_OTG_EP_TYPE_CONTROL ; 
 int DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WARN (char*,size_t,char*,int) ; 
 TYPE_18__* GET_CORE_IF (TYPE_9__*) ; 

__attribute__((used)) static void dwc_otg_pcd_handle_noniso_bna(dwc_otg_pcd_ep_t * ep)
{
	dwc_ep_t *dwc_ep = &ep->dwc_ep;
	volatile uint32_t *addr;
	depctl_data_t depctl = {.d32 = 0 };
	dwc_otg_pcd_t *pcd = ep->pcd;
	dwc_otg_dev_dma_desc_t *dma_desc;
	dev_dma_desc_sts_t sts = {.d32 = 0 };
	dwc_otg_core_if_t *core_if = ep->pcd->core_if;
	int i, start;

	if (!dwc_ep->desc_cnt)
		DWC_WARN("Ep%d %s Descriptor count = %d \n", dwc_ep->num,
			 (dwc_ep->is_in ? "IN" : "OUT"), dwc_ep->desc_cnt);

	if (core_if->core_params->cont_on_bna && !dwc_ep->is_in
							&& dwc_ep->type != DWC_OTG_EP_TYPE_CONTROL) {
		uint32_t doepdma;
		dwc_otg_dev_out_ep_regs_t *out_regs =
			core_if->dev_if->out_ep_regs[dwc_ep->num];
		doepdma = DWC_READ_REG32(&(out_regs->doepdma));
		start = (doepdma - dwc_ep->dma_desc_addr)/sizeof(dwc_otg_dev_dma_desc_t);
		dma_desc = &(dwc_ep->desc_addr[start]);
	} else {
		start = 0;
		dma_desc = dwc_ep->desc_addr;
	}


	for (i = start; i < dwc_ep->desc_cnt; ++i, ++dma_desc) {
		sts.d32 = dma_desc->status.d32;
		sts.b.bs = BS_HOST_READY;
		dma_desc->status.d32 = sts.d32;
	}

	if (dwc_ep->is_in == 0) {
		addr =
		    &GET_CORE_IF(pcd)->dev_if->out_ep_regs[dwc_ep->num]->
		    doepctl;
	} else {
		addr =
		    &GET_CORE_IF(pcd)->dev_if->in_ep_regs[dwc_ep->num]->diepctl;
	}
	depctl.b.epena = 1;
	depctl.b.cnak = 1;
	DWC_MODIFY_REG32(addr, 0, depctl.d32);
}