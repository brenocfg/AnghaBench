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
struct TYPE_2__ {int /*<<< orphan*/  hlid; } ;
struct wl12xx_vif {scalar_t__ bss_type; TYPE_1__ sta; int /*<<< orphan*/  dev_hlid; } ;
struct wl1271 {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_AP_BSS ; 
 int /*<<< orphan*/  DEBUG_TX ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_TX_OFFCHAN ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl12xx_tx_get_hlid_ap (struct wl1271*,struct wl12xx_vif*,struct sk_buff*,struct ieee80211_sta*) ; 

u8 wl12xx_tx_get_hlid(struct wl1271 *wl, struct wl12xx_vif *wlvif,
		      struct sk_buff *skb, struct ieee80211_sta *sta)
{
	struct ieee80211_tx_info *control;

	if (wlvif->bss_type == BSS_TYPE_AP_BSS)
		return wl12xx_tx_get_hlid_ap(wl, wlvif, skb, sta);

	control = IEEE80211_SKB_CB(skb);
	if (control->flags & IEEE80211_TX_CTL_TX_OFFCHAN) {
		wl1271_debug(DEBUG_TX, "tx offchannel");
		return wlvif->dev_hlid;
	}

	return wlvif->sta.hlid;
}