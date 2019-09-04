#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct dwc_otg_hcd_iso_packet_desc {scalar_t__ actual_length; scalar_t__ offset; scalar_t__ length; scalar_t__ status; } ;
typedef  int int32_t ;
struct TYPE_18__ {size_t isoc_frame_index; scalar_t__ isoc_split_offset; TYPE_7__* urb; scalar_t__ complete_split; } ;
typedef  TYPE_3__ dwc_otg_qtd_t ;
struct TYPE_19__ {TYPE_2__* fops; } ;
typedef  TYPE_4__ dwc_otg_hcd_t ;
typedef  int /*<<< orphan*/  dwc_otg_hc_regs_t ;
struct TYPE_20__ {TYPE_1__* qh; scalar_t__ align_buff; } ;
typedef  TYPE_5__ dwc_hc_t ;
struct TYPE_21__ {scalar_t__ buf; size_t packet_count; int /*<<< orphan*/  priv; struct dwc_otg_hcd_iso_packet_desc* iso_descs; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* complete ) (TYPE_4__*,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {int /*<<< orphan*/  dw_align_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_OTG_HC_XFER_COMPLETE ; 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_NO_HALT_STATUS ; 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_URB_COMPLETE ; 
 int /*<<< orphan*/  dwc_memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_actual_xfer_length (TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_channel (TYPE_4__*,TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t handle_xfercomp_isoc_split_in(dwc_otg_hcd_t * hcd,
					     dwc_hc_t * hc,
					     dwc_otg_hc_regs_t * hc_regs,
					     dwc_otg_qtd_t * qtd)
{
	uint32_t len;
	struct dwc_otg_hcd_iso_packet_desc *frame_desc;
	frame_desc = &qtd->urb->iso_descs[qtd->isoc_frame_index];

	len = get_actual_xfer_length(hc, hc_regs, qtd,
				     DWC_OTG_HC_XFER_COMPLETE, NULL);

	if (!len) {
		qtd->complete_split = 0;
		qtd->isoc_split_offset = 0;
		return 0;
	}
	frame_desc->actual_length += len;

	if (hc->align_buff && len)
		dwc_memcpy(qtd->urb->buf + frame_desc->offset +
			   qtd->isoc_split_offset, hc->qh->dw_align_buf, len);
	qtd->isoc_split_offset += len;

	if (frame_desc->length == frame_desc->actual_length) {
		frame_desc->status = 0;
		qtd->isoc_frame_index++;
		qtd->complete_split = 0;
		qtd->isoc_split_offset = 0;
	}

	if (qtd->isoc_frame_index == qtd->urb->packet_count) {
		hcd->fops->complete(hcd, qtd->urb->priv, qtd->urb, 0);
		release_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_URB_COMPLETE);
	} else {
		release_channel(hcd, hc, qtd, DWC_OTG_HC_XFER_NO_HALT_STATUS);
	}

	return 1;		/* Indicates that channel released */
}