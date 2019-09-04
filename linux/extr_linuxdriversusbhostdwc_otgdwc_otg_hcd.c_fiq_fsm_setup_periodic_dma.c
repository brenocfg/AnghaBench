#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct fiq_dma_blob {TYPE_7__* channel; } ;
struct TYPE_18__ {int* slot_len; scalar_t__ index; } ;
struct TYPE_30__ {int xfersize; scalar_t__ pid; } ;
struct TYPE_31__ {TYPE_8__ b; } ;
struct TYPE_27__ {void* d32; } ;
struct TYPE_23__ {int mps; } ;
struct TYPE_24__ {TYPE_1__ b; } ;
struct fiq_channel_state {int nrpackets; TYPE_10__ dma_info; TYPE_9__ hctsiz_copy; TYPE_5__ hcdma_copy; TYPE_2__ hcchar_copy; } ;
struct dwc_otg_hcd_iso_packet_desc {int length; int offset; } ;
struct TYPE_19__ {size_t isoc_frame_index; TYPE_3__* urb; } ;
typedef  TYPE_11__ dwc_otg_qtd_t ;
struct TYPE_20__ {scalar_t__ ep_type; int /*<<< orphan*/  qtd_list; TYPE_14__* channel; } ;
typedef  TYPE_12__ dwc_otg_qh_t ;
struct TYPE_21__ {TYPE_4__* fiq_state; struct fiq_dma_blob* fiq_dmab; } ;
typedef  TYPE_13__ dwc_otg_hcd_t ;
struct TYPE_22__ {size_t hc_num; scalar_t__ ep_is_in; } ;
typedef  TYPE_14__ dwc_hc_t ;
typedef  void* dma_addr_t ;
struct TYPE_29__ {TYPE_6__* index; } ;
struct TYPE_28__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_26__ {scalar_t__ dma_base; } ;
struct TYPE_25__ {int /*<<< orphan*/ * buf; struct dwc_otg_hcd_iso_packet_desc* iso_descs; } ;

/* Variables and functions */
 TYPE_11__* DWC_CIRCLEQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ UE_ISOCHRONOUS ; 
 int /*<<< orphan*/  dwc_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int fiq_fsm_setup_periodic_dma(dwc_otg_hcd_t *hcd, struct fiq_channel_state *st, dwc_otg_qh_t *qh)
 {
	int frame_length, i = 0;
	uint8_t *ptr = NULL;
	dwc_hc_t *hc = qh->channel;
	struct fiq_dma_blob *blob;
	struct dwc_otg_hcd_iso_packet_desc *frame_desc;

	for (i = 0; i < 6; i++) {
		st->dma_info.slot_len[i] = 255;
	}
	st->dma_info.index = 0;
	i = 0;
	if (hc->ep_is_in) {
		/*
		 * Set dma_regs to bounce buffer. FIQ will update the
		 * state depending on transaction progress.
		 * Pointer arithmetic on hcd->fiq_state->dma_base (a dma_addr_t)
		 * to point it to the correct offset in the allocated buffers.
		 */
		blob = (struct fiq_dma_blob *) hcd->fiq_state->dma_base;
		st->hcdma_copy.d32 = (dma_addr_t) blob->channel[hc->hc_num].index[0].buf;

		/* Calculate the max number of CSPLITS such that the FIQ can time out
		 * a transaction if it fails.
		 */
		frame_length = st->hcchar_copy.b.mps;
		do {
			i++;
			frame_length -= 188;
		} while (frame_length >= 0);
		st->nrpackets = i;
		return 1;
	} else {
		if (qh->ep_type == UE_ISOCHRONOUS) {

			dwc_otg_qtd_t *qtd = DWC_CIRCLEQ_FIRST(&qh->qtd_list);

			frame_desc = &qtd->urb->iso_descs[qtd->isoc_frame_index];
			frame_length = frame_desc->length;

			/* Virtual address for bounce buffers */
			blob = hcd->fiq_dmab;

			ptr = qtd->urb->buf + frame_desc->offset;
			if (frame_length == 0) {
				/*
				 * for isochronous transactions, we must still transmit a packet
				 * even if the length is zero.
				 */
				st->dma_info.slot_len[0] = 0;
				st->nrpackets = 1;
			} else {
				do {
					if (frame_length <= 188) {
						dwc_memcpy(&blob->channel[hc->hc_num].index[i].buf[0], ptr, frame_length);
						st->dma_info.slot_len[i] = frame_length;
						ptr += frame_length;
					} else {
						dwc_memcpy(&blob->channel[hc->hc_num].index[i].buf[0], ptr, 188);
						st->dma_info.slot_len[i] = 188;
						ptr += 188;
					}
					i++;
					frame_length -= 188;
				} while (frame_length > 0);
				st->nrpackets = i;
			}
			ptr = qtd->urb->buf + frame_desc->offset;
			/*
			 * Point the HC at the DMA address of the bounce buffers
			 *
			 * Pointer arithmetic on hcd->fiq_state->dma_base (a
			 * dma_addr_t) to point it to the correct offset in the
			 * allocated buffers.
			 */
			blob = (struct fiq_dma_blob *) hcd->fiq_state->dma_base;
			st->hcdma_copy.d32 = (dma_addr_t) blob->channel[hc->hc_num].index[0].buf;

			/* fixup xfersize to the actual packet size */
			st->hctsiz_copy.b.pid = 0;
			st->hctsiz_copy.b.xfersize = st->dma_info.slot_len[0];
			return 1;
		} else {
			/* For interrupt, single OUT packet required, goes in the SSPLIT from hc_buff. */
			return 0;
		}
	}
}