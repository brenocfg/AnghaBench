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
struct wb_domain {unsigned long dirty_limit; } ;
struct dirty_throttle_control {unsigned long thresh; int /*<<< orphan*/  dirty; } ;

/* Variables and functions */
 struct wb_domain* dtc_dom (struct dirty_throttle_control*) ; 
 unsigned long max (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_dirty_limit(struct dirty_throttle_control *dtc)
{
	struct wb_domain *dom = dtc_dom(dtc);
	unsigned long thresh = dtc->thresh;
	unsigned long limit = dom->dirty_limit;

	/*
	 * Follow up in one step.
	 */
	if (limit < thresh) {
		limit = thresh;
		goto update;
	}

	/*
	 * Follow down slowly. Use the higher one as the target, because thresh
	 * may drop below dirty. This is exactly the reason to introduce
	 * dom->dirty_limit which is guaranteed to lie above the dirty pages.
	 */
	thresh = max(thresh, dtc->dirty);
	if (limit > thresh) {
		limit -= (limit - thresh) >> 5;
		goto update;
	}
	return;
update:
	dom->dirty_limit = limit;
}