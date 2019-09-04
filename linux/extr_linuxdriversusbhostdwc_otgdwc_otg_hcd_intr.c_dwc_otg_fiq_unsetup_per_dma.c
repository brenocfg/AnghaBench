#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct fiq_dma_blob {TYPE_5__* channel; } ;
struct TYPE_20__ {int index; scalar_t__* slot_len; } ;
struct fiq_channel_state {TYPE_6__ dma_info; } ;
struct TYPE_21__ {int isoc_frame_index; TYPE_3__* urb; } ;
typedef  TYPE_7__ dwc_otg_qtd_t ;
struct TYPE_22__ {scalar_t__ ep_type; TYPE_10__* channel; } ;
typedef  TYPE_8__ dwc_otg_qh_t ;
struct TYPE_23__ {TYPE_1__* fiq_state; struct fiq_dma_blob* fiq_dmab; } ;
typedef  TYPE_9__ dwc_otg_hcd_t ;
struct TYPE_14__ {scalar_t__ ep_is_in; } ;
typedef  TYPE_10__ dwc_hc_t ;
struct TYPE_19__ {TYPE_4__* index; } ;
struct TYPE_18__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_17__ {int /*<<< orphan*/  actual_length; TYPE_2__* iso_descs; int /*<<< orphan*/ * buf; } ;
struct TYPE_16__ {int /*<<< orphan*/  offset; } ;
struct TYPE_15__ {struct fiq_channel_state* channel; } ;

/* Variables and functions */
 scalar_t__ UE_ISOCHRONOUS ; 
 int /*<<< orphan*/  dwc_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

int dwc_otg_fiq_unsetup_per_dma(dwc_otg_hcd_t *hcd, dwc_otg_qh_t *qh, dwc_otg_qtd_t *qtd, uint32_t num)
{
	dwc_hc_t *hc = qh->channel;
	struct fiq_dma_blob *blob = hcd->fiq_dmab;
	struct fiq_channel_state *st = &hcd->fiq_state->channel[num];
	uint8_t *ptr = NULL;
	int index = 0, len = 0;
	int i = 0;
	if (hc->ep_is_in) {
		/* Copy data out of the DMA bounce buffers to the URB's buffer.
		 * The align_buf is ignored as this is ignored on FSM enqueue. */
		ptr = qtd->urb->buf;
		if (qh->ep_type == UE_ISOCHRONOUS) {
			/* Isoc IN transactions - grab the offset of the iso_frame_desc into the URB transfer buffer */
			index = qtd->isoc_frame_index;
			ptr += qtd->urb->iso_descs[index].offset;
		} else {
			/* Need to increment by actual_length for interrupt IN */
			ptr += qtd->urb->actual_length;
		}

		for (i = 0; i < st->dma_info.index; i++) {
			len += st->dma_info.slot_len[i];
			dwc_memcpy(ptr, &blob->channel[num].index[i].buf[0], st->dma_info.slot_len[i]);
			ptr += st->dma_info.slot_len[i];
		}
		return len;
	} else {
		/* OUT endpoints - nothing to do. */
		return -1;
	}

}