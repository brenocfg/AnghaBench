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
struct ieee80211_channel {int dummy; } ;
typedef  enum ieee80211_roc_type { ____Placeholder_ieee80211_roc_type } ieee80211_roc_type ;
struct TYPE_2__ {int (* remain_on_channel ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ieee80211_channel*,unsigned int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  might_sleep () ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ieee80211_channel*,unsigned int,int) ; 
 int /*<<< orphan*/  trace_drv_remain_on_channel (struct ieee80211_local*,struct ieee80211_sub_if_data*,struct ieee80211_channel*,unsigned int,int) ; 
 int /*<<< orphan*/  trace_drv_return_int (struct ieee80211_local*,int) ; 

__attribute__((used)) static inline int drv_remain_on_channel(struct ieee80211_local *local,
					struct ieee80211_sub_if_data *sdata,
					struct ieee80211_channel *chan,
					unsigned int duration,
					enum ieee80211_roc_type type)
{
	int ret;

	might_sleep();

	trace_drv_remain_on_channel(local, sdata, chan, duration, type);
	ret = local->ops->remain_on_channel(&local->hw, &sdata->vif,
					    chan, duration, type);
	trace_drv_return_int(local, ret);

	return ret;
}