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
struct cfg80211_registered_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  __cfg80211_stop_sched_scan (struct cfg80211_registered_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_cfg80211_sched_scan_stopped (struct wiphy*,int /*<<< orphan*/ ) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (struct wiphy*) ; 

void cfg80211_sched_scan_stopped_rtnl(struct wiphy *wiphy, u64 reqid)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wiphy);

	ASSERT_RTNL();

	trace_cfg80211_sched_scan_stopped(wiphy, reqid);

	__cfg80211_stop_sched_scan(rdev, reqid, true);
}