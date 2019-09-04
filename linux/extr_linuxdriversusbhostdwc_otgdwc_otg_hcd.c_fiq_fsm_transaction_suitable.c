#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* urb; } ;
typedef  TYPE_2__ dwc_otg_qtd_t ;
struct TYPE_9__ {int ep_type; int /*<<< orphan*/  qtd_list; scalar_t__ do_split; } ;
typedef  TYPE_3__ dwc_otg_qh_t ;
struct TYPE_10__ {int packet_count; int dma; TYPE_1__* iso_descs; } ;
typedef  TYPE_4__ dwc_otg_hcd_urb_t ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;
typedef  int dwc_dma_t ;
struct TYPE_7__ {int offset; } ;

/* Variables and functions */
 TYPE_2__* DWC_CIRCLEQ_FIRST (int /*<<< orphan*/ *) ; 
#define  UE_BULK 131 
#define  UE_CONTROL 130 
#define  UE_INTERRUPT 129 
#define  UE_ISOCHRONOUS 128 
 int fiq_fsm_mask ; 

int fiq_fsm_transaction_suitable(dwc_otg_hcd_t *hcd, dwc_otg_qh_t *qh)
{
	if (qh->do_split) {
		switch (qh->ep_type) {
		case UE_CONTROL:
		case UE_BULK:
			if (fiq_fsm_mask & (1 << 0))
				return 1;
			break;
		case UE_INTERRUPT:
		case UE_ISOCHRONOUS:
			if (fiq_fsm_mask & (1 << 1))
				return 1;
			break;
		default:
			break;
		}
	} else if (qh->ep_type == UE_ISOCHRONOUS) {
		if (fiq_fsm_mask & (1 << 2)) {
			/* ISOCH support. We test for compatibility:
			 * - DWORD aligned buffers
			 * - Must be at least 2 transfers (otherwise pointless to use the FIQ)
			 * If yes, then the fsm enqueue function will handle the state machine setup.
			 */
			dwc_otg_qtd_t *qtd = DWC_CIRCLEQ_FIRST(&qh->qtd_list);
			dwc_otg_hcd_urb_t *urb = qtd->urb;
			dwc_dma_t ptr;
			int i;

			if (urb->packet_count < 2)
				return 0;
			for (i = 0; i < urb->packet_count; i++) {
				ptr = urb->dma + urb->iso_descs[i].offset;
				if (ptr & 0x3)
					return 0;
			}
			return 1;
		}
	}
	return 0;
}