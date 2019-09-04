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
struct mt76x2_vif {int /*<<< orphan*/  idx; } ;
struct mt76x2_dev {int beacon_int; int slottime; int /*<<< orphan*/  mutex; int /*<<< orphan*/  pre_tbtt_tasklet; scalar_t__ tbtt_count; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct mt76x2_dev* priv; } ;
struct ieee80211_bss_conf {int beacon_int; scalar_t__ use_short_slot; int /*<<< orphan*/  enable_beacon; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_BSSID ; 
 int BSS_CHANGED_ERP_SLOT ; 
 int /*<<< orphan*/  MT_BEACON_TIME_CFG ; 
 int /*<<< orphan*/  MT_BEACON_TIME_CFG_INTVAL ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x2_mac_set_beacon_enable (struct mt76x2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2_mac_set_bssid (struct mt76x2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2_set_tx_ackto (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt76x2_bss_info_changed(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			struct ieee80211_bss_conf *info, u32 changed)
{
	struct mt76x2_dev *dev = hw->priv;
	struct mt76x2_vif *mvif = (struct mt76x2_vif *) vif->drv_priv;

	mutex_lock(&dev->mutex);

	if (changed & BSS_CHANGED_BSSID)
		mt76x2_mac_set_bssid(dev, mvif->idx, info->bssid);

	if (changed & BSS_CHANGED_BEACON_INT) {
		mt76_rmw_field(dev, MT_BEACON_TIME_CFG,
			       MT_BEACON_TIME_CFG_INTVAL,
			       info->beacon_int << 4);
		dev->beacon_int = info->beacon_int;
		dev->tbtt_count = 0;
	}

	if (changed & BSS_CHANGED_BEACON_ENABLED) {
		tasklet_disable(&dev->pre_tbtt_tasklet);
		mt76x2_mac_set_beacon_enable(dev, mvif->idx,
					     info->enable_beacon);
		tasklet_enable(&dev->pre_tbtt_tasklet);
	}

	if (changed & BSS_CHANGED_ERP_SLOT) {
		int slottime = info->use_short_slot ? 9 : 20;

		dev->slottime = slottime;
		mt76x2_set_tx_ackto(dev);
	}

	mutex_unlock(&dev->mutex);
}