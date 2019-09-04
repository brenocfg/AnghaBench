#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_20__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_19__ ;
typedef  struct TYPE_31__   TYPE_18__ ;
typedef  struct TYPE_30__   TYPE_17__ ;
typedef  struct TYPE_29__   TYPE_16__ ;
typedef  struct TYPE_28__   TYPE_15__ ;
typedef  struct TYPE_27__   TYPE_14__ ;
typedef  struct TYPE_26__   TYPE_13__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_25__ {void* d32; } ;
typedef  TYPE_12__ gnptxsts_data_t ;
struct TYPE_35__ {int nptxfempty; } ;
struct TYPE_26__ {int d32; TYPE_2__ b; } ;
typedef  TYPE_13__ gintmsk_data_t ;
struct TYPE_27__ {int /*<<< orphan*/  doepctl; int /*<<< orphan*/  doepdma; int /*<<< orphan*/  doeptsiz; } ;
typedef  TYPE_14__ dwc_otg_dev_out_ep_regs_t ;
struct TYPE_28__ {int /*<<< orphan*/  diepctl; int /*<<< orphan*/  diepdma; int /*<<< orphan*/  dieptsiz; } ;
typedef  TYPE_15__ dwc_otg_dev_in_ep_regs_t ;
struct TYPE_42__ {int l; int ioc; int sp; scalar_t__ bytes; void* bs; scalar_t__ sts; } ;
struct TYPE_23__ {TYPE_9__ b; } ;
struct TYPE_29__ {TYPE_10__ status; scalar_t__ buf; } ;
typedef  TYPE_16__ dwc_otg_dev_dma_desc_t ;
struct TYPE_37__ {scalar_t__ architecture; } ;
struct TYPE_38__ {TYPE_4__ b; } ;
struct TYPE_30__ {scalar_t__ dma_desc_enable; scalar_t__ dma_enable; scalar_t__ en_multiple_tx_fifo; TYPE_5__ hwcfg2; TYPE_11__* dev_if; TYPE_7__* core_global_regs; int /*<<< orphan*/ * nextep_seq; TYPE_1__* core_params; } ;
typedef  TYPE_17__ dwc_otg_core_if_t ;
struct TYPE_31__ {int is_in; scalar_t__ total_len; scalar_t__ xfer_count; scalar_t__ maxpacket; scalar_t__ xfer_len; size_t num; scalar_t__ dma_addr; } ;
typedef  TYPE_18__ dwc_ep_t ;
struct TYPE_41__ {scalar_t__ xfersize; int pktcnt; } ;
struct TYPE_32__ {int d32; TYPE_8__ b; } ;
typedef  TYPE_19__ deptsiz0_data_t ;
struct TYPE_39__ {int cnak; int epena; int /*<<< orphan*/  nextep; } ;
struct TYPE_34__ {int d32; TYPE_6__ b; } ;
typedef  TYPE_20__ depctl_data_t ;
struct TYPE_40__ {int /*<<< orphan*/  gintmsk; int /*<<< orphan*/  gnptxsts; } ;
struct TYPE_36__ {int /*<<< orphan*/  dtknqr4_fifoemptymsk; } ;
struct TYPE_33__ {int /*<<< orphan*/  en_multiple_tx_fifo; } ;
struct TYPE_24__ {int dma_in_desc_addr; int dma_out_desc_addr; TYPE_16__* out_desc_addr; TYPE_14__** out_ep_regs; TYPE_3__* dev_global_regs; TYPE_16__* in_desc_addr; TYPE_15__** in_ep_regs; } ;

/* Variables and functions */
 void* BS_HOST_BUSY ; 
 void* BS_HOST_READY ; 
 int /*<<< orphan*/  DBG_PCDV ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ DWC_INT_DMA_ARCH ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int,int) ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int) ; 

