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
struct tx_frame_hdr {int dummy; } ;
struct ieee80211_hw {int queues; int max_listen_interval; int vif_data_size; int sta_data_size; int extra_tx_headroom; TYPE_2__* wiphy; } ;
struct htc_frame_hdr {int dummy; } ;
struct base_eep_header {int /*<<< orphan*/  txMask; int /*<<< orphan*/  rxMask; } ;
struct TYPE_3__ {int hw_caps; } ;
struct ath_hw {TYPE_1__ caps; } ;
struct ath_common {int /*<<< orphan*/  macaddr; int /*<<< orphan*/ * sbands; } ;
struct ath9k_htc_vif {int dummy; } ;
struct ath9k_htc_sta {int dummy; } ;
struct ath9k_htc_priv {struct ath_hw* ah; } ;
struct TYPE_4__ {int interface_modes; int n_iface_combinations; int flags; int /*<<< orphan*/  available_antennas_tx; int /*<<< orphan*/  available_antennas_rx; int /*<<< orphan*/ ** bands; int /*<<< orphan*/ * iface_combinations; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMPDU_AGGREGATION ; 
 int ATH9K_HW_CAP_2GHZ ; 
 int ATH9K_HW_CAP_5GHZ ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DOESNT_SUPPORT_QOS_NDP ; 
 int /*<<< orphan*/  HAS_RATE_CONTROL ; 
 int /*<<< orphan*/  HOST_BROADCAST_PS_BUFFERING ; 
 int /*<<< orphan*/  MFP_CAPABLE ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_CQM_RSSI_LIST ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_OCB ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_CLIENT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_GO ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  PS_NULLFUNC_STACK ; 
 int /*<<< orphan*/  REPORTS_TX_ACK_STATUS ; 
 int /*<<< orphan*/  RX_INCLUDES_FCS ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGNAL_DBM ; 
 int /*<<< orphan*/  SPECTRUM_MGMT ; 
 int /*<<< orphan*/  SUPPORTS_PS ; 
 int WIPHY_FLAG_HAS_CHANNEL_SWITCH ; 
 int WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL ; 
 int WIPHY_FLAG_IBSS_RSN ; 
 int WIPHY_FLAG_PS_ON_BY_DEFAULT ; 
 int WIPHY_FLAG_SUPPORTS_TDLS ; 
 int /*<<< orphan*/  ath9k_cmn_reload_chainmask (struct ath_hw*) ; 
 struct base_eep_header* ath9k_htc_get_eeprom_base (struct ath9k_htc_priv*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 scalar_t__ ath9k_ps_enable ; 
 int /*<<< orphan*/  ieee80211_hw_set (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_comb ; 
 int /*<<< orphan*/  wiphy_ext_feature_set (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_set_hw_capab(struct ath9k_htc_priv *priv,
			       struct ieee80211_hw *hw)
{
	struct ath_hw *ah = priv->ah;
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct base_eep_header *pBase;

	ieee80211_hw_set(hw, HOST_BROADCAST_PS_BUFFERING);
	ieee80211_hw_set(hw, MFP_CAPABLE);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, PS_NULLFUNC_STACK);
	ieee80211_hw_set(hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(hw, HAS_RATE_CONTROL);
	ieee80211_hw_set(hw, SPECTRUM_MGMT);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, DOESNT_SUPPORT_QOS_NDP);

	if (ath9k_ps_enable)
		ieee80211_hw_set(hw, SUPPORTS_PS);

	hw->wiphy->interface_modes =
		BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_ADHOC) |
		BIT(NL80211_IFTYPE_AP) |
		BIT(NL80211_IFTYPE_P2P_GO) |
		BIT(NL80211_IFTYPE_P2P_CLIENT) |
		BIT(NL80211_IFTYPE_MESH_POINT) |
		BIT(NL80211_IFTYPE_OCB);

	hw->wiphy->iface_combinations = &if_comb;
	hw->wiphy->n_iface_combinations = 1;

	hw->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN |
			    WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL |
			    WIPHY_FLAG_HAS_CHANNEL_SWITCH;

	hw->wiphy->flags |= WIPHY_FLAG_SUPPORTS_TDLS;

	hw->queues = 4;
	hw->max_listen_interval = 1;

	hw->vif_data_size = sizeof(struct ath9k_htc_vif);
	hw->sta_data_size = sizeof(struct ath9k_htc_sta);

	/* tx_frame_hdr is larger than tx_mgmt_hdr anyway */
	hw->extra_tx_headroom = sizeof(struct tx_frame_hdr) +
		sizeof(struct htc_frame_hdr) + 4;

	if (priv->ah->caps.hw_caps & ATH9K_HW_CAP_2GHZ)
		hw->wiphy->bands[NL80211_BAND_2GHZ] =
			&common->sbands[NL80211_BAND_2GHZ];
	if (priv->ah->caps.hw_caps & ATH9K_HW_CAP_5GHZ)
		hw->wiphy->bands[NL80211_BAND_5GHZ] =
			&common->sbands[NL80211_BAND_5GHZ];

	ath9k_cmn_reload_chainmask(ah);

	pBase = ath9k_htc_get_eeprom_base(priv);
	if (pBase) {
		hw->wiphy->available_antennas_rx = pBase->rxMask;
		hw->wiphy->available_antennas_tx = pBase->txMask;
	}

	SET_IEEE80211_PERM_ADDR(hw, common->macaddr);

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);
}