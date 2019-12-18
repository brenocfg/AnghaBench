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
struct wb_domain {unsigned long dirty_limit_tstamp; int /*<<< orphan*/  lock; } ;
struct dirty_throttle_control {int dummy; } ;

/* Variables and functions */
 scalar_t__ BANDWIDTH_INTERVAL ; 
 struct wb_domain* dtc_dom (struct dirty_throttle_control*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (unsigned long,scalar_t__) ; 
 scalar_t__ time_before (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  update_dirty_limit (struct dirty_throttle_control*) ; 

__attribute__((used)) static void domain_update_bandwidth(struct dirty_throttle_control *dtc,
				    unsigned long now)
{
	struct wb_domain *dom = dtc_dom(dtc);

	/*
	 * check locklessly first to optimize away locking for the most time
	 */
	if (time_before(now, dom->dirty_limit_tstamp + BANDWIDTH_INTERVAL))
		return;

	spin_lock(&dom->lock);
	if (time_after_eq(now, dom->dirty_limit_tstamp + BANDWIDTH_INTERVAL)) {
		update_dirty_limit(dtc);
		dom->dirty_limit_tstamp = now;
	}
	spin_unlock(&dom->lock);
}