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
struct mt76_wcid {int hw_key_idx; int /*<<< orphan*/  idx; } ;
struct mt76_vif {int /*<<< orphan*/  idx; struct mt76_wcid group_wcid; } ;
struct mt76_sta {struct mt76_wcid wcid; } ;
struct mt7601u_dev {int dummy; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_key_conf {int keyidx; int cipher; int /*<<< orphan*/  hw_key_idx; } ;
struct ieee80211_hw {struct mt7601u_dev* priv; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int SET_KEY ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int mt76_mac_shared_key_setup (struct mt7601u_dev*,int /*<<< orphan*/ ,int,struct ieee80211_key_conf*) ; 
 int mt76_mac_wcid_set_key (struct mt7601u_dev*,int /*<<< orphan*/ ,struct ieee80211_key_conf*) ; 

__attribute__((used)) static int
mt7601u_set_key(struct ieee80211_hw *hw, enum set_key_cmd cmd,
		struct ieee80211_vif *vif, struct ieee80211_sta *sta,
		struct ieee80211_key_conf *key)
{
	struct mt7601u_dev *dev = hw->priv;
	struct mt76_vif *mvif = (struct mt76_vif *) vif->drv_priv;
	struct mt76_sta *msta = sta ? (struct mt76_sta *) sta->drv_priv : NULL;
	struct mt76_wcid *wcid = msta ? &msta->wcid : &mvif->group_wcid;
	int idx = key->keyidx;
	int ret;

	/* fall back to sw encryption for unsupported ciphers */
	switch (key->cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
	case WLAN_CIPHER_SUITE_TKIP:
	case WLAN_CIPHER_SUITE_CCMP:
		break;
	default:
		return -EOPNOTSUPP;
	}

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
			ret = mt76_mac_wcid_set_key(dev, wcid->idx, key);
			if (ret)
				return ret;
		}

		return mt76_mac_shared_key_setup(dev, mvif->idx, idx, key);
	}

	return mt76_mac_wcid_set_key(dev, msta->wcid.idx, key);
}