void dwc_otg_ep0_continue_transfer(dwc_otg_core_if_t * core_if, dwc_ep_t * ep)
{
	depctl_data_t depctl;
	deptsiz0_data_t deptsiz;
	gintmsk_data_t intr_mask = {.d32 = 0 };
	dwc_otg_dev_dma_desc_t *dma_desc;

	if (ep->is_in == 1) {
		dwc_otg_dev_in_ep_regs_t *in_regs =
		    core_if->dev_if->in_ep_regs[0];
		gnptxsts_data_t tx_status = {.d32 = 0 };

		tx_status.d32 =
		    DWC_READ_REG32(&core_if->core_global_regs->gnptxsts);
		/** @todo Should there be check for room in the Tx
		 * Status Queue.  If not remove the code above this comment. */

		depctl.d32 = DWC_READ_REG32(&in_regs->diepctl);
		deptsiz.d32 = DWC_READ_REG32(&in_regs->dieptsiz);

		/* Program the transfer size and packet count
		 *      as follows: xfersize = N * maxpacket +
		 *      short_packet pktcnt = N + (short_packet
		 *      exist ? 1 : 0)
		 */

		if (core_if->dma_desc_enable == 0) {
			deptsiz.b.xfersize =
			    (ep->total_len - ep->xfer_count) >
			    ep->maxpacket ? ep->maxpacket : (ep->total_len -
							     ep->xfer_count);
			deptsiz.b.pktcnt = 1;
			if (core_if->dma_enable == 0) {
				ep->xfer_len += deptsiz.b.xfersize;
			} else {
				ep->xfer_len = deptsiz.b.xfersize;
			}
			DWC_WRITE_REG32(&in_regs->dieptsiz, deptsiz.d32);
		} else {
			ep->xfer_len =
			    (ep->total_len - ep->xfer_count) >
			    ep->maxpacket ? ep->maxpacket : (ep->total_len -
							     ep->xfer_count);

			dma_desc = core_if->dev_if->in_desc_addr;

			/** DMA Descriptor Setup */
			dma_desc->status.b.bs = BS_HOST_BUSY;
			dma_desc->status.b.l = 1;
			dma_desc->status.b.ioc = 1;
			dma_desc->status.b.sp =
			    (ep->xfer_len == ep->maxpacket) ? 0 : 1;
			dma_desc->status.b.bytes = ep->xfer_len;
			dma_desc->buf = ep->dma_addr;
			dma_desc->status.b.sts = 0;
			dma_desc->status.b.bs = BS_HOST_READY;

			/** DIEPDMA0 Register write */
			DWC_WRITE_REG32(&in_regs->diepdma,
					core_if->dev_if->dma_in_desc_addr);
		}

		DWC_DEBUGPL(DBG_PCDV,
			    "IN len=%d  xfersize=%d pktcnt=%d [%08x]\n",
			    ep->xfer_len, deptsiz.b.xfersize, deptsiz.b.pktcnt,
			    deptsiz.d32);

		/* Write the DMA register */
		if (core_if->hwcfg2.b.architecture == DWC_INT_DMA_ARCH) {
			if (core_if->dma_desc_enable == 0)
				DWC_WRITE_REG32(&(in_regs->diepdma),
						(uint32_t) ep->dma_addr);
		}
		if (!core_if->core_params->en_multiple_tx_fifo && core_if->dma_enable)
			depctl.b.nextep = core_if->nextep_seq[ep->num];
		/* EP enable, IN data in FIFO */
		depctl.b.cnak = 1;
		depctl.b.epena = 1;
		DWC_WRITE_REG32(&in_regs->diepctl, depctl.d32);

		/**
		 * Enable the Non-Periodic Tx FIFO empty interrupt, the
		 * data will be written into the fifo by the ISR.
		 */
		if (!core_if->dma_enable) {
			if (core_if->en_multiple_tx_fifo == 0) {
				/* First clear it from GINTSTS */
				intr_mask.b.nptxfempty = 1;
				DWC_MODIFY_REG32(&core_if->
						 core_global_regs->gintmsk,
						 intr_mask.d32, intr_mask.d32);

			} else {
				/* Enable the Tx FIFO Empty Interrupt for this EP */
				if (ep->xfer_len > 0) {
					uint32_t fifoemptymsk = 0;
					fifoemptymsk |= 1 << ep->num;
					DWC_MODIFY_REG32(&core_if->
							 dev_if->dev_global_regs->dtknqr4_fifoemptymsk,
							 0, fifoemptymsk);
				}
			}
		}
	} else {
		dwc_otg_dev_out_ep_regs_t *out_regs =
		    core_if->dev_if->out_ep_regs[0];

		depctl.d32 = DWC_READ_REG32(&out_regs->doepctl);
		deptsiz.d32 = DWC_READ_REG32(&out_regs->doeptsiz);

		/* Program the transfer size and packet count
		 *      as follows: xfersize = N * maxpacket +
		 *      short_packet pktcnt = N + (short_packet
		 *      exist ? 1 : 0)
		 */
		deptsiz.b.xfersize = ep->maxpacket;
		deptsiz.b.pktcnt = 1;

		if (core_if->dma_desc_enable == 0) {
			DWC_WRITE_REG32(&out_regs->doeptsiz, deptsiz.d32);
		} else {
			dma_desc = core_if->dev_if->out_desc_addr;

			/** DMA Descriptor Setup */
			dma_desc->status.b.bs = BS_HOST_BUSY;
			dma_desc->status.b.l = 1;
			dma_desc->status.b.ioc = 1;
			dma_desc->status.b.bytes = ep->maxpacket;
			dma_desc->buf = ep->dma_addr;
			dma_desc->status.b.sts = 0;
			dma_desc->status.b.bs = BS_HOST_READY;

			/** DOEPDMA0 Register write */
			DWC_WRITE_REG32(&out_regs->doepdma,
					core_if->dev_if->dma_out_desc_addr);
		}

		DWC_DEBUGPL(DBG_PCDV,
			    "IN len=%d  xfersize=%d pktcnt=%d [%08x]\n",
			    ep->xfer_len, deptsiz.b.xfersize, deptsiz.b.pktcnt,
			    deptsiz.d32);

		/* Write the DMA register */
		if (core_if->hwcfg2.b.architecture == DWC_INT_DMA_ARCH) {
			if (core_if->dma_desc_enable == 0)
				DWC_WRITE_REG32(&(out_regs->doepdma),
						(uint32_t) ep->dma_addr);

		}

		/* EP enable, IN data in FIFO */
		depctl.b.cnak = 1;
		depctl.b.epena = 1;
		DWC_WRITE_REG32(&out_regs->doepctl, depctl.d32);

	}
}