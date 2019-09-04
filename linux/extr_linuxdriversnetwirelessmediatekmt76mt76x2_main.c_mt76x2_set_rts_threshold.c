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
struct ieee80211_hw {struct mt76x2_dev* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mt76x2_mac_set_tx_protection (struct mt76x2_dev*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt76x2_set_rts_threshold(struct ieee80211_hw *hw, u32 val)
{
	struct mt76x2_dev *dev = hw->priv;

	if (val != ~0 && val > 0xffff)
		return -EINVAL;

	mutex_lock(&dev->mutex);
	mt76x2_mac_set_tx_protection(dev, val);
	mutex_unlock(&dev->mutex);

	return 0;
}