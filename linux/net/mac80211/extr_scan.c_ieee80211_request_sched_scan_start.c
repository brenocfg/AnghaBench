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
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  mtx; int /*<<< orphan*/  sched_scan_sdata; } ;
struct cfg80211_sched_scan_request {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int __ieee80211_request_sched_scan_start (struct ieee80211_sub_if_data*,struct cfg80211_sched_scan_request*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 

int ieee80211_request_sched_scan_start(struct ieee80211_sub_if_data *sdata,
				       struct cfg80211_sched_scan_request *req)
{
	struct ieee80211_local *local = sdata->local;
	int ret;

	mutex_lock(&local->mtx);

	if (rcu_access_pointer(local->sched_scan_sdata)) {
		mutex_unlock(&local->mtx);
		return -EBUSY;
	}

	ret = __ieee80211_request_sched_scan_start(sdata, req);

	mutex_unlock(&local->mtx);
	return ret;
}