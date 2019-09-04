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
struct mt76x2_vif {int /*<<< orphan*/  idx; } ;
struct TYPE_2__ {int sta; int idx; int hw_key_idx; int /*<<< orphan*/  flags; } ;
struct mt76x2_sta {TYPE_1__ wcid; int /*<<< orphan*/  rssi; struct mt76x2_vif* vif; } ;
struct mt76x2_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * wcid; int /*<<< orphan*/  wcid_mask; } ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ drv_priv; } ;
struct ieee80211_sta {int /*<<< orphan*/ * txq; int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct mt76x2_dev* priv; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  MT_WCID_FLAG_CHECK_PS ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  ewma_signal_init (int /*<<< orphan*/ *) ; 
 int mt76_wcid_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x2_mac_wcid_set_drop (struct mt76x2_dev*,int,int) ; 
 int /*<<< orphan*/  mt76x2_mac_wcid_setup (struct mt76x2_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2_txq_init (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mt76x2_sta_add(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		   struct ieee80211_sta *sta)
{
	struct mt76x2_dev *dev = hw->priv;
	struct mt76x2_sta *msta = (struct mt76x2_sta *) sta->drv_priv;
	struct mt76x2_vif *mvif = (struct mt76x2_vif *) vif->drv_priv;
	int ret = 0;
	int idx = 0;
	int i;

	mutex_lock(&dev->mutex);

	idx = mt76_wcid_alloc(dev->wcid_mask, ARRAY_SIZE(dev->wcid));
	if (idx < 0) {
		ret = -ENOSPC;
		goto out;
	}

	msta->vif = mvif;
	msta->wcid.sta = 1;
	msta->wcid.idx = idx;
	msta->wcid.hw_key_idx = -1;
	mt76x2_mac_wcid_setup(dev, idx, mvif->idx, sta->addr);
	mt76x2_mac_wcid_set_drop(dev, idx, false);
	for (i = 0; i < ARRAY_SIZE(sta->txq); i++)
		mt76x2_txq_init(dev, sta->txq[i]);

	if (vif->type == NL80211_IFTYPE_AP)
		set_bit(MT_WCID_FLAG_CHECK_PS, &msta->wcid.flags);

	ewma_signal_init(&msta->rssi);

	rcu_assign_pointer(dev->wcid[idx], &msta->wcid);

out:
	mutex_unlock(&dev->mutex);

	return ret;
}