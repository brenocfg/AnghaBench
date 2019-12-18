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
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_sta {int dummy; } ;
struct sta_info {struct ieee80211_sta sta; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  vif; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct ieee80211_key_conf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_tkip_key ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ieee80211_key_conf*,struct ieee80211_sta*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  check_sdata_in_driver (struct ieee80211_sub_if_data*) ; 
 struct ieee80211_sub_if_data* get_bss_sdata (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ieee80211_key_conf*,struct ieee80211_sta*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_drv_return_void (struct ieee80211_local*) ; 
 int /*<<< orphan*/  trace_drv_update_tkip_key (struct ieee80211_local*,struct ieee80211_sub_if_data*,struct ieee80211_key_conf*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void drv_update_tkip_key(struct ieee80211_local *local,
				       struct ieee80211_sub_if_data *sdata,
				       struct ieee80211_key_conf *conf,
				       struct sta_info *sta, u32 iv32,
				       u16 *phase1key)
{
	struct ieee80211_sta *ista = NULL;

	if (sta)
		ista = &sta->sta;

	sdata = get_bss_sdata(sdata);
	if (!check_sdata_in_driver(sdata))
		return;

	trace_drv_update_tkip_key(local, sdata, conf, ista, iv32);
	if (local->ops->update_tkip_key)
		local->ops->update_tkip_key(&local->hw, &sdata->vif, conf,
					    ista, iv32, phase1key);
	trace_drv_return_void(local);
}