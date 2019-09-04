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
typedef  int /*<<< orphan*/  u64 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct ieee80211_local {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  sched_scan_stop; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ieee80211_request_sched_scan_stop (struct ieee80211_local*) ; 
 struct ieee80211_local* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int
ieee80211_sched_scan_stop(struct wiphy *wiphy, struct net_device *dev,
			  u64 reqid)
{
	struct ieee80211_local *local = wiphy_priv(wiphy);

	if (!local->ops->sched_scan_stop)
		return -EOPNOTSUPP;

	return ieee80211_request_sched_scan_stop(local);
}