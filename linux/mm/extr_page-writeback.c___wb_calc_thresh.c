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
typedef  long u64 ;
struct wb_domain {int /*<<< orphan*/  completions; } ;
struct dirty_throttle_control {unsigned long thresh; int /*<<< orphan*/  wb; int /*<<< orphan*/  wb_completions; } ;

/* Variables and functions */
 int bdi_min_ratio ; 
 int /*<<< orphan*/  do_div (long,long) ; 
 struct wb_domain* dtc_dom (struct dirty_throttle_control*) ; 
 int /*<<< orphan*/  fprop_fraction_percpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long*,long*) ; 
 int /*<<< orphan*/  wb_min_max_ratio (int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 

__attribute__((used)) static unsigned long __wb_calc_thresh(struct dirty_throttle_control *dtc)
{
	struct wb_domain *dom = dtc_dom(dtc);
	unsigned long thresh = dtc->thresh;
	u64 wb_thresh;
	long numerator, denominator;
	unsigned long wb_min_ratio, wb_max_ratio;

	/*
	 * Calculate this BDI's share of the thresh ratio.
	 */
	fprop_fraction_percpu(&dom->completions, dtc->wb_completions,
			      &numerator, &denominator);

	wb_thresh = (thresh * (100 - bdi_min_ratio)) / 100;
	wb_thresh *= numerator;
	do_div(wb_thresh, denominator);

	wb_min_max_ratio(dtc->wb, &wb_min_ratio, &wb_max_ratio);

	wb_thresh += (thresh * wb_min_ratio) / 100;
	if (wb_thresh > (thresh * wb_max_ratio) / 100)
		wb_thresh = thresh * wb_max_ratio / 100;

	return wb_thresh;
}