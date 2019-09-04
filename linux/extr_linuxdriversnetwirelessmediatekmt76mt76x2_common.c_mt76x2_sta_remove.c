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
struct TYPE_2__ {int idx; } ;
struct mt76x2_sta {TYPE_1__ wcid; } ;
struct mt76x2_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  wcid_mask; int /*<<< orphan*/  mt76; int /*<<< orphan*/ * wcid; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/ * txq; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct mt76x2_dev* priv; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_txq_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wcid_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x2_mac_wcid_set_drop (struct mt76x2_dev*,int,int) ; 
 int /*<<< orphan*/  mt76x2_mac_wcid_setup (struct mt76x2_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mt76x2_sta_remove(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		      struct ieee80211_sta *sta)
{
	struct mt76x2_dev *dev = hw->priv;
	struct mt76x2_sta *msta = (struct mt76x2_sta *) sta->drv_priv;
	int idx = msta->wcid.idx;
	int i;

	mutex_lock(&dev->mutex);
	rcu_assign_pointer(dev->wcid[idx], NULL);
	for (i = 0; i < ARRAY_SIZE(sta->txq); i++)
		mt76_txq_remove(&dev->mt76, sta->txq[i]);
	mt76x2_mac_wcid_set_drop(dev, idx, true);
	mt76_wcid_free(dev->wcid_mask, idx);
	mt76x2_mac_wcid_setup(dev, idx, 0, NULL);
	mutex_unlock(&dev->mutex);

	return 0;
}