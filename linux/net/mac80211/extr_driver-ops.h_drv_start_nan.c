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
struct cfg80211_nan_conf {int dummy; } ;
struct TYPE_2__ {int (* start_nan ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cfg80211_nan_conf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  check_sdata_in_driver (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cfg80211_nan_conf*) ; 
 int /*<<< orphan*/  trace_drv_return_int (struct ieee80211_local*,int) ; 
 int /*<<< orphan*/  trace_drv_start_nan (struct ieee80211_local*,struct ieee80211_sub_if_data*,struct cfg80211_nan_conf*) ; 

__attribute__((used)) static inline int drv_start_nan(struct ieee80211_local *local,
				struct ieee80211_sub_if_data *sdata,
				struct cfg80211_nan_conf *conf)
{
	int ret;

	might_sleep();
	check_sdata_in_driver(sdata);

	trace_drv_start_nan(local, sdata, conf);
	ret = local->ops->start_nan(&local->hw, &sdata->vif, conf);
	trace_drv_return_int(local, ret);
	return ret;
}