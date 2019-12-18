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

/* Variables and functions */
 int /*<<< orphan*/  cfg80211_sched_scan_stopped_rtnl (struct wiphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

void cfg80211_sched_scan_stopped(struct wiphy *wiphy, u64 reqid)
{
	rtnl_lock();
	cfg80211_sched_scan_stopped_rtnl(wiphy, reqid);
	rtnl_unlock();
}