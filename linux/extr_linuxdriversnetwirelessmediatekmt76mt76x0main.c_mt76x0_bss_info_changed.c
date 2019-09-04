#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct mt76x0_dev {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct mt76x0_dev* priv; } ;
struct ieee80211_bss_conf {int basic_rates; scalar_t__ use_short_slot; int /*<<< orphan*/  use_short_preamble; int /*<<< orphan*/  ht_operation_mode; int /*<<< orphan*/  use_cts_prot; int /*<<< orphan*/  beacon_int; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BASIC_RATES ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_BSSID ; 
 int BSS_CHANGED_ERP_CTS_PROT ; 
 int BSS_CHANGED_ERP_PREAMBLE ; 
 int BSS_CHANGED_ERP_SLOT ; 
 int BSS_CHANGED_HT ; 
 int /*<<< orphan*/  MT_BKOFF_SLOT_CFG ; 
 int /*<<< orphan*/  MT_BKOFF_SLOT_CFG_SLOTTIME ; 
 int /*<<< orphan*/  MT_HT_FBK_CFG0 ; 
 int /*<<< orphan*/  MT_HT_FBK_CFG1 ; 
 int /*<<< orphan*/  MT_LEGACY_BASIC_RATE ; 
 int /*<<< orphan*/  MT_LG_FBK_CFG0 ; 
 int /*<<< orphan*/  MT_LG_FBK_CFG1 ; 
 int /*<<< orphan*/  MT_MAC_BSSID_DW0 ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x0_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x0_addr_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x0_mac_config_tsf (struct mt76x0_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x0_mac_set_protection (struct mt76x0_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x0_mac_set_short_preamble (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x0_phy_con_cal_onoff (struct mt76x0_dev*,struct ieee80211_bss_conf*) ; 
 int /*<<< orphan*/  mt76x0_phy_recalibrate_after_assoc (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt76x0_bss_info_changed(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			 struct ieee80211_bss_conf *info, u32 changed)
{
	struct mt76x0_dev *dev = hw->priv;

	mutex_lock(&dev->mutex);

	if (changed & BSS_CHANGED_ASSOC)
		mt76x0_phy_con_cal_onoff(dev, info);

	if (changed & BSS_CHANGED_BSSID) {
		mt76x0_addr_wr(dev, MT_MAC_BSSID_DW0, info->bssid);

		/* Note: this is a hack because beacon_int is not changed
		 *	 on leave nor is any more appropriate event generated.
		 *	 rt2x00 doesn't seem to be bothered though.
		 */
		if (is_zero_ether_addr(info->bssid))
			mt76x0_mac_config_tsf(dev, false, 0);
	}

	if (changed & BSS_CHANGED_BASIC_RATES) {
		mt76_wr(dev, MT_LEGACY_BASIC_RATE, info->basic_rates);
		mt76_wr(dev, MT_HT_FBK_CFG0, 0x65432100);
		mt76_wr(dev, MT_HT_FBK_CFG1, 0xedcba980);
		mt76_wr(dev, MT_LG_FBK_CFG0, 0xedcba988);
		mt76_wr(dev, MT_LG_FBK_CFG1, 0x00002100);
	}

	if (changed & BSS_CHANGED_BEACON_INT)
		mt76x0_mac_config_tsf(dev, true, info->beacon_int);

	if (changed & BSS_CHANGED_HT || changed & BSS_CHANGED_ERP_CTS_PROT)
		mt76x0_mac_set_protection(dev, info->use_cts_prot,
					   info->ht_operation_mode);

	if (changed & BSS_CHANGED_ERP_PREAMBLE)
		mt76x0_mac_set_short_preamble(dev, info->use_short_preamble);

	if (changed & BSS_CHANGED_ERP_SLOT) {
		int slottime = info->use_short_slot ? 9 : 20;

		mt76_rmw_field(dev, MT_BKOFF_SLOT_CFG,
			       MT_BKOFF_SLOT_CFG_SLOTTIME, slottime);
	}

	if (changed & BSS_CHANGED_ASSOC)
		mt76x0_phy_recalibrate_after_assoc(dev);

	mutex_unlock(&dev->mutex);
}