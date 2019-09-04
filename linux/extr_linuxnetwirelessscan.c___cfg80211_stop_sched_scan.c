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
struct cfg80211_sched_scan_request {int dummy; } ;
struct cfg80211_registered_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOENT ; 
 struct cfg80211_sched_scan_request* cfg80211_find_sched_scan_req (struct cfg80211_registered_device*,int /*<<< orphan*/ ) ; 
 int cfg80211_stop_sched_scan_req (struct cfg80211_registered_device*,struct cfg80211_sched_scan_request*,int) ; 

int __cfg80211_stop_sched_scan(struct cfg80211_registered_device *rdev,
			       u64 reqid, bool driver_initiated)
{
	struct cfg80211_sched_scan_request *sched_scan_req;

	ASSERT_RTNL();

	sched_scan_req = cfg80211_find_sched_scan_req(rdev, reqid);
	if (!sched_scan_req)
		return -ENOENT;

	return cfg80211_stop_sched_scan_req(rdev, sched_scan_req,
					    driver_initiated);
}