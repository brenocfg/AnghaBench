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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  vif; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct cfg80211_chan_def {int dummy; } ;
struct TYPE_2__ {int (* tdls_channel_switch ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ieee80211_sta*,int /*<<< orphan*/ ,struct cfg80211_chan_def*,struct sk_buff*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  check_sdata_in_driver (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ieee80211_sta*,int /*<<< orphan*/ ,struct cfg80211_chan_def*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_drv_return_int (struct ieee80211_local*,int) ; 
 int /*<<< orphan*/  trace_drv_tdls_channel_switch (struct ieee80211_local*,struct ieee80211_sub_if_data*,struct ieee80211_sta*,int /*<<< orphan*/ ,struct cfg80211_chan_def*) ; 

__attribute__((used)) static inline int
drv_tdls_channel_switch(struct ieee80211_local *local,
			struct ieee80211_sub_if_data *sdata,
			struct ieee80211_sta *sta, u8 oper_class,
			struct cfg80211_chan_def *chandef,
			struct sk_buff *tmpl_skb, u32 ch_sw_tm_ie)
{
	int ret;

	might_sleep();
	if (!check_sdata_in_driver(sdata))
		return -EIO;

	if (!local->ops->tdls_channel_switch)
		return -EOPNOTSUPP;

	trace_drv_tdls_channel_switch(local, sdata, sta, oper_class, chandef);
	ret = local->ops->tdls_channel_switch(&local->hw, &sdata->vif, sta,
					      oper_class, chandef, tmpl_skb,
					      ch_sw_tm_ie);
	trace_drv_return_int(local, ret);
	return ret;
}