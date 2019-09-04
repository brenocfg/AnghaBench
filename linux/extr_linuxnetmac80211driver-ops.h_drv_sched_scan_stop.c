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
struct ieee80211_sub_if_data {int /*<<< orphan*/  vif; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* sched_scan_stop ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  check_sdata_in_driver (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_drv_return_int (struct ieee80211_local*,int) ; 
 int /*<<< orphan*/  trace_drv_sched_scan_stop (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 

__attribute__((used)) static inline int drv_sched_scan_stop(struct ieee80211_local *local,
				      struct ieee80211_sub_if_data *sdata)
{
	int ret;

	might_sleep();

	if (!check_sdata_in_driver(sdata))
		return -EIO;

	trace_drv_sched_scan_stop(local, sdata);
	ret = local->ops->sched_scan_stop(&local->hw, &sdata->vif);
	trace_drv_return_int(local, ret);

	return ret;
}