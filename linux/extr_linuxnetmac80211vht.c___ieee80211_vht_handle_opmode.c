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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sta_opmode_info {int rx_nss; int changed; int /*<<< orphan*/  bw; } ;
struct TYPE_2__ {int rx_nss; int bandwidth; } ;
struct sta_info {int /*<<< orphan*/  addr; TYPE_1__ sta; int /*<<< orphan*/  cur_max_bandwidth; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  dev; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
typedef  enum ieee80211_sta_rx_bandwidth { ____Placeholder_ieee80211_sta_rx_bandwidth } ieee80211_sta_rx_bandwidth ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IEEE80211_OPMODE_NOTIF_CHANWIDTH_160MHZ 131 
#define  IEEE80211_OPMODE_NOTIF_CHANWIDTH_20MHZ 130 
#define  IEEE80211_OPMODE_NOTIF_CHANWIDTH_40MHZ 129 
#define  IEEE80211_OPMODE_NOTIF_CHANWIDTH_80MHZ 128 
 int IEEE80211_OPMODE_NOTIF_CHANWIDTH_MASK ; 
 int IEEE80211_OPMODE_NOTIF_RX_NSS_MASK ; 
 int IEEE80211_OPMODE_NOTIF_RX_NSS_SHIFT ; 
 int IEEE80211_OPMODE_NOTIF_RX_NSS_TYPE_BF ; 
 int /*<<< orphan*/  IEEE80211_RC_BW_CHANGED ; 
 int /*<<< orphan*/  IEEE80211_RC_NSS_CHANGED ; 
 int /*<<< orphan*/  IEEE80211_STA_RX_BW_160 ; 
 int /*<<< orphan*/  IEEE80211_STA_RX_BW_20 ; 
 int /*<<< orphan*/  IEEE80211_STA_RX_BW_40 ; 
 int /*<<< orphan*/  IEEE80211_STA_RX_BW_80 ; 
 int STA_OPMODE_MAX_BW_CHANGED ; 
 int STA_OPMODE_N_SS_CHANGED ; 
 int /*<<< orphan*/  cfg80211_sta_opmode_change_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sta_opmode_info*,int /*<<< orphan*/ ) ; 
 int ieee80211_sta_cur_vht_bw (struct sta_info*) ; 
 int /*<<< orphan*/  ieee80211_sta_rx_bw_to_chan_width (struct sta_info*) ; 

u32 __ieee80211_vht_handle_opmode(struct ieee80211_sub_if_data *sdata,
				  struct sta_info *sta, u8 opmode,
				  enum nl80211_band band)
{
	enum ieee80211_sta_rx_bandwidth new_bw;
	struct sta_opmode_info sta_opmode = {};
	u32 changed = 0;
	u8 nss;

	/* ignore - no support for BF yet */
	if (opmode & IEEE80211_OPMODE_NOTIF_RX_NSS_TYPE_BF)
		return 0;

	nss = opmode & IEEE80211_OPMODE_NOTIF_RX_NSS_MASK;
	nss >>= IEEE80211_OPMODE_NOTIF_RX_NSS_SHIFT;
	nss += 1;

	if (sta->sta.rx_nss != nss) {
		sta->sta.rx_nss = nss;
		sta_opmode.rx_nss = nss;
		changed |= IEEE80211_RC_NSS_CHANGED;
		sta_opmode.changed |= STA_OPMODE_N_SS_CHANGED;
	}

	switch (opmode & IEEE80211_OPMODE_NOTIF_CHANWIDTH_MASK) {
	case IEEE80211_OPMODE_NOTIF_CHANWIDTH_20MHZ:
		sta->cur_max_bandwidth = IEEE80211_STA_RX_BW_20;
		break;
	case IEEE80211_OPMODE_NOTIF_CHANWIDTH_40MHZ:
		sta->cur_max_bandwidth = IEEE80211_STA_RX_BW_40;
		break;
	case IEEE80211_OPMODE_NOTIF_CHANWIDTH_80MHZ:
		sta->cur_max_bandwidth = IEEE80211_STA_RX_BW_80;
		break;
	case IEEE80211_OPMODE_NOTIF_CHANWIDTH_160MHZ:
		sta->cur_max_bandwidth = IEEE80211_STA_RX_BW_160;
		break;
	}

	new_bw = ieee80211_sta_cur_vht_bw(sta);
	if (new_bw != sta->sta.bandwidth) {
		sta->sta.bandwidth = new_bw;
		sta_opmode.bw = ieee80211_sta_rx_bw_to_chan_width(sta);
		changed |= IEEE80211_RC_BW_CHANGED;
		sta_opmode.changed |= STA_OPMODE_MAX_BW_CHANGED;
	}

	if (sta_opmode.changed)
		cfg80211_sta_opmode_change_notify(sdata->dev, sta->addr,
						  &sta_opmode, GFP_KERNEL);

	return changed;
}