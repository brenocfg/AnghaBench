#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct dwc_otg_hcd_urb {int packet_count; int /*<<< orphan*/  error_count; TYPE_2__* iso_descs; int /*<<< orphan*/  actual_length; } ;
struct TYPE_8__ {scalar_t__ bblerr; scalar_t__ xacterr; scalar_t__ frmovrun; scalar_t__ xfercomp; } ;
struct TYPE_10__ {int d32; TYPE_1__ b; } ;
typedef  TYPE_3__ hcint_data_t ;
struct TYPE_11__ {struct dwc_otg_hcd_urb* urb; } ;
typedef  TYPE_4__ dwc_otg_qtd_t ;
struct TYPE_12__ {int interval; int /*<<< orphan*/  sched_frame; scalar_t__ ep_is_in; } ;
typedef  TYPE_5__ dwc_otg_qh_t ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;
struct TYPE_9__ {int status; scalar_t__ actual_length; } ;

/* Variables and functions */
 int DWC_E_COMMUNICATION ; 
 int DWC_E_NO_STREAM_RES ; 
 int DWC_E_OVERFLOW ; 
 int DWC_E_PROTOCOL ; 
 int /*<<< orphan*/  dwc_frame_num_inc (int /*<<< orphan*/ ,int) ; 

void dwc_otg_fiq_unmangle_isoc(dwc_otg_hcd_t *hcd, dwc_otg_qh_t *qh, dwc_otg_qtd_t *qtd, uint32_t num)
{
	struct dwc_otg_hcd_urb *dwc_urb = qtd->urb;
	int nr_frames = dwc_urb->packet_count;
	int i;
	hcint_data_t frame_hcint;

	for (i = 0; i < nr_frames; i++) {
		frame_hcint.d32 = dwc_urb->iso_descs[i].status;
		if (frame_hcint.b.xfercomp) {
			dwc_urb->iso_descs[i].status = 0;
			dwc_urb->actual_length += dwc_urb->iso_descs[i].actual_length;
		} else if (frame_hcint.b.frmovrun) {
			if (qh->ep_is_in)
				dwc_urb->iso_descs[i].status = -DWC_E_NO_STREAM_RES;
			else
				dwc_urb->iso_descs[i].status = -DWC_E_COMMUNICATION;
			dwc_urb->error_count++;
			dwc_urb->iso_descs[i].actual_length = 0;
		} else if (frame_hcint.b.xacterr) {
			dwc_urb->iso_descs[i].status = -DWC_E_PROTOCOL;
			dwc_urb->error_count++;
			dwc_urb->iso_descs[i].actual_length = 0;
		} else if (frame_hcint.b.bblerr) {
			dwc_urb->iso_descs[i].status = -DWC_E_OVERFLOW;
			dwc_urb->error_count++;
			dwc_urb->iso_descs[i].actual_length = 0;
		} else {
			/* Something went wrong */
			dwc_urb->iso_descs[i].status = -1;
			dwc_urb->iso_descs[i].actual_length = 0;
			dwc_urb->error_count++;
		}
	}
	qh->sched_frame = dwc_frame_num_inc(qh->sched_frame, qh->interval * (nr_frames - 1));

	//printk_ratelimited(KERN_INFO "%s: HS isochronous of %d/%d frames with %d errors complete\n",
	//			__FUNCTION__, i, dwc_urb->packet_count, dwc_urb->error_count);
}