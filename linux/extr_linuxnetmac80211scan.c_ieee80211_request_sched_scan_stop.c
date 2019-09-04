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
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_local {int /*<<< orphan*/  mtx; int /*<<< orphan*/  sched_scan_sdata; int /*<<< orphan*/  sched_scan_req; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  sched_scan_stop; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drv_sched_scan_stop (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ieee80211_sub_if_data* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ieee80211_request_sched_scan_stop(struct ieee80211_local *local)
{
	struct ieee80211_sub_if_data *sched_scan_sdata;
	int ret = -ENOENT;

	mutex_lock(&local->mtx);

	if (!local->ops->sched_scan_stop) {
		ret = -ENOTSUPP;
		goto out;
	}

	/* We don't want to restart sched scan anymore. */
	RCU_INIT_POINTER(local->sched_scan_req, NULL);

	sched_scan_sdata = rcu_dereference_protected(local->sched_scan_sdata,
						lockdep_is_held(&local->mtx));
	if (sched_scan_sdata) {
		ret = drv_sched_scan_stop(local, sched_scan_sdata);
		if (!ret)
			RCU_INIT_POINTER(local->sched_scan_sdata, NULL);
	}
out:
	mutex_unlock(&local->mtx);

	return ret;
}