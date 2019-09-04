#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wmi_peer_assoc_complete_arg {int peer_phymode; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct TYPE_10__ {int /*<<< orphan*/  ht_supported; } ;
struct TYPE_9__ {int /*<<< orphan*/  vht_supported; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; int /*<<< orphan*/  bandwidth; TYPE_5__ ht_cap; TYPE_4__ vht_cap; } ;
struct cfg80211_chan_def {TYPE_1__* chan; } ;
struct TYPE_8__ {TYPE_2__* control; } ;
struct ath10k_vif {TYPE_3__ bitrate_mask; } ;
struct ath10k {int dummy; } ;
typedef  enum wmi_phy_mode { ____Placeholder_wmi_phy_mode } wmi_phy_mode ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_7__ {int /*<<< orphan*/ * vht_mcs; int /*<<< orphan*/ * ht_mcs; } ;
struct TYPE_6__ {int band; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 int /*<<< orphan*/  IEEE80211_STA_RX_BW_40 ; 
 int MODE_11A ; 
 int MODE_11AC_VHT20 ; 
 int MODE_11AC_VHT40 ; 
 int MODE_11B ; 
 int MODE_11G ; 
 int MODE_11NA_HT20 ; 
 int MODE_11NA_HT40 ; 
 int MODE_11NG_HT20 ; 
 int MODE_11NG_HT40 ; 
 int MODE_UNKNOWN ; 
#define  NL80211_BAND_2GHZ 129 
#define  NL80211_BAND_5GHZ 128 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath10k_mac_get_phymode_vht (struct ath10k*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  ath10k_mac_sta_has_ofdm_only (struct ieee80211_sta*) ; 
 int ath10k_mac_vif_chan (struct ieee80211_vif*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  ath10k_peer_assoc_h_ht_masked (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ath10k_peer_assoc_h_vht_masked (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ath10k_wmi_phymode_str (int) ; 

__attribute__((used)) static void ath10k_peer_assoc_h_phymode(struct ath10k *ar,
					struct ieee80211_vif *vif,
					struct ieee80211_sta *sta,
					struct wmi_peer_assoc_complete_arg *arg)
{
	struct ath10k_vif *arvif = (void *)vif->drv_priv;
	struct cfg80211_chan_def def;
	enum nl80211_band band;
	const u8 *ht_mcs_mask;
	const u16 *vht_mcs_mask;
	enum wmi_phy_mode phymode = MODE_UNKNOWN;

	if (WARN_ON(ath10k_mac_vif_chan(vif, &def)))
		return;

	band = def.chan->band;
	ht_mcs_mask = arvif->bitrate_mask.control[band].ht_mcs;
	vht_mcs_mask = arvif->bitrate_mask.control[band].vht_mcs;

	switch (band) {
	case NL80211_BAND_2GHZ:
		if (sta->vht_cap.vht_supported &&
		    !ath10k_peer_assoc_h_vht_masked(vht_mcs_mask)) {
			if (sta->bandwidth == IEEE80211_STA_RX_BW_40)
				phymode = MODE_11AC_VHT40;
			else
				phymode = MODE_11AC_VHT20;
		} else if (sta->ht_cap.ht_supported &&
			   !ath10k_peer_assoc_h_ht_masked(ht_mcs_mask)) {
			if (sta->bandwidth == IEEE80211_STA_RX_BW_40)
				phymode = MODE_11NG_HT40;
			else
				phymode = MODE_11NG_HT20;
		} else if (ath10k_mac_sta_has_ofdm_only(sta)) {
			phymode = MODE_11G;
		} else {
			phymode = MODE_11B;
		}

		break;
	case NL80211_BAND_5GHZ:
		/*
		 * Check VHT first.
		 */
		if (sta->vht_cap.vht_supported &&
		    !ath10k_peer_assoc_h_vht_masked(vht_mcs_mask)) {
			phymode = ath10k_mac_get_phymode_vht(ar, sta);
		} else if (sta->ht_cap.ht_supported &&
			   !ath10k_peer_assoc_h_ht_masked(ht_mcs_mask)) {
			if (sta->bandwidth >= IEEE80211_STA_RX_BW_40)
				phymode = MODE_11NA_HT40;
			else
				phymode = MODE_11NA_HT20;
		} else {
			phymode = MODE_11A;
		}

		break;
	default:
		break;
	}

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac peer %pM phymode %s\n",
		   sta->addr, ath10k_wmi_phymode_str(phymode));

	arg->peer_phymode = phymode;
	WARN_ON(phymode == MODE_UNKNOWN);
}