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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct wiphy {scalar_t__ signal_type; } ;
struct wilc_priv {int cfg_scanning; scalar_t__ rcvd_ch_cnt; int /*<<< orphan*/  scan_req_lock; int /*<<< orphan*/ * scan_req; TYPE_2__* dev; } ;
struct network_info {scalar_t__ rssi; int /*<<< orphan*/  bssid; scalar_t__ ies_len; scalar_t__ ies; int /*<<< orphan*/  beacon_period; int /*<<< orphan*/  cap_info; int /*<<< orphan*/  tsf_hi; int /*<<< orphan*/  ssid; scalar_t__ new_network; scalar_t__ ch; } ;
struct ieee80211_channel {int dummy; } ;
struct cfg80211_scan_info {int aborted; } ;
struct cfg80211_bss {int dummy; } ;
typedef  int s32 ;
typedef  enum scan_event { ____Placeholder_scan_event } scan_event ;
struct TYPE_6__ {char* bssid; int /*<<< orphan*/  time_scan; scalar_t__ rssi; } ;
struct TYPE_5__ {TYPE_1__* ieee80211_ptr; } ;
struct TYPE_4__ {struct wiphy* wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG80211_BSS_FTYPE_UNKNOWN ; 
 scalar_t__ CFG80211_SIGNAL_TYPE_UNSPEC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MAX_NUM_SCANNED_NETWORKS ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int SCAN_EVENT_ABORTED ; 
 int SCAN_EVENT_DONE ; 
 int SCAN_EVENT_NETWORK_FOUND ; 
 int /*<<< orphan*/  add_network_to_shadow (struct network_info*,struct wilc_priv*,void*) ; 
 struct cfg80211_bss* cfg80211_inform_bss (struct wiphy*,struct ieee80211_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_put_bss (struct wiphy*,struct cfg80211_bss*) ; 
 int /*<<< orphan*/  cfg80211_scan_done (int /*<<< orphan*/ *,struct cfg80211_scan_info*) ; 
 int ieee80211_channel_to_frequency (int,int /*<<< orphan*/ ) ; 
 struct ieee80211_channel* ieee80211_get_channel (struct wiphy*,int) ; 
 int /*<<< orphan*/  jiffies ; 
 TYPE_3__* last_scanned_shadow ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refresh_scan (struct wilc_priv*,int) ; 
 int /*<<< orphan*/  update_scan_time () ; 

__attribute__((used)) static void cfg_scan_result(enum scan_event scan_event,
			    struct network_info *network_info,
			    void *user_void, void *join_params)
{
	struct wilc_priv *priv;
	struct wiphy *wiphy;
	s32 freq;
	struct ieee80211_channel *channel;
	struct cfg80211_bss *bss = NULL;

	priv = user_void;
	if (!priv->cfg_scanning)
		return;

	if (scan_event == SCAN_EVENT_NETWORK_FOUND) {
		wiphy = priv->dev->ieee80211_ptr->wiphy;

		if (!wiphy || !network_info)
			return;

		if (wiphy->signal_type == CFG80211_SIGNAL_TYPE_UNSPEC &&
		    (((s32)network_info->rssi * 100) < 0 ||
		    ((s32)network_info->rssi * 100) > 100))
			return;

		freq = ieee80211_channel_to_frequency((s32)network_info->ch,
						      NL80211_BAND_2GHZ);
		channel = ieee80211_get_channel(wiphy, freq);

		if (!channel)
			return;

		if (network_info->new_network) {
			if (priv->rcvd_ch_cnt >= MAX_NUM_SCANNED_NETWORKS)
				return;

			priv->rcvd_ch_cnt++;

			add_network_to_shadow(network_info, priv, join_params);

			if (memcmp("DIRECT-", network_info->ssid, 7))
				return;

			bss = cfg80211_inform_bss(wiphy,
						  channel,
						  CFG80211_BSS_FTYPE_UNKNOWN,
						  network_info->bssid,
						  network_info->tsf_hi,
						  network_info->cap_info,
						  network_info->beacon_period,
						  (const u8 *)network_info->ies,
						  (size_t)network_info->ies_len,
						  (s32)network_info->rssi * 100,
						  GFP_KERNEL);
			cfg80211_put_bss(wiphy, bss);
		} else {
			u32 i;

			for (i = 0; i < priv->rcvd_ch_cnt; i++) {
				if (memcmp(last_scanned_shadow[i].bssid,
					   network_info->bssid, 6) == 0)
					break;
			}

			if (i >= priv->rcvd_ch_cnt)
				return;

			last_scanned_shadow[i].rssi = network_info->rssi;
			last_scanned_shadow[i].time_scan = jiffies;
		}
	} else if (scan_event == SCAN_EVENT_DONE) {
		refresh_scan(priv, false);

		mutex_lock(&priv->scan_req_lock);

		if (priv->scan_req) {
			struct cfg80211_scan_info info = {
				.aborted = false,
			};

			cfg80211_scan_done(priv->scan_req, &info);
			priv->rcvd_ch_cnt = 0;
			priv->cfg_scanning = false;
			priv->scan_req = NULL;
		}
		mutex_unlock(&priv->scan_req_lock);
	} else if (scan_event == SCAN_EVENT_ABORTED) {
		mutex_lock(&priv->scan_req_lock);

		if (priv->scan_req) {
			struct cfg80211_scan_info info = {
				.aborted = false,
			};

			update_scan_time();
			refresh_scan(priv, false);

			cfg80211_scan_done(priv->scan_req, &info);
			priv->cfg_scanning = false;
			priv->scan_req = NULL;
		}
		mutex_unlock(&priv->scan_req_lock);
	}
}