#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_9__ ;
typedef  struct TYPE_47__   TYPE_8__ ;
typedef  struct TYPE_46__   TYPE_7__ ;
typedef  struct TYPE_45__   TYPE_6__ ;
typedef  struct TYPE_44__   TYPE_5__ ;
typedef  struct TYPE_43__   TYPE_4__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_22__ ;
typedef  struct TYPE_39__   TYPE_21__ ;
typedef  struct TYPE_38__   TYPE_20__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_19__ ;
typedef  struct TYPE_35__   TYPE_18__ ;
typedef  struct TYPE_34__   TYPE_17__ ;
typedef  struct TYPE_33__   TYPE_16__ ;
typedef  struct TYPE_32__   TYPE_15__ ;
typedef  struct TYPE_31__   TYPE_14__ ;
typedef  struct TYPE_30__   TYPE_13__ ;
typedef  struct TYPE_29__   TYPE_12__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
struct TYPE_31__ {int mps; scalar_t__ epdir; int oddfrm; int multicnt; int chen; scalar_t__ lspddev; int /*<<< orphan*/  eptype; int /*<<< orphan*/  epnum; int /*<<< orphan*/  devaddr; } ;
struct TYPE_30__ {size_t d32; TYPE_14__ b; } ;
struct TYPE_44__ {int chhltd; } ;
struct TYPE_45__ {size_t d32; TYPE_5__ b; } ;
struct TYPE_48__ {size_t d32; } ;
struct TYPE_46__ {size_t d32; } ;
struct TYPE_28__ {int pktcnt; int xfersize; void* pid; } ;
struct TYPE_29__ {size_t d32; TYPE_11__ b; } ;
struct TYPE_27__ {int /*<<< orphan*/  stride; struct dwc_otg_hcd_iso_packet_desc* iso_desc; int /*<<< orphan*/  nrframes; } ;
struct fiq_channel_state {scalar_t__ fsm; int uframe_sleeps; TYPE_13__ hcchar_copy; TYPE_6__ hcintmsk_copy; TYPE_9__ hcdma_copy; TYPE_7__ hcsplt_copy; TYPE_12__ hctsiz_copy; TYPE_10__ hs_isoc_info; scalar_t__ nr_errors; } ;
struct dwc_otg_hcd_iso_packet_desc {int length; scalar_t__ offset; } ;
struct TYPE_41__ {scalar_t__ frrem; } ;
struct TYPE_32__ {TYPE_2__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_15__ hfnum_data_t ;
struct TYPE_33__ {scalar_t__ d32; } ;
typedef  TYPE_16__ hcdma_data_t ;
struct TYPE_34__ {TYPE_8__* urb; } ;
typedef  TYPE_17__ dwc_otg_qtd_t ;
struct TYPE_35__ {int /*<<< orphan*/  interval; int /*<<< orphan*/  qtd_list; TYPE_21__* channel; } ;
typedef  TYPE_18__ dwc_otg_qh_t ;
struct TYPE_36__ {TYPE_22__* fiq_state; TYPE_4__* core_if; } ;
typedef  TYPE_19__ dwc_otg_hcd_t ;
struct TYPE_38__ {int /*<<< orphan*/  hcchar; int /*<<< orphan*/  hcintmsk; int /*<<< orphan*/  hcdma; int /*<<< orphan*/  hcsplt; int /*<<< orphan*/  hctsiz; } ;
typedef  TYPE_20__ dwc_otg_hc_regs_t ;
struct TYPE_39__ {size_t hc_num; int max_packet; scalar_t__ ep_is_in; int /*<<< orphan*/  ep_type; int /*<<< orphan*/  ep_num; int /*<<< orphan*/  dev_addr; } ;
typedef  TYPE_21__ dwc_hc_t ;
struct TYPE_47__ {size_t dma; int /*<<< orphan*/  packet_count; int /*<<< orphan*/  iso_descs; } ;
struct TYPE_43__ {TYPE_3__* host_if; } ;
struct TYPE_42__ {TYPE_1__* host_global_regs; TYPE_20__** hc_regs; } ;
struct TYPE_40__ {int /*<<< orphan*/  lock; struct fiq_channel_state* channel; } ;
struct TYPE_37__ {int /*<<< orphan*/  hfnum; } ;

/* Variables and functions */
 TYPE_17__* DWC_CIRCLEQ_FIRST (int /*<<< orphan*/ *) ; 
 void* DWC_PID_DATA0 ; 
 void* DWC_PID_DATA1 ; 
 void* DWC_PID_DATA2 ; 
 void* DWC_PID_MDATA ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  FIQDBG_INT ; 
 scalar_t__ FIQ_HS_ISOC_SLEEPING ; 
 scalar_t__ FIQ_HS_ISOC_TURBO ; 
 scalar_t__ FIQ_PASSTHROUGH ; 
 scalar_t__ PERIODIC_FRREM_BACKOFF ; 
 int dwc_otg_hcd_get_frame_number (TYPE_19__*) ; 
 int /*<<< orphan*/  fiq_fsm_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fiq_fsm_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fiq_print (int /*<<< orphan*/ ,TYPE_22__*,char*,size_t) ; 
 int /*<<< orphan*/  local_fiq_disable () ; 
 int /*<<< orphan*/  local_fiq_enable () ; 
 int /*<<< orphan*/  mb () ; 

int fiq_fsm_queue_isoc_transaction(dwc_otg_hcd_t *hcd, dwc_otg_qh_t *qh)
{
	dwc_hc_t *hc = qh->channel;
	dwc_otg_hc_regs_t *hc_regs = hcd->core_if->host_if->hc_regs[hc->hc_num];
	dwc_otg_qtd_t *qtd = DWC_CIRCLEQ_FIRST(&qh->qtd_list);
	int frame;
	struct fiq_channel_state *st = &hcd->fiq_state->channel[hc->hc_num];
	int xfer_len, nrpackets;
	hcdma_data_t hcdma;
	hfnum_data_t hfnum;

	if (st->fsm != FIQ_PASSTHROUGH)
		return 0;

	st->nr_errors = 0;

	st->hcchar_copy.d32 = 0;
	st->hcchar_copy.b.mps = hc->max_packet;
	st->hcchar_copy.b.epdir = hc->ep_is_in;
	st->hcchar_copy.b.devaddr = hc->dev_addr;
	st->hcchar_copy.b.epnum = hc->ep_num;
	st->hcchar_copy.b.eptype = hc->ep_type;

	st->hcintmsk_copy.b.chhltd = 1;

	frame = dwc_otg_hcd_get_frame_number(hcd);
	st->hcchar_copy.b.oddfrm = (frame & 0x1) ? 0 : 1;

	st->hcchar_copy.b.lspddev = 0;
	/* Enable the channel later as a final register write. */

	st->hcsplt_copy.d32 = 0;

	st->hs_isoc_info.iso_desc = (struct dwc_otg_hcd_iso_packet_desc *) &qtd->urb->iso_descs;
	st->hs_isoc_info.nrframes = qtd->urb->packet_count;
	/* grab the next DMA address offset from the array */
	st->hcdma_copy.d32 = qtd->urb->dma;
	hcdma.d32 = st->hcdma_copy.d32 + st->hs_isoc_info.iso_desc[0].offset;

	/* We need to set multi_count. This is a bit tricky - has to be set per-transaction as
	 * the core needs to be told to send the correct number. Caution: for IN transfers,
	 * this is always set to the maximum size of the endpoint. */
	xfer_len = st->hs_isoc_info.iso_desc[0].length;
	nrpackets = (xfer_len + st->hcchar_copy.b.mps - 1) / st->hcchar_copy.b.mps;
	if (nrpackets == 0)
		nrpackets = 1;
	st->hcchar_copy.b.multicnt = nrpackets;
	st->hctsiz_copy.b.pktcnt = nrpackets;

	/* Initial PID also needs to be set */
	if (st->hcchar_copy.b.epdir == 0) {
		st->hctsiz_copy.b.xfersize = xfer_len;
		switch (st->hcchar_copy.b.multicnt) {
		case 1:
			st->hctsiz_copy.b.pid = DWC_PID_DATA0;
			break;
		case 2:
		case 3:
			st->hctsiz_copy.b.pid = DWC_PID_MDATA;
			break;
		}

	} else {
		st->hctsiz_copy.b.xfersize = nrpackets * st->hcchar_copy.b.mps;
		switch (st->hcchar_copy.b.multicnt) {
		case 1:
			st->hctsiz_copy.b.pid = DWC_PID_DATA0;
			break;
		case 2:
			st->hctsiz_copy.b.pid = DWC_PID_DATA1;
			break;
		case 3:
			st->hctsiz_copy.b.pid = DWC_PID_DATA2;
			break;
		}
	}

	st->hs_isoc_info.stride = qh->interval;
	st->uframe_sleeps = 0;

	fiq_print(FIQDBG_INT, hcd->fiq_state, "FSMQ  %01d ", hc->hc_num);
	fiq_print(FIQDBG_INT, hcd->fiq_state, "%08x", st->hcchar_copy.d32);
	fiq_print(FIQDBG_INT, hcd->fiq_state, "%08x", st->hctsiz_copy.d32);
	fiq_print(FIQDBG_INT, hcd->fiq_state, "%08x", st->hcdma_copy.d32);
	hfnum.d32 = DWC_READ_REG32(&hcd->core_if->host_if->host_global_regs->hfnum);
	local_fiq_disable();
	fiq_fsm_spin_lock(&hcd->fiq_state->lock);
	DWC_WRITE_REG32(&hc_regs->hctsiz, st->hctsiz_copy.d32);
	DWC_WRITE_REG32(&hc_regs->hcsplt, st->hcsplt_copy.d32);
	DWC_WRITE_REG32(&hc_regs->hcdma, st->hcdma_copy.d32);
	DWC_WRITE_REG32(&hc_regs->hcchar, st->hcchar_copy.d32);
	DWC_WRITE_REG32(&hc_regs->hcintmsk, st->hcintmsk_copy.d32);
	if (hfnum.b.frrem < PERIODIC_FRREM_BACKOFF) {
		/* Prevent queueing near EOF1. Bad things happen if a periodic
		 * split transaction is queued very close to EOF. SOF interrupt handler
		 * will wake this channel at the next interrupt.
		 */
		st->fsm = FIQ_HS_ISOC_SLEEPING;
		st->uframe_sleeps = 1;
	} else {
		st->fsm = FIQ_HS_ISOC_TURBO;
		st->hcchar_copy.b.chen = 1;
		DWC_WRITE_REG32(&hc_regs->hcchar, st->hcchar_copy.d32);
	}
	mb();
	st->hcchar_copy.b.chen = 0;
	fiq_fsm_spin_unlock(&hcd->fiq_state->lock);
	local_fiq_enable();
	return 0;
}