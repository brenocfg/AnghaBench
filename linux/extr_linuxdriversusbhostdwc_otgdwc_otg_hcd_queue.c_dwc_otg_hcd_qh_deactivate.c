#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_13__ {int nak_frame; scalar_t__ sched_frame; scalar_t__ start_split_frame; scalar_t__ ep_type; scalar_t__ ep_is_in; int interval; int /*<<< orphan*/  qh_list_entry; int /*<<< orphan*/  qtd_list; scalar_t__ do_split; } ;
typedef  TYPE_2__ dwc_otg_qh_t ;
struct TYPE_14__ {int /*<<< orphan*/  periodic_sched_inactive; TYPE_1__* fiq_state; int /*<<< orphan*/  periodic_sched_ready; } ;
typedef  TYPE_3__ dwc_otg_hcd_t ;
struct TYPE_12__ {scalar_t__ next_sched_frame; } ;

/* Variables and functions */
 scalar_t__ DWC_CIRCLEQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_LIST_MOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ UE_ISOCHRONOUS ; 
 scalar_t__ dwc_frame_num_inc (scalar_t__,int) ; 
 scalar_t__ dwc_frame_num_le (scalar_t__,scalar_t__) ; 
 scalar_t__ dwc_otg_hcd_get_frame_number (TYPE_3__*) ; 
 int /*<<< orphan*/  dwc_otg_hcd_qh_add (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dwc_otg_hcd_qh_remove (TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ dwc_qh_is_non_per (TYPE_2__*) ; 
 scalar_t__ fiq_enable ; 
 scalar_t__ microframe_schedule ; 
 scalar_t__ nak_holdoff ; 

void dwc_otg_hcd_qh_deactivate(dwc_otg_hcd_t * hcd, dwc_otg_qh_t * qh,
			       int sched_next_periodic_split)
{
	if (dwc_qh_is_non_per(qh)) {
		dwc_otg_hcd_qh_remove(hcd, qh);
		if (!DWC_CIRCLEQ_EMPTY(&qh->qtd_list)) {
			/* Add back to inactive non-periodic schedule. */
			dwc_otg_hcd_qh_add(hcd, qh);
			//hcd->fiq_state->kick_np_queues = 1;
		} else {
			if(nak_holdoff && qh->do_split) {
				qh->nak_frame = 0xFFFF;
			}
		}
	} else {
		uint16_t frame_number = dwc_otg_hcd_get_frame_number(hcd);

		if (qh->do_split) {
			/* Schedule the next continuing periodic split transfer */
			if (sched_next_periodic_split) {

				qh->sched_frame = frame_number;

				if (dwc_frame_num_le(frame_number,
						     dwc_frame_num_inc
						     (qh->start_split_frame,
						      1))) {
					/*
					 * Allow one frame to elapse after start
					 * split microframe before scheduling
					 * complete split, but DONT if we are
					 * doing the next start split in the
					 * same frame for an ISOC out.
					 */
					if ((qh->ep_type != UE_ISOCHRONOUS) ||
					    (qh->ep_is_in != 0)) {
						qh->sched_frame =
						    dwc_frame_num_inc(qh->sched_frame, 1);
					}
				}
			} else {
				qh->sched_frame =
				    dwc_frame_num_inc(qh->start_split_frame,
						      qh->interval);
				if (dwc_frame_num_le
				    (qh->sched_frame, frame_number)) {
					qh->sched_frame = frame_number;
				}
				qh->sched_frame |= 0x7;
				qh->start_split_frame = qh->sched_frame;
			}
		} else {
			qh->sched_frame =
			    dwc_frame_num_inc(qh->sched_frame, qh->interval);
			if (dwc_frame_num_le(qh->sched_frame, frame_number)) {
				qh->sched_frame = frame_number;
			}
		}

		if (DWC_CIRCLEQ_EMPTY(&qh->qtd_list)) {
			dwc_otg_hcd_qh_remove(hcd, qh);
		} else {
			/*
			 * Remove from periodic_sched_queued and move to
			 * appropriate queue.
			 */
			if ((microframe_schedule && dwc_frame_num_le(qh->sched_frame, frame_number)) ||
			(!microframe_schedule && qh->sched_frame == frame_number)) {
				DWC_LIST_MOVE_HEAD(&hcd->periodic_sched_ready,
						   &qh->qh_list_entry);
			} else {
				if(fiq_enable && !dwc_frame_num_le(hcd->fiq_state->next_sched_frame, qh->sched_frame))
				{
					hcd->fiq_state->next_sched_frame = qh->sched_frame;
				}

				DWC_LIST_MOVE_HEAD
				    (&hcd->periodic_sched_inactive,
				     &qh->qh_list_entry);
			}
		}
	}
}