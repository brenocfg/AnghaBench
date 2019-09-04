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
struct ieee80211_sub_if_data {int /*<<< orphan*/  vif; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_et_stats ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ethtool_stats*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ethtool_stats*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_drv_get_et_stats (struct ieee80211_local*) ; 
 int /*<<< orphan*/  trace_drv_return_void (struct ieee80211_local*) ; 

__attribute__((used)) static inline void drv_get_et_stats(struct ieee80211_sub_if_data *sdata,
				    struct ethtool_stats *stats,
				    u64 *data)
{
	struct ieee80211_local *local = sdata->local;
	if (local->ops->get_et_stats) {
		trace_drv_get_et_stats(local);
		local->ops->get_et_stats(&local->hw, &sdata->vif, stats, data);
		trace_drv_return_void(local);
	}
}