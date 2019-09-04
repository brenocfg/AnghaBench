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
struct mt76x2_dev {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct mt76x2_dev* priv; } ;
struct ieee80211_bss_conf {scalar_t__ bssid; } ;

/* Variables and functions */
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BSSID ; 
 int /*<<< orphan*/  MT_MAC_BSSID_DW0 ; 
 int /*<<< orphan*/  MT_MAC_BSSID_DW1 ; 
 int /*<<< orphan*/  get_unaligned_le16 (scalar_t__) ; 
 int /*<<< orphan*/  get_unaligned_le32 (scalar_t__) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2_apply_gain_adj (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2u_phy_channel_calibrate (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt76x2u_bss_info_changed(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			 struct ieee80211_bss_conf *info, u32 changed)
{
	struct mt76x2_dev *dev = hw->priv;

	mutex_lock(&dev->mutex);

	if (changed & BSS_CHANGED_ASSOC) {
		mt76x2u_phy_channel_calibrate(dev);
		mt76x2_apply_gain_adj(dev);
	}

	if (changed & BSS_CHANGED_BSSID) {
		mt76_wr(dev, MT_MAC_BSSID_DW0,
			get_unaligned_le32(info->bssid));
		mt76_wr(dev, MT_MAC_BSSID_DW1,
			get_unaligned_le16(info->bssid + 4));
	}

	mutex_unlock(&dev->mutex);
}