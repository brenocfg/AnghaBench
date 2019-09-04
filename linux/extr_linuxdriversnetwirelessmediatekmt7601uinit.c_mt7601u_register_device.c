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
struct wiphy {int /*<<< orphan*/  interface_modes; int /*<<< orphan*/  features; } ;
struct mt76_vif {int dummy; } ;
struct mt76_sta {int dummy; } ;
struct mt7601u_dev {int* wcid_mask; int /*<<< orphan*/  stat_work; int /*<<< orphan*/  mac_work; int /*<<< orphan*/  macaddr; int /*<<< orphan*/  dev; TYPE_1__* mon_wcid; struct ieee80211_hw* hw; } ;
struct ieee80211_hw {int queues; int max_rates; int max_report_rates; int max_rate_tries; int sta_data_size; int vif_data_size; struct wiphy* wiphy; } ;
struct TYPE_2__ {int idx; int hw_key_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMPDU_AGGREGATION ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MFP_CAPABLE ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_CQM_RSSI_LIST ; 
 int /*<<< orphan*/  NL80211_FEATURE_ACTIVE_MONITOR ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  PS_NULLFUNC_STACK ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGNAL_DBM ; 
 int /*<<< orphan*/  SUPPORTS_HT_CCK_RATES ; 
 int /*<<< orphan*/  SUPPORTS_RC_TABLE ; 
 TYPE_1__* devm_kmalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_hw_set (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int ieee80211_register_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mt7601u_init_debugfs (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_mac_work ; 
 int /*<<< orphan*/  mt7601u_tx_stat ; 
 int mt76_init_sband_2g (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  wiphy_ext_feature_set (struct wiphy*,int /*<<< orphan*/ ) ; 

int mt7601u_register_device(struct mt7601u_dev *dev)
{
	struct ieee80211_hw *hw = dev->hw;
	struct wiphy *wiphy = hw->wiphy;
	int ret;

	/* Reserve WCID 0 for mcast - thanks to this APs WCID will go to
	 * entry no. 1 like it does in the vendor driver.
	 */
	dev->wcid_mask[0] |= 1;

	/* init fake wcid for monitor interfaces */
	dev->mon_wcid = devm_kmalloc(dev->dev, sizeof(*dev->mon_wcid),
				     GFP_KERNEL);
	if (!dev->mon_wcid)
		return -ENOMEM;
	dev->mon_wcid->idx = 0xff;
	dev->mon_wcid->hw_key_idx = -1;

	SET_IEEE80211_DEV(hw, dev->dev);

	hw->queues = 4;
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, PS_NULLFUNC_STACK);
	ieee80211_hw_set(hw, SUPPORTS_HT_CCK_RATES);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, SUPPORTS_RC_TABLE);
	ieee80211_hw_set(hw, MFP_CAPABLE);
	hw->max_rates = 1;
	hw->max_report_rates = 7;
	hw->max_rate_tries = 1;

	hw->sta_data_size = sizeof(struct mt76_sta);
	hw->vif_data_size = sizeof(struct mt76_vif);

	SET_IEEE80211_PERM_ADDR(hw, dev->macaddr);

	wiphy->features |= NL80211_FEATURE_ACTIVE_MONITOR;
	wiphy->interface_modes = BIT(NL80211_IFTYPE_STATION);

	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	ret = mt76_init_sband_2g(dev);
	if (ret)
		return ret;

	INIT_DELAYED_WORK(&dev->mac_work, mt7601u_mac_work);
	INIT_DELAYED_WORK(&dev->stat_work, mt7601u_tx_stat);

	ret = ieee80211_register_hw(hw);
	if (ret)
		return ret;

	mt7601u_init_debugfs(dev);

	return 0;
}