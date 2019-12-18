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
struct intel_pt_queue {int sel_start; scalar_t__ sel_timestamp; scalar_t__ sel_idx; } ;
struct intel_pt {TYPE_1__* time_ranges; int /*<<< orphan*/  range_cnt; } ;
struct TYPE_2__ {scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */

__attribute__((used)) static void intel_pt_setup_time_range(struct intel_pt *pt,
				      struct intel_pt_queue *ptq)
{
	if (!pt->range_cnt)
		return;

	ptq->sel_timestamp = pt->time_ranges[0].start;
	ptq->sel_idx = 0;

	if (ptq->sel_timestamp) {
		ptq->sel_start = true;
	} else {
		ptq->sel_timestamp = pt->time_ranges[0].end;
		ptq->sel_start = false;
	}
}