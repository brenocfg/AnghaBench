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
typedef  int u32 ;
struct mt76x0_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  rxfilter; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  chandef; } ;
struct ieee80211_hw {TYPE_1__ conf; struct mt76x0_dev* priv; } ;

/* Variables and functions */
 int IEEE80211_CONF_CHANGE_CHANNEL ; 
 int IEEE80211_CONF_CHANGE_MONITOR ; 
 int IEEE80211_CONF_MONITOR ; 
 int /*<<< orphan*/  MT_RX_FILTR_CFG ; 
 int /*<<< orphan*/  MT_RX_FILTR_CFG_PROMISC ; 
 int /*<<< orphan*/  ieee80211_stop_queues (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt76x0_phy_set_channel (struct mt76x0_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt76x0_config(struct ieee80211_hw *hw, u32 changed)
{
	struct mt76x0_dev *dev = hw->priv;
	int ret = 0;

	mutex_lock(&dev->mutex);

	if (changed & IEEE80211_CONF_CHANGE_MONITOR) {
		if (!(hw->conf.flags & IEEE80211_CONF_MONITOR))
			dev->rxfilter |= MT_RX_FILTR_CFG_PROMISC;
		else
			dev->rxfilter &= ~MT_RX_FILTR_CFG_PROMISC;

		mt76_wr(dev, MT_RX_FILTR_CFG, dev->rxfilter);
	}

	if (changed & IEEE80211_CONF_CHANGE_CHANNEL) {
		ieee80211_stop_queues(hw);
		ret = mt76x0_phy_set_channel(dev, &hw->conf.chandef);
		ieee80211_wake_queues(hw);
	}

	mutex_unlock(&dev->mutex);

	return ret;
}