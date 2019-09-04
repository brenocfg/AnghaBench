#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl1271 {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  roc_complete_work; struct ieee80211_vif* roc_vif; int /*<<< orphan*/  roc_map; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct wl1271* priv; } ;
struct ieee80211_channel {int /*<<< orphan*/  band; int /*<<< orphan*/  center_freq; } ;
typedef  enum ieee80211_roc_type { ____Placeholder_ieee80211_roc_type } ieee80211_roc_type ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 int EBUSY ; 
 int WL12XX_MAX_ROLES ; 
 scalar_t__ WLCORE_STATE_ON ; 
 int find_first_bit (int /*<<< orphan*/ ,int) ; 
 int ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (struct ieee80211_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 
 int wl12xx_start_dev (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ,int) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 

__attribute__((used)) static int wlcore_op_remain_on_channel(struct ieee80211_hw *hw,
				       struct ieee80211_vif *vif,
				       struct ieee80211_channel *chan,
				       int duration,
				       enum ieee80211_roc_type type)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	struct wl1271 *wl = hw->priv;
	int channel, active_roc, ret = 0;

	channel = ieee80211_frequency_to_channel(chan->center_freq);

	wl1271_debug(DEBUG_MAC80211, "mac80211 roc %d (%d)",
		     channel, wlvif->role_id);

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state != WLCORE_STATE_ON))
		goto out;

	/* return EBUSY if we can't ROC right now */
	active_roc = find_first_bit(wl->roc_map, WL12XX_MAX_ROLES);
	if (wl->roc_vif || active_roc < WL12XX_MAX_ROLES) {
		wl1271_warning("active roc on role %d", active_roc);
		ret = -EBUSY;
		goto out;
	}

	ret = pm_runtime_get_sync(wl->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(wl->dev);
		goto out;
	}

	ret = wl12xx_start_dev(wl, wlvif, chan->band, channel);
	if (ret < 0)
		goto out_sleep;

	wl->roc_vif = vif;
	ieee80211_queue_delayed_work(hw, &wl->roc_complete_work,
				     msecs_to_jiffies(duration));
out_sleep:
	pm_runtime_mark_last_busy(wl->dev);
	pm_runtime_put_autosuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
	return ret;
}