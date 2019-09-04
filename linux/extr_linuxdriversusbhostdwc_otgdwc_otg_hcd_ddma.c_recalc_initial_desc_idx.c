#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_6__ {int sched_frame; int /*<<< orphan*/  td_last; int /*<<< orphan*/  td_first; scalar_t__ channel; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */
 int MAX_FRLIST_EN_NUM ; 
 void* calc_starting_frame (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int frame_incr_val (TYPE_1__*) ; 
 int frame_list_idx (int) ; 
 int /*<<< orphan*/  frame_to_desc_idx (TYPE_1__*,int) ; 

__attribute__((used)) static uint8_t recalc_initial_desc_idx(dwc_otg_hcd_t * hcd, dwc_otg_qh_t * qh)
{
	uint16_t frame = 0, fr_idx, fr_idx_tmp;
	uint8_t skip_frames = 0;
	/*
	 * With current ISOC processing algorithm the channel is being
	 * released when no more QTDs in the list(qh->ntd == 0).
	 * Thus this function is called only when qh->ntd == 0 and qh->channel == 0.
	 *
	 * So qh->channel != NULL branch is not used and just not removed from the
	 * source file. It is required for another possible approach which is,
	 * do not disable and release the channel when ISOC session completed,
	 * just move QH to inactive schedule until new QTD arrives.
	 * On new QTD, the QH moved back to 'ready' schedule,
	 * starting frame and therefore starting desc_index are recalculated.
	 * In this case channel is released only on ep_disable.
	 */

	/* Calculate starting descriptor index. For INTERRUPT endpoint it is always 0. */
	if (qh->channel) {
		frame = calc_starting_frame(hcd, qh, &skip_frames);
		/*
		 * Calculate initial descriptor index based on FrameList current bitmap
		 * and servicing period.
		 */
		fr_idx_tmp = frame_list_idx(frame);
		fr_idx =
		    (MAX_FRLIST_EN_NUM + frame_list_idx(qh->sched_frame) -
		     fr_idx_tmp)
		    % frame_incr_val(qh);
		fr_idx = (fr_idx + fr_idx_tmp) % MAX_FRLIST_EN_NUM;
	} else {
		qh->sched_frame = calc_starting_frame(hcd, qh, &skip_frames);
		fr_idx = frame_list_idx(qh->sched_frame);
	}

	qh->td_first = qh->td_last = frame_to_desc_idx(qh, fr_idx);

	return skip_frames;
}