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
struct ieee80211_hw {int extra_tx_headroom; int max_rates; int vif_data_size; int /*<<< orphan*/  max_rate_tries; TYPE_2__* wiphy; } ;
struct ath_common {int clockrate; int cachelsz; int /*<<< orphan*/  cc_lock; struct ath5k_hw* priv; struct ieee80211_hw* hw; struct ath5k_hw* ah; struct ath_bus_ops const* bus_ops; int /*<<< orphan*/ * ops; } ;
struct ath_bus_ops {int dummy; } ;
struct ath5k_vif {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  cap_mode; scalar_t__ cap_has_mrr_support; } ;
struct ath5k_hw {int bintval; int /*<<< orphan*/  irq; int /*<<< orphan*/  status; scalar_t__ ah_radio_2ghz_revision; scalar_t__ ah_radio_5ghz_revision; TYPE_1__ ah_capabilities; int /*<<< orphan*/  ah_single_chip; int /*<<< orphan*/  ah_phy_revision; scalar_t__ ah_mac_srev; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  block; int /*<<< orphan*/  txbuflock; int /*<<< orphan*/  rxbuflock; int /*<<< orphan*/  lock; int /*<<< orphan*/  opmode; int /*<<< orphan*/  dev; struct ieee80211_hw* hw; } ;
struct TYPE_4__ {int interface_modes; int n_iface_combinations; int available_antennas_tx; int available_antennas_rx; int /*<<< orphan*/  flags; int /*<<< orphan*/ * iface_combinations; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_INIT_RETRY_LONG ; 
 int /*<<< orphan*/  AR5K_INIT_RETRY_SHORT ; 
 int /*<<< orphan*/  AR5K_MODE_11A ; 
 int /*<<< orphan*/  AR5K_MODE_11B ; 
 int /*<<< orphan*/  AR5K_VERSION_MAC ; 
 int /*<<< orphan*/  AR5K_VERSION_RAD ; 
 int /*<<< orphan*/  ATH5K_ERR (struct ath5k_hw*,char*) ; 
 int /*<<< orphan*/  ATH5K_INFO (struct ath5k_hw*,char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  ATH_STAT_INVALID ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST_BROADCAST_PS_BUFFERING ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  MFP_CAPABLE ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_CQM_RSSI_LIST ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  REPORTS_TX_ACK_STATUS ; 
 int /*<<< orphan*/  RX_INCLUDES_FCS ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGNAL_DBM ; 
 int /*<<< orphan*/  SUPPORTS_RC_TABLE ; 
 int /*<<< orphan*/  WIPHY_FLAG_IBSS_RSN ; 
 int /*<<< orphan*/  WIPHY_FLAG_SUPPORTS_5_10_MHZ ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_chip_name (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ath5k_common_ops ; 
 int /*<<< orphan*/  ath5k_debug_init_device (struct ath5k_hw*) ; 
 struct ath_common* ath5k_hw_common (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_deinit (struct ath5k_hw*) ; 
 int ath5k_hw_init (struct ath5k_hw*) ; 
 int ath5k_init (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ath5k_intr ; 
 int /*<<< orphan*/  ath5k_read_cachesize (struct ath_common*,int*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ath5k_hw*) ; 
 int /*<<< orphan*/  ieee80211_hw_set (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_comb ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ath5k_hw*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_ext_feature_set (TYPE_2__*,int /*<<< orphan*/ ) ; 

int
ath5k_init_ah(struct ath5k_hw *ah, const struct ath_bus_ops *bus_ops)
{
	struct ieee80211_hw *hw = ah->hw;
	struct ath_common *common;
	int ret;
	int csz;

	/* Initialize driver private data */
	SET_IEEE80211_DEV(hw, ah->dev);
	ieee80211_hw_set(hw, SUPPORTS_RC_TABLE);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, MFP_CAPABLE);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(hw, HOST_BROADCAST_PS_BUFFERING);

	hw->wiphy->interface_modes =
		BIT(NL80211_IFTYPE_AP) |
		BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_ADHOC) |
		BIT(NL80211_IFTYPE_MESH_POINT);

	hw->wiphy->iface_combinations = &if_comb;
	hw->wiphy->n_iface_combinations = 1;

	/* SW support for IBSS_RSN is provided by mac80211 */
	hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;

	hw->wiphy->flags |= WIPHY_FLAG_SUPPORTS_5_10_MHZ;

	/* both antennas can be configured as RX or TX */
	hw->wiphy->available_antennas_tx = 0x3;
	hw->wiphy->available_antennas_rx = 0x3;

	hw->extra_tx_headroom = 2;

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	/*
	 * Mark the device as detached to avoid processing
	 * interrupts until setup is complete.
	 */
	__set_bit(ATH_STAT_INVALID, ah->status);

	ah->opmode = NL80211_IFTYPE_STATION;
	ah->bintval = 1000;
	mutex_init(&ah->lock);
	spin_lock_init(&ah->rxbuflock);
	spin_lock_init(&ah->txbuflock);
	spin_lock_init(&ah->block);
	spin_lock_init(&ah->irqlock);

	/* Setup interrupt handler */
	ret = request_irq(ah->irq, ath5k_intr, IRQF_SHARED, "ath", ah);
	if (ret) {
		ATH5K_ERR(ah, "request_irq failed\n");
		goto err;
	}

	common = ath5k_hw_common(ah);
	common->ops = &ath5k_common_ops;
	common->bus_ops = bus_ops;
	common->ah = ah;
	common->hw = hw;
	common->priv = ah;
	common->clockrate = 40;

	/*
	 * Cache line size is used to size and align various
	 * structures used to communicate with the hardware.
	 */
	ath5k_read_cachesize(common, &csz);
	common->cachelsz = csz << 2; /* convert to bytes */

	spin_lock_init(&common->cc_lock);

	/* Initialize device */
	ret = ath5k_hw_init(ah);
	if (ret)
		goto err_irq;

	/* Set up multi-rate retry capabilities */
	if (ah->ah_capabilities.cap_has_mrr_support) {
		hw->max_rates = 4;
		hw->max_rate_tries = max(AR5K_INIT_RETRY_SHORT,
					 AR5K_INIT_RETRY_LONG);
	}

	hw->vif_data_size = sizeof(struct ath5k_vif);

	/* Finish private driver data initialization */
	ret = ath5k_init(hw);
	if (ret)
		goto err_ah;

	ATH5K_INFO(ah, "Atheros AR%s chip found (MAC: 0x%x, PHY: 0x%x)\n",
			ath5k_chip_name(AR5K_VERSION_MAC, ah->ah_mac_srev),
					ah->ah_mac_srev,
					ah->ah_phy_revision);

	if (!ah->ah_single_chip) {
		/* Single chip radio (!RF5111) */
		if (ah->ah_radio_5ghz_revision &&
			!ah->ah_radio_2ghz_revision) {
			/* No 5GHz support -> report 2GHz radio */
			if (!test_bit(AR5K_MODE_11A,
				ah->ah_capabilities.cap_mode)) {
				ATH5K_INFO(ah, "RF%s 2GHz radio found (0x%x)\n",
					ath5k_chip_name(AR5K_VERSION_RAD,
						ah->ah_radio_5ghz_revision),
						ah->ah_radio_5ghz_revision);
			/* No 2GHz support (5110 and some
			 * 5GHz only cards) -> report 5GHz radio */
			} else if (!test_bit(AR5K_MODE_11B,
				ah->ah_capabilities.cap_mode)) {
				ATH5K_INFO(ah, "RF%s 5GHz radio found (0x%x)\n",
					ath5k_chip_name(AR5K_VERSION_RAD,
						ah->ah_radio_5ghz_revision),
						ah->ah_radio_5ghz_revision);
			/* Multiband radio */
			} else {
				ATH5K_INFO(ah, "RF%s multiband radio found"
					" (0x%x)\n",
					ath5k_chip_name(AR5K_VERSION_RAD,
						ah->ah_radio_5ghz_revision),
						ah->ah_radio_5ghz_revision);
			}
		}
		/* Multi chip radio (RF5111 - RF2111) ->
		 * report both 2GHz/5GHz radios */
		else if (ah->ah_radio_5ghz_revision &&
				ah->ah_radio_2ghz_revision) {
			ATH5K_INFO(ah, "RF%s 5GHz radio found (0x%x)\n",
				ath5k_chip_name(AR5K_VERSION_RAD,
					ah->ah_radio_5ghz_revision),
					ah->ah_radio_5ghz_revision);
			ATH5K_INFO(ah, "RF%s 2GHz radio found (0x%x)\n",
				ath5k_chip_name(AR5K_VERSION_RAD,
					ah->ah_radio_2ghz_revision),
					ah->ah_radio_2ghz_revision);
		}
	}

	ath5k_debug_init_device(ah);

	/* ready to process interrupts */
	__clear_bit(ATH_STAT_INVALID, ah->status);

	return 0;
err_ah:
	ath5k_hw_deinit(ah);
err_irq:
	free_irq(ah->irq, ah);
err:
	return ret;
}