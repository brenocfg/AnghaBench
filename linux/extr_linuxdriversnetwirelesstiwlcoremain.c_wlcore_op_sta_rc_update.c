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
typedef  int u32 ;
struct wl12xx_vif {int /*<<< orphan*/  rc_update_work; int /*<<< orphan*/  rc_ht_cap; int /*<<< orphan*/  rc_update_bw; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  ht_cap; int /*<<< orphan*/  bandwidth; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 int IEEE80211_RC_BW_CHANGED ; 
 int /*<<< orphan*/  ieee80211_queue_work (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 

__attribute__((used)) static void wlcore_op_sta_rc_update(struct ieee80211_hw *hw,
				    struct ieee80211_vif *vif,
				    struct ieee80211_sta *sta,
				    u32 changed)
{
	struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);

	wl1271_debug(DEBUG_MAC80211, "mac80211 sta_rc_update");

	if (!(changed & IEEE80211_RC_BW_CHANGED))
		return;

	/* this callback is atomic, so schedule a new work */
	wlvif->rc_update_bw = sta->bandwidth;
	memcpy(&wlvif->rc_ht_cap, &sta->ht_cap, sizeof(sta->ht_cap));
	ieee80211_queue_work(hw, &wlvif->rc_update_work);
}