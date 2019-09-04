#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_19__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_27__ {int epinfobase; } ;
struct TYPE_29__ {int d32; TYPE_4__ b; } ;
typedef  TYPE_6__ gdfifocfg_data_t ;
struct TYPE_30__ {int d32; } ;
typedef  TYPE_7__ fifosize_data_t ;
struct TYPE_31__ {int /*<<< orphan*/  lock; TYPE_3__* core_if; } ;
typedef  TYPE_8__ dwc_otg_pcd_t ;
struct TYPE_23__ {size_t num; int tx_fifo_num; scalar_t__ type; scalar_t__ is_in; int /*<<< orphan*/  dma_desc_addr; int /*<<< orphan*/ * desc_addr; } ;
struct TYPE_32__ {int stopped; TYPE_19__ dwc_ep; int /*<<< orphan*/ * desc; } ;
typedef  TYPE_9__ dwc_otg_pcd_ep_t ;
typedef  int /*<<< orphan*/  dwc_otg_dev_dma_desc_t ;
typedef  int /*<<< orphan*/  dwc_irqflags_t ;
typedef  int /*<<< orphan*/  dwc_dma_t ;
struct TYPE_28__ {int /*<<< orphan*/  gdfifocfg; int /*<<< orphan*/ * dtxfsiz; } ;
struct TYPE_26__ {TYPE_2__* ep_xfer_info; int /*<<< orphan*/ * ep_xfer_timer; TYPE_1__* core_params; } ;
struct TYPE_25__ {scalar_t__ state; } ;
struct TYPE_24__ {scalar_t__ dev_out_nak; } ;
struct TYPE_22__ {scalar_t__ snpsid; scalar_t__ dma_desc_enable; TYPE_5__* core_global_regs; scalar_t__ en_multiple_tx_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
 int DWC_E_INVALID ; 
 int DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_IRQSAVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK_IRQRESTORE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_TIMER_CANCEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int) ; 
 TYPE_10__* GET_CORE_IF (TYPE_8__*) ; 
 int /*<<< orphan*/  MAX_DMA_DESC_CNT ; 
 scalar_t__ OTG_CORE_REV_2_94a ; 
 scalar_t__ UE_ISOCHRONOUS ; 
 int /*<<< orphan*/  dwc_otg_ep_deactivate (TYPE_10__*,TYPE_19__*) ; 
 int /*<<< orphan*/  dwc_otg_ep_free_desc_chain (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_flush_tx_fifo (TYPE_10__*,int) ; 
 struct device* dwc_otg_pcd_to_dev (TYPE_8__*) ; 
 int /*<<< orphan*/  dwc_otg_request_nuke (TYPE_9__*) ; 
 TYPE_9__* get_ep_from_handle (TYPE_8__*,void*) ; 
 int /*<<< orphan*/  release_perio_tx_fifo (TYPE_10__*,int) ; 
 int /*<<< orphan*/  release_tx_fifo (TYPE_10__*,int) ; 

int dwc_otg_pcd_ep_disable(dwc_otg_pcd_t * pcd, void *ep_handle)
{
	dwc_otg_pcd_ep_t *ep;
	dwc_irqflags_t flags;
	dwc_otg_dev_dma_desc_t *desc_addr;
	dwc_dma_t dma_desc_addr;
	gdfifocfg_data_t gdfifocfgbase = {.d32 = 0 };
	gdfifocfg_data_t gdfifocfg = {.d32 = 0 };
	fifosize_data_t dptxfsiz = {.d32 = 0 };
	struct device *dev = dwc_otg_pcd_to_dev(pcd);

	ep = get_ep_from_handle(pcd, ep_handle);

	if (!ep || !ep->desc) {
		DWC_DEBUGPL(DBG_PCD, "bad ep address\n");
		return -DWC_E_INVALID;
	}

	DWC_SPINLOCK_IRQSAVE(pcd->lock, &flags);

	dwc_otg_request_nuke(ep);

	dwc_otg_ep_deactivate(GET_CORE_IF(pcd), &ep->dwc_ep);
	if (pcd->core_if->core_params->dev_out_nak) {
		DWC_TIMER_CANCEL(pcd->core_if->ep_xfer_timer[ep->dwc_ep.num]);
		pcd->core_if->ep_xfer_info[ep->dwc_ep.num].state = 0;
	}
	ep->desc = NULL;
	ep->stopped = 1;

	gdfifocfg.d32 =
	    DWC_READ_REG32(&GET_CORE_IF(pcd)->core_global_regs->gdfifocfg);
	gdfifocfgbase.d32 = gdfifocfg.d32 >> 16;

	if (ep->dwc_ep.is_in) {
		if (GET_CORE_IF(pcd)->en_multiple_tx_fifo) {
			/* Flush the Tx FIFO */
			dwc_otg_flush_tx_fifo(GET_CORE_IF(pcd),
					      ep->dwc_ep.tx_fifo_num);
		}
		release_perio_tx_fifo(GET_CORE_IF(pcd), ep->dwc_ep.tx_fifo_num);
		release_tx_fifo(GET_CORE_IF(pcd), ep->dwc_ep.tx_fifo_num);
		if (GET_CORE_IF(pcd)->en_multiple_tx_fifo) {
			/* Decreasing EPinfo Base Addr */
			dptxfsiz.d32 =
			    (DWC_READ_REG32
			     (&GET_CORE_IF(pcd)->
				core_global_regs->dtxfsiz[ep->dwc_ep.tx_fifo_num-1]) >> 16);
			gdfifocfg.b.epinfobase = gdfifocfgbase.d32 - dptxfsiz.d32;
			if (GET_CORE_IF(pcd)->snpsid <= OTG_CORE_REV_2_94a) {
				DWC_WRITE_REG32(&GET_CORE_IF(pcd)->core_global_regs->gdfifocfg,
					gdfifocfg.d32);
			}
		}
	}

	/* Free DMA Descriptors */
	if (GET_CORE_IF(pcd)->dma_desc_enable) {
		if (ep->dwc_ep.type != UE_ISOCHRONOUS) {
			desc_addr = ep->dwc_ep.desc_addr;
			dma_desc_addr = ep->dwc_ep.dma_desc_addr;

			/* Cannot call dma_free_coherent() with IRQs disabled */
			DWC_SPINUNLOCK_IRQRESTORE(pcd->lock, flags);
			dwc_otg_ep_free_desc_chain(dev, desc_addr, dma_desc_addr,
						   MAX_DMA_DESC_CNT);

			goto out_unlocked;
		}
	}
	DWC_SPINUNLOCK_IRQRESTORE(pcd->lock, flags);

out_unlocked:
	DWC_DEBUGPL(DBG_PCD, "%d %s disabled\n", ep->dwc_ep.num,
		    ep->dwc_ep.is_in ? "IN" : "OUT");
	return 0;

}