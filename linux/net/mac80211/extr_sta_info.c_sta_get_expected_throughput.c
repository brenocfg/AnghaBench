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
struct sta_info {int /*<<< orphan*/  rate_ctrl_priv; struct ieee80211_sub_if_data* sdata; } ;
struct rate_control_ref {TYPE_1__* ops; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct ieee80211_local {struct rate_control_ref* rate_ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_expected_throughput ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_STA_RATE_CONTROL ; 
 int /*<<< orphan*/  drv_get_expected_throughput (struct ieee80211_local*,struct sta_info*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

u32 sta_get_expected_throughput(struct sta_info *sta)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	struct ieee80211_local *local = sdata->local;
	struct rate_control_ref *ref = NULL;
	u32 thr = 0;

	if (test_sta_flag(sta, WLAN_STA_RATE_CONTROL))
		ref = local->rate_ctrl;

	/* check if the driver has a SW RC implementation */
	if (ref && ref->ops->get_expected_throughput)
		thr = ref->ops->get_expected_throughput(sta->rate_ctrl_priv);
	else
		thr = drv_get_expected_throughput(local, sta);

	return thr;
}