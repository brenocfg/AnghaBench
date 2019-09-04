#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wl12xx_vif {int channel; scalar_t__ bss_type; int radar_enabled; int /*<<< orphan*/  channel_type; int /*<<< orphan*/  band; int /*<<< orphan*/  flags; int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;
struct TYPE_4__ {TYPE_1__* chan; } ;
struct ieee80211_chanctx_conf {scalar_t__ radar_enabled; TYPE_2__ def; } ;
struct TYPE_3__ {int /*<<< orphan*/  band; int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_AP_BSS ; 
 int /*<<< orphan*/  DEBUG_MAC80211 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WLVIF_FLAG_BEACON_DISABLED ; 
 int /*<<< orphan*/  cfg80211_get_chandef_type (TYPE_2__*) ; 
 int ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wlcore_hw_set_cac (struct wl1271*,struct wl12xx_vif*,int) ; 

__attribute__((used)) static int __wlcore_switch_vif_chan(struct wl1271 *wl,
				    struct wl12xx_vif *wlvif,
				    struct ieee80211_chanctx_conf *new_ctx)
{
	int channel = ieee80211_frequency_to_channel(
		new_ctx->def.chan->center_freq);

	wl1271_debug(DEBUG_MAC80211,
		     "switch vif (role %d) %d -> %d chan_type: %d",
		     wlvif->role_id, wlvif->channel, channel,
		     cfg80211_get_chandef_type(&new_ctx->def));

	if (WARN_ON_ONCE(wlvif->bss_type != BSS_TYPE_AP_BSS))
		return 0;

	WARN_ON(!test_bit(WLVIF_FLAG_BEACON_DISABLED, &wlvif->flags));

	if (wlvif->radar_enabled) {
		wl1271_debug(DEBUG_MAC80211, "Stop radar detection");
		wlcore_hw_set_cac(wl, wlvif, false);
		wlvif->radar_enabled = false;
	}

	wlvif->band = new_ctx->def.chan->band;
	wlvif->channel = channel;
	wlvif->channel_type = cfg80211_get_chandef_type(&new_ctx->def);

	/* start radar if needed */
	if (new_ctx->radar_enabled) {
		wl1271_debug(DEBUG_MAC80211, "Start radar detection");
		wlcore_hw_set_cac(wl, wlvif, true);
		wlvif->radar_enabled = true;
	}

	return 0;
}