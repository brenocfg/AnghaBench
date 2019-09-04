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
struct TYPE_2__ {int /*<<< orphan*/  hlid; } ;
struct wl12xx_vif {int default_key; scalar_t__ encryption_type; TYPE_1__ sta; } ;
struct wl1271 {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct wl1271* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 int EAGAIN ; 
 scalar_t__ KEY_WEP ; 
 scalar_t__ WLCORE_STATE_ON ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int) ; 
 int wl12xx_cmd_set_default_wep_key (struct wl1271*,int,int /*<<< orphan*/ ) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 

__attribute__((used)) static void wl1271_op_set_default_key_idx(struct ieee80211_hw *hw,
					  struct ieee80211_vif *vif,
					  int key_idx)
{
	struct wl1271 *wl = hw->priv;
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	int ret;

	wl1271_debug(DEBUG_MAC80211, "mac80211 set default key idx %d",
		     key_idx);

	/* we don't handle unsetting of default key */
	if (key_idx == -1)
		return;

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state != WLCORE_STATE_ON)) {
		ret = -EAGAIN;
		goto out_unlock;
	}

	ret = pm_runtime_get_sync(wl->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(wl->dev);
		goto out_unlock;
	}

	wlvif->default_key = key_idx;

	/* the default WEP key needs to be configured at least once */
	if (wlvif->encryption_type == KEY_WEP) {
		ret = wl12xx_cmd_set_default_wep_key(wl,
				key_idx,
				wlvif->sta.hlid);
		if (ret < 0)
			goto out_sleep;
	}

out_sleep:
	pm_runtime_mark_last_busy(wl->dev);
	pm_runtime_put_autosuspend(wl->dev);

out_unlock:
	mutex_unlock(&wl->mutex);
}