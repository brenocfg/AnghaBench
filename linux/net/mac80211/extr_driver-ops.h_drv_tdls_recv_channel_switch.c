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
struct ieee80211_tdls_ch_sw_params {int dummy; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  vif; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tdls_recv_channel_switch ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ieee80211_tdls_ch_sw_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ieee80211_tdls_ch_sw_params*) ; 
 int /*<<< orphan*/  trace_drv_return_void (struct ieee80211_local*) ; 
 int /*<<< orphan*/  trace_drv_tdls_recv_channel_switch (struct ieee80211_local*,struct ieee80211_sub_if_data*,struct ieee80211_tdls_ch_sw_params*) ; 

__attribute__((used)) static inline void
drv_tdls_recv_channel_switch(struct ieee80211_local *local,
			     struct ieee80211_sub_if_data *sdata,
			     struct ieee80211_tdls_ch_sw_params *params)
{
	trace_drv_tdls_recv_channel_switch(local, sdata, params);
	if (local->ops->tdls_recv_channel_switch)
		local->ops->tdls_recv_channel_switch(&local->hw, &sdata->vif,
						     params);
	trace_drv_return_void(local);
}