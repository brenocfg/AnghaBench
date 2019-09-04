#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct dwc2_qtd {size_t isoc_frame_index_last; scalar_t__ isoc_frame_index; TYPE_1__* urb; } ;
struct dwc2_qh {int /*<<< orphan*/  ntd; scalar_t__* n_bytes; struct dwc2_dma_desc* desc_list; scalar_t__ desc_list_dma; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; } ;
struct dwc2_host_chan {scalar_t__ halt_status; scalar_t__ ep_is_in; } ;
struct dwc2_hcd_iso_packet_desc {int /*<<< orphan*/  status; scalar_t__ actual_length; scalar_t__ offset; } ;
struct dwc2_dma_desc {int status; scalar_t__ buf; } ;
struct TYPE_2__ {scalar_t__ packet_count; int /*<<< orphan*/  error_count; scalar_t__ dma; struct dwc2_hcd_iso_packet_desc* iso_descs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int DWC2_CMPL_DONE ; 
 int DWC2_CMPL_STOP ; 
 scalar_t__ DWC2_HC_XFER_URB_DEQUEUE ; 
 int EINVAL ; 
 int /*<<< orphan*/  EPROTO ; 
 int HOST_DMA_IOC ; 
 int HOST_DMA_ISOC_NBYTES_MASK ; 
 int HOST_DMA_ISOC_NBYTES_SHIFT ; 
 int HOST_DMA_STS_MASK ; 
 int HOST_DMA_STS_PKTERR ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_hcd_qtd_unlink_and_free (struct dwc2_hsotg*,struct dwc2_qtd*,struct dwc2_qh*) ; 
 int /*<<< orphan*/  dwc2_host_complete (struct dwc2_hsotg*,struct dwc2_qtd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc2_cmpl_host_isoc_dma_desc(struct dwc2_hsotg *hsotg,
					struct dwc2_host_chan *chan,
					struct dwc2_qtd *qtd,
					struct dwc2_qh *qh, u16 idx)
{
	struct dwc2_dma_desc *dma_desc;
	struct dwc2_hcd_iso_packet_desc *frame_desc;
	u16 remain = 0;
	int rc = 0;

	if (!qtd->urb)
		return -EINVAL;

	dma_sync_single_for_cpu(hsotg->dev, qh->desc_list_dma + (idx *
				sizeof(struct dwc2_dma_desc)),
				sizeof(struct dwc2_dma_desc),
				DMA_FROM_DEVICE);

	dma_desc = &qh->desc_list[idx];

	frame_desc = &qtd->urb->iso_descs[qtd->isoc_frame_index_last];
	dma_desc->buf = (u32)(qtd->urb->dma + frame_desc->offset);
	if (chan->ep_is_in)
		remain = (dma_desc->status & HOST_DMA_ISOC_NBYTES_MASK) >>
			 HOST_DMA_ISOC_NBYTES_SHIFT;

	if ((dma_desc->status & HOST_DMA_STS_MASK) == HOST_DMA_STS_PKTERR) {
		/*
		 * XactError, or unable to complete all the transactions
		 * in the scheduled micro-frame/frame, both indicated by
		 * HOST_DMA_STS_PKTERR
		 */
		qtd->urb->error_count++;
		frame_desc->actual_length = qh->n_bytes[idx] - remain;
		frame_desc->status = -EPROTO;
	} else {
		/* Success */
		frame_desc->actual_length = qh->n_bytes[idx] - remain;
		frame_desc->status = 0;
	}

	if (++qtd->isoc_frame_index == qtd->urb->packet_count) {
		/*
		 * urb->status is not used for isoc transfers here. The
		 * individual frame_desc status are used instead.
		 */
		dwc2_host_complete(hsotg, qtd, 0);
		dwc2_hcd_qtd_unlink_and_free(hsotg, qtd, qh);

		/*
		 * This check is necessary because urb_dequeue can be called
		 * from urb complete callback (sound driver for example). All
		 * pending URBs are dequeued there, so no need for further
		 * processing.
		 */
		if (chan->halt_status == DWC2_HC_XFER_URB_DEQUEUE)
			return -1;
		rc = DWC2_CMPL_DONE;
	}

	qh->ntd--;

	/* Stop if IOC requested descriptor reached */
	if (dma_desc->status & HOST_DMA_IOC)
		rc = DWC2_CMPL_STOP;

	return rc;
}