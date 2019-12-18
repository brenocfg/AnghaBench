#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_pt_queue {int sel_start; size_t sel_idx; int /*<<< orphan*/  sel_timestamp; struct intel_pt* pt; } ;
struct intel_pt {int range_cnt; TYPE_1__* time_ranges; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; int /*<<< orphan*/  end; } ;

/* Variables and functions */

__attribute__((used)) static bool intel_pt_next_time(struct intel_pt_queue *ptq)
{
	struct intel_pt *pt = ptq->pt;

	if (ptq->sel_start) {
		/* Next time is an end time */
		ptq->sel_start = false;
		ptq->sel_timestamp = pt->time_ranges[ptq->sel_idx].end;
		return true;
	} else if (ptq->sel_idx + 1 < pt->range_cnt) {
		/* Next time is a start time */
		ptq->sel_start = true;
		ptq->sel_idx += 1;
		ptq->sel_timestamp = pt->time_ranges[ptq->sel_idx].start;
		return true;
	}

	/* No next time */
	return false;
}