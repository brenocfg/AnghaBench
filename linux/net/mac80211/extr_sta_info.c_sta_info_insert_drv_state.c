#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct sta_info {int sta_state; int uploaded; TYPE_3__ sta; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; } ;
struct ieee80211_local {TYPE_1__* ops; } ;
typedef  enum ieee80211_sta_state { ____Placeholder_ieee80211_sta_state } ieee80211_sta_state ;
struct TYPE_4__ {int /*<<< orphan*/  sta_add; } ;

/* Variables and functions */
 int IEEE80211_STA_NOTEXIST ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int drv_sta_state (struct ieee80211_local*,struct ieee80211_sub_if_data*,struct sta_info*,int,int) ; 
 int /*<<< orphan*/  sdata_info (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sta_info_insert_drv_state(struct ieee80211_local *local,
				     struct ieee80211_sub_if_data *sdata,
				     struct sta_info *sta)
{
	enum ieee80211_sta_state state;
	int err = 0;

	for (state = IEEE80211_STA_NOTEXIST; state < sta->sta_state; state++) {
		err = drv_sta_state(local, sdata, sta, state, state + 1);
		if (err)
			break;
	}

	if (!err) {
		/*
		 * Drivers using legacy sta_add/sta_remove callbacks only
		 * get uploaded set to true after sta_add is called.
		 */
		if (!local->ops->sta_add)
			sta->uploaded = true;
		return 0;
	}

	if (sdata->vif.type == NL80211_IFTYPE_ADHOC) {
		sdata_info(sdata,
			   "failed to move IBSS STA %pM to state %d (%d) - keeping it anyway\n",
			   sta->sta.addr, state + 1, err);
		err = 0;
	}

	/* unwind on error */
	for (; state > IEEE80211_STA_NOTEXIST; state--)
		WARN_ON(drv_sta_state(local, sdata, sta, state, state - 1));

	return err;
}