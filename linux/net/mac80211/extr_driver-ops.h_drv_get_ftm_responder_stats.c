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
typedef  int u32 ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  vif; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct cfg80211_ftm_responder_stats {int dummy; } ;
struct TYPE_2__ {int (* get_ftm_responder_stats ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cfg80211_ftm_responder_stats*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cfg80211_ftm_responder_stats*) ; 
 int /*<<< orphan*/  trace_drv_get_ftm_responder_stats (struct ieee80211_local*,struct ieee80211_sub_if_data*,struct cfg80211_ftm_responder_stats*) ; 

__attribute__((used)) static inline int
drv_get_ftm_responder_stats(struct ieee80211_local *local,
			    struct ieee80211_sub_if_data *sdata,
			    struct cfg80211_ftm_responder_stats *ftm_stats)
{
	u32 ret = -EOPNOTSUPP;

	if (local->ops->get_ftm_responder_stats)
		ret = local->ops->get_ftm_responder_stats(&local->hw,
							 &sdata->vif,
							 ftm_stats);
	trace_drv_get_ftm_responder_stats(local, sdata, ftm_stats);

	return ret;
}