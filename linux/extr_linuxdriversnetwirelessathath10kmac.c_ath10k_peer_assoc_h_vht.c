#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_14__ {int rx_max_rate; int rx_mcs_set; int tx_max_rate; int /*<<< orphan*/  tx_mcs_set; } ;
struct wmi_peer_assoc_complete_arg {unsigned int peer_vht_caps; int peer_bw_rxnss_override; TYPE_7__ peer_vht_rates; int /*<<< orphan*/  peer_flags; int /*<<< orphan*/  peer_max_mpdu; int /*<<< orphan*/  peer_num_spatial_streams; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct TYPE_13__ {int /*<<< orphan*/  tx_mcs_map; int /*<<< orphan*/  tx_highest; int /*<<< orphan*/  rx_mcs_map; int /*<<< orphan*/  rx_highest; } ;
struct ieee80211_sta_vht_cap {unsigned int cap; TYPE_6__ vht_mcs; int /*<<< orphan*/  vht_supported; } ;
struct ieee80211_sta {scalar_t__ bandwidth; struct ieee80211_sta_vht_cap vht_cap; int /*<<< orphan*/  addr; int /*<<< orphan*/  rx_nss; } ;
struct cfg80211_chan_def {TYPE_3__* chan; } ;
struct TYPE_9__ {TYPE_1__* control; } ;
struct ath10k_vif {TYPE_2__ bitrate_mask; } ;
struct TYPE_12__ {TYPE_4__* peer_flags; } ;
struct ath10k {TYPE_5__ wmi; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_11__ {int /*<<< orphan*/  bw160; int /*<<< orphan*/  bw80; int /*<<< orphan*/  vht_2g; int /*<<< orphan*/  vht; } ;
struct TYPE_10__ {int band; } ;
struct TYPE_8__ {scalar_t__* vht_mcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 unsigned int IEEE80211_HT_MAX_AMPDU_FACTOR ; 
 scalar_t__ IEEE80211_STA_RX_BW_160 ; 
 scalar_t__ IEEE80211_STA_RX_BW_80 ; 
 unsigned int IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK ; 
 unsigned int IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT ; 
 int IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK ; 
 unsigned int IEEE80211_VHT_MCS_NOT_SUPPORTED ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 int NL80211_VHT_NSS_MAX ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_mac_vif_chan (struct ieee80211_vif*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  ath10k_peer_assoc_h_vht_limit (int,scalar_t__ const*) ; 
 scalar_t__ ath10k_peer_assoc_h_vht_masked (scalar_t__ const*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void ath10k_peer_assoc_h_vht(struct ath10k *ar,
				    struct ieee80211_vif *vif,
				    struct ieee80211_sta *sta,
				    struct wmi_peer_assoc_complete_arg *arg)
{
	const struct ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;
	struct ath10k_vif *arvif = (void *)vif->drv_priv;
	struct cfg80211_chan_def def;
	enum nl80211_band band;
	const u16 *vht_mcs_mask;
	u8 ampdu_factor;
	u8 max_nss, vht_mcs;
	int i;

	if (WARN_ON(ath10k_mac_vif_chan(vif, &def)))
		return;

	if (!vht_cap->vht_supported)
		return;

	band = def.chan->band;
	vht_mcs_mask = arvif->bitrate_mask.control[band].vht_mcs;

	if (ath10k_peer_assoc_h_vht_masked(vht_mcs_mask))
		return;

	arg->peer_flags |= ar->wmi.peer_flags->vht;

	if (def.chan->band == NL80211_BAND_2GHZ)
		arg->peer_flags |= ar->wmi.peer_flags->vht_2g;

	arg->peer_vht_caps = vht_cap->cap;

	ampdu_factor = (vht_cap->cap &
			IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK) >>
		       IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT;

	/* Workaround: Some Netgear/Linksys 11ac APs set Rx A-MPDU factor to
	 * zero in VHT IE. Using it would result in degraded throughput.
	 * arg->peer_max_mpdu at this point contains HT max_mpdu so keep
	 * it if VHT max_mpdu is smaller.
	 */
	arg->peer_max_mpdu = max(arg->peer_max_mpdu,
				 (1U << (IEEE80211_HT_MAX_AMPDU_FACTOR +
					ampdu_factor)) - 1);

	if (sta->bandwidth == IEEE80211_STA_RX_BW_80)
		arg->peer_flags |= ar->wmi.peer_flags->bw80;

	if (sta->bandwidth == IEEE80211_STA_RX_BW_160)
		arg->peer_flags |= ar->wmi.peer_flags->bw160;

	/* Calculate peer NSS capability from VHT capabilities if STA
	 * supports VHT.
	 */
	for (i = 0, max_nss = 0, vht_mcs = 0; i < NL80211_VHT_NSS_MAX; i++) {
		vht_mcs = __le16_to_cpu(vht_cap->vht_mcs.rx_mcs_map) >>
			  (2 * i) & 3;

		if ((vht_mcs != IEEE80211_VHT_MCS_NOT_SUPPORTED) &&
		    vht_mcs_mask[i])
			max_nss = i + 1;
	}
	arg->peer_num_spatial_streams = min(sta->rx_nss, max_nss);
	arg->peer_vht_rates.rx_max_rate =
		__le16_to_cpu(vht_cap->vht_mcs.rx_highest);
	arg->peer_vht_rates.rx_mcs_set =
		__le16_to_cpu(vht_cap->vht_mcs.rx_mcs_map);
	arg->peer_vht_rates.tx_max_rate =
		__le16_to_cpu(vht_cap->vht_mcs.tx_highest);
	arg->peer_vht_rates.tx_mcs_set = ath10k_peer_assoc_h_vht_limit(
		__le16_to_cpu(vht_cap->vht_mcs.tx_mcs_map), vht_mcs_mask);

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vht peer %pM max_mpdu %d flags 0x%x\n",
		   sta->addr, arg->peer_max_mpdu, arg->peer_flags);

	if (arg->peer_vht_rates.rx_max_rate &&
	    (sta->vht_cap.cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK)) {
		switch (arg->peer_vht_rates.rx_max_rate) {
		case 1560:
			/* Must be 2x2 at 160Mhz is all it can do. */
			arg->peer_bw_rxnss_override = 2;
			break;
		case 780:
			/* Can only do 1x1 at 160Mhz (Long Guard Interval) */
			arg->peer_bw_rxnss_override = 1;
			break;
		}
	}
}