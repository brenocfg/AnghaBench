#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u64 ;
struct intel_pt_queue {scalar_t__ timestamp; scalar_t__ sel_timestamp; int have_sample; int /*<<< orphan*/  switch_state; int /*<<< orphan*/  decoder; int /*<<< orphan*/  pt; scalar_t__ sync_switch; scalar_t__ sel_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_PT_SS_NOT_TRACING ; 
 int /*<<< orphan*/  INTEL_PT_SS_UNKNOWN ; 
 int intel_pt_fast_forward (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  intel_pt_next_tid (int /*<<< orphan*/ ,struct intel_pt_queue*) ; 
 int /*<<< orphan*/  intel_pt_next_time (struct intel_pt_queue*) ; 

__attribute__((used)) static int intel_pt_time_filter(struct intel_pt_queue *ptq, u64 *ff_timestamp)
{
	int err;

	while (1) {
		if (ptq->sel_start) {
			if (ptq->timestamp >= ptq->sel_timestamp) {
				/* After start time, so consider next time */
				intel_pt_next_time(ptq);
				if (!ptq->sel_timestamp) {
					/* No end time */
					return 0;
				}
				/* Check against end time */
				continue;
			}
			/* Before start time, so fast forward */
			ptq->have_sample = false;
			if (ptq->sel_timestamp > *ff_timestamp) {
				if (ptq->sync_switch) {
					intel_pt_next_tid(ptq->pt, ptq);
					ptq->switch_state = INTEL_PT_SS_UNKNOWN;
				}
				*ff_timestamp = ptq->sel_timestamp;
				err = intel_pt_fast_forward(ptq->decoder,
							    ptq->sel_timestamp);
				if (err)
					return err;
			}
			return 0;
		} else if (ptq->timestamp > ptq->sel_timestamp) {
			/* After end time, so consider next time */
			if (!intel_pt_next_time(ptq)) {
				/* No next time range, so stop decoding */
				ptq->have_sample = false;
				ptq->switch_state = INTEL_PT_SS_NOT_TRACING;
				return 1;
			}
			/* Check against next start time */
			continue;
		} else {
			/* Before end time */
			return 0;
		}
	}
}