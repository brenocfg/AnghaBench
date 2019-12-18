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
struct ieee80211_sub_if_data {int /*<<< orphan*/  vif; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct cfg80211_chan_def {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* channel_switch_beacon ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cfg80211_chan_def*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  trace_drv_channel_switch_beacon (struct ieee80211_local*,struct ieee80211_sub_if_data*,struct cfg80211_chan_def*) ; 

__attribute__((used)) static inline void
drv_channel_switch_beacon(struct ieee80211_sub_if_data *sdata,
			  struct cfg80211_chan_def *chandef)
{
	struct ieee80211_local *local = sdata->local;

	if (local->ops->channel_switch_beacon) {
		trace_drv_channel_switch_beacon(local, sdata, chandef);
		local->ops->channel_switch_beacon(&local->hw, &sdata->vif,
						  chandef);
	}
}