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
struct wl12xx_vif {scalar_t__ bss_type; int /*<<< orphan*/  basic_rate_set; int /*<<< orphan*/  basic_rate; int /*<<< orphan*/  flags; int /*<<< orphan*/ * bitrate_masks; } ;
struct wl1271 {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct wl1271* priv; } ;
struct cfg80211_bitrate_mask {TYPE_1__* control; } ;
struct TYPE_2__ {int /*<<< orphan*/  legacy; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_STA_BSS ; 
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int WLCORE_NUM_BANDS ; 
 scalar_t__ WLCORE_STATE_ON ; 
 int /*<<< orphan*/  WLVIF_FLAG_STA_ASSOCIATED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int wl1271_acx_sta_rate_policies (struct wl1271*,struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_set_band_rate (struct wl1271*,struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wl1271_tx_enabled_rates_get (struct wl1271*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wl1271_tx_min_rate_get (struct wl1271*,int /*<<< orphan*/ ) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 

__attribute__((used)) static int wl12xx_set_bitrate_mask(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif,
				   const struct cfg80211_bitrate_mask *mask)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
	struct wl1271 *wl = hw->priv;
	int i, ret = 0;

	wl1271_debug(DEBUG_MAC80211, "mac80211 set_bitrate_mask 0x%x 0x%x",
		mask->control[NL80211_BAND_2GHZ].legacy,
		mask->control[NL80211_BAND_5GHZ].legacy);

	mutex_lock(&wl->mutex);

	for (i = 0; i < WLCORE_NUM_BANDS; i++)
		wlvif->bitrate_masks[i] =
			wl1271_tx_enabled_rates_get(wl,
						    mask->control[i].legacy,
						    i);

	if (unlikely(wl->state != WLCORE_STATE_ON))
		goto out;

	if (wlvif->bss_type == BSS_TYPE_STA_BSS &&
	    !test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvif->flags)) {

		ret = pm_runtime_get_sync(wl->dev);
		if (ret < 0) {
			pm_runtime_put_noidle(wl->dev);
			goto out;
		}

		wl1271_set_band_rate(wl, wlvif);
		wlvif->basic_rate =
			wl1271_tx_min_rate_get(wl, wlvif->basic_rate_set);
		ret = wl1271_acx_sta_rate_policies(wl, wlvif);

		pm_runtime_mark_last_busy(wl->dev);
		pm_runtime_put_autosuspend(wl->dev);
	}
out:
	mutex_unlock(&wl->mutex);

	return ret;
}