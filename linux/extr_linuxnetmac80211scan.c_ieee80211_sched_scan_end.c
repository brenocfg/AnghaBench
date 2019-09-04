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
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {TYPE_1__ hw; int /*<<< orphan*/  mtx; int /*<<< orphan*/  sched_scan_req; int /*<<< orphan*/  sched_scan_sdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_sched_scan_stopped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 

void ieee80211_sched_scan_end(struct ieee80211_local *local)
{
	mutex_lock(&local->mtx);

	if (!rcu_access_pointer(local->sched_scan_sdata)) {
		mutex_unlock(&local->mtx);
		return;
	}

	RCU_INIT_POINTER(local->sched_scan_sdata, NULL);

	/* If sched scan was aborted by the driver. */
	RCU_INIT_POINTER(local->sched_scan_req, NULL);

	mutex_unlock(&local->mtx);

	cfg80211_sched_scan_stopped(local->hw.wiphy, 0);
}