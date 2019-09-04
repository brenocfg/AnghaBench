#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_11__ {int xfersize; int pktcnt; } ;
struct TYPE_12__ {TYPE_2__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_3__ hctsiz_data_t ;
struct TYPE_13__ {int ssplit_out_xfer_count; } ;
typedef  TYPE_4__ dwc_otg_qtd_t ;
struct TYPE_14__ {int /*<<< orphan*/  hctsiz; } ;
typedef  TYPE_5__ dwc_otg_hc_regs_t ;
typedef  scalar_t__ dwc_otg_halt_status_e ;
struct TYPE_15__ {int xfer_len; int start_pkt_count; int max_packet; TYPE_1__* qh; scalar_t__ ep_is_in; } ;
typedef  TYPE_6__ dwc_hc_t ;
struct TYPE_10__ {scalar_t__ do_split; } ;

/* Variables and functions */
 scalar_t__ DWC_OTG_HC_XFER_COMPLETE ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t get_actual_xfer_length(dwc_hc_t * hc,
				       dwc_otg_hc_regs_t * hc_regs,
				       dwc_otg_qtd_t * qtd,
				       dwc_otg_halt_status_e halt_status,
				       int *short_read)
{
	hctsiz_data_t hctsiz;
	uint32_t length;

	if (short_read != NULL) {
		*short_read = 0;
	}
	hctsiz.d32 = DWC_READ_REG32(&hc_regs->hctsiz);

	if (halt_status == DWC_OTG_HC_XFER_COMPLETE) {
		if (hc->ep_is_in) {
			length = hc->xfer_len - hctsiz.b.xfersize;
			if (short_read != NULL) {
				*short_read = (hctsiz.b.xfersize != 0);
			}
		} else if (hc->qh->do_split) {
				//length = split_out_xfersize[hc->hc_num];
				length = qtd->ssplit_out_xfer_count;
		} else {
			length = hc->xfer_len;
		}
	} else {
		/*
		 * Must use the hctsiz.pktcnt field to determine how much data
		 * has been transferred. This field reflects the number of
		 * packets that have been transferred via the USB. This is
		 * always an integral number of packets if the transfer was
		 * halted before its normal completion. (Can't use the
		 * hctsiz.xfersize field because that reflects the number of
		 * bytes transferred via the AHB, not the USB).
		 */
		length =
		    (hc->start_pkt_count - hctsiz.b.pktcnt) * hc->max_packet;
	}

	return length;
}