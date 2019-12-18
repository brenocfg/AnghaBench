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
typedef  int /*<<< orphan*/  u64 ;
struct wiphy {int dummy; } ;
struct cfg80211_sched_scan_request {int report_results; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  sched_scan_res_wk; } ;

/* Variables and functions */
 struct cfg80211_sched_scan_request* cfg80211_find_sched_scan_req (struct cfg80211_registered_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  trace_cfg80211_sched_scan_results (struct wiphy*,int /*<<< orphan*/ ) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (struct wiphy*) ; 

void cfg80211_sched_scan_results(struct wiphy *wiphy, u64 reqid)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wiphy);
	struct cfg80211_sched_scan_request *request;

	trace_cfg80211_sched_scan_results(wiphy, reqid);
	/* ignore if we're not scanning */

	rcu_read_lock();
	request = cfg80211_find_sched_scan_req(rdev, reqid);
	if (request) {
		request->report_results = true;
		queue_work(cfg80211_wq, &rdev->sched_scan_res_wk);
	}
	rcu_read_unlock();
}