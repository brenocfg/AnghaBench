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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sub_if_data {struct ieee80211_vif vif; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush ) (int /*<<< orphan*/ *,struct ieee80211_vif*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  check_sdata_in_driver (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct ieee80211_vif*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_drv_flush (struct ieee80211_local*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_drv_return_void (struct ieee80211_local*) ; 

__attribute__((used)) static inline void drv_flush(struct ieee80211_local *local,
			     struct ieee80211_sub_if_data *sdata,
			     u32 queues, bool drop)
{
	struct ieee80211_vif *vif = sdata ? &sdata->vif : NULL;

	might_sleep();

	if (sdata && !check_sdata_in_driver(sdata))
		return;

	trace_drv_flush(local, queues, drop);
	if (local->ops->flush)
		local->ops->flush(&local->hw, vif, queues, drop);
	trace_drv_return_void(local);
}