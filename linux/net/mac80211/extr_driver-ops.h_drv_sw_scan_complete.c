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
struct TYPE_2__ {int /*<<< orphan*/  (* sw_scan_complete ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_drv_return_void (struct ieee80211_local*) ; 
 int /*<<< orphan*/  trace_drv_sw_scan_complete (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 

__attribute__((used)) static inline void drv_sw_scan_complete(struct ieee80211_local *local,
					struct ieee80211_sub_if_data *sdata)
{
	might_sleep();

	trace_drv_sw_scan_complete(local, sdata);
	if (local->ops->sw_scan_complete)
		local->ops->sw_scan_complete(&local->hw, &sdata->vif);
	trace_drv_return_void(local);
}