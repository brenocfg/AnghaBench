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
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct wilc_priv {TYPE_2__* dev; } ;
struct network_info {scalar_t__ ies_len; scalar_t__ ies; int /*<<< orphan*/  beacon_period; int /*<<< orphan*/  cap_info; int /*<<< orphan*/  tsf_hi; int /*<<< orphan*/  bssid; scalar_t__ ch; int /*<<< orphan*/  ssid; } ;
struct ieee80211_channel {int dummy; } ;
struct cfg80211_bss {int dummy; } ;
typedef  int s32 ;
struct TYPE_4__ {TYPE_1__* ieee80211_ptr; } ;
struct TYPE_3__ {struct wiphy* wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG80211_BSS_FTYPE_UNKNOWN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 struct cfg80211_bss* cfg80211_inform_bss (struct wiphy*,struct ieee80211_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_put_bss (struct wiphy*,struct cfg80211_bss*) ; 
 int get_rssi_avg (struct network_info*) ; 
 int ieee80211_channel_to_frequency (int,int /*<<< orphan*/ ) ; 
 struct ieee80211_channel* ieee80211_get_channel (struct wiphy*,int) ; 
 int last_scanned_cnt ; 
 struct network_info* last_scanned_shadow ; 
 int /*<<< orphan*/  memcmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void refresh_scan(struct wilc_priv *priv, bool direct_scan)
{
	struct wiphy *wiphy = priv->dev->ieee80211_ptr->wiphy;
	int i;

	for (i = 0; i < last_scanned_cnt; i++) {
		struct network_info *network_info;
		s32 freq;
		struct ieee80211_channel *channel;
		int rssi;
		struct cfg80211_bss *bss;

		network_info = &last_scanned_shadow[i];

		if (!memcmp("DIRECT-", network_info->ssid, 7) && !direct_scan)
			continue;

		freq = ieee80211_channel_to_frequency((s32)network_info->ch,
						      NL80211_BAND_2GHZ);
		channel = ieee80211_get_channel(wiphy, freq);
		rssi = get_rssi_avg(network_info);
		bss = cfg80211_inform_bss(wiphy,
					  channel,
					  CFG80211_BSS_FTYPE_UNKNOWN,
					  network_info->bssid,
					  network_info->tsf_hi,
					  network_info->cap_info,
					  network_info->beacon_period,
					  (const u8 *)network_info->ies,
					  (size_t)network_info->ies_len,
					  (s32)rssi * 100,
					  GFP_KERNEL);
		cfg80211_put_bss(wiphy, bss);
	}
}