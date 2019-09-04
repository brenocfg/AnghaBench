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
struct mt76x0_dev {int dummy; } ;
struct mt76_wcid {int hw_key_idx; int /*<<< orphan*/  idx; } ;
struct mt76_vif {int /*<<< orphan*/  idx; struct mt76_wcid group_wcid; } ;
struct mt76_sta {struct mt76_wcid wcid; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_key_conf {int keyidx; int /*<<< orphan*/  hw_key_idx; } ;
struct ieee80211_hw {struct mt76x0_dev* priv; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;

/* Variables and functions */
 int SET_KEY ; 
 int mt76x0_mac_shared_key_setup (struct mt76x0_dev*,int /*<<< orphan*/ ,int,struct ieee80211_key_conf*) ; 
 int mt76x0_mac_wcid_set_key (struct mt76x0_dev*,int /*<<< orphan*/ ,struct ieee80211_key_conf*) ; 

__attribute__((used)) static int
mt76x0_set_key(struct ieee80211_hw *hw, enum set_key_cmd cmd,
		struct ieee80211_vif *vif, struct ieee80211_sta *sta,
		struct ieee80211_key_conf *key)
{
	struct mt76x0_dev *dev = hw->priv;
	struct mt76_vif *mvif = (struct mt76_vif *) vif->drv_priv;
	struct mt76_sta *msta = sta ? (struct mt76_sta *) sta->drv_priv : NULL;
	struct mt76_wcid *wcid = msta ? &msta->wcid : &mvif->group_wcid;
	int idx = key->keyidx;
	int ret;

	if (cmd == SET_KEY) {
		key->hw_key_idx = wcid->idx;
		wcid->hw_key_idx = idx;
	} else {
		if (idx == wcid->hw_key_idx)
			wcid->hw_key_idx = -1;

		key = NULL;
	}

	if (!msta) {
		if (key || wcid->hw_key_idx == idx) {
			ret = mt76x0_mac_wcid_set_key(dev, wcid->idx, key);
			if (ret)
				return ret;
		}

		return mt76x0_mac_shared_key_setup(dev, mvif->idx, idx, key);
	}

	return mt76x0_mac_wcid_set_key(dev, msta->wcid.idx, key);
}