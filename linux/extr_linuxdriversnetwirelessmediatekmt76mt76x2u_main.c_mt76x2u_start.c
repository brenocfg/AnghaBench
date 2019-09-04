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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mt76x2_dev {int /*<<< orphan*/  mutex; TYPE_1__ mt76; } ;
struct ieee80211_hw {struct mt76x2_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_STATE_RUNNING ; 
 int mt76x2u_mac_start (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt76x2u_start(struct ieee80211_hw *hw)
{
	struct mt76x2_dev *dev = hw->priv;
	int ret;

	mutex_lock(&dev->mutex);

	ret = mt76x2u_mac_start(dev);
	if (ret)
		goto out;

	set_bit(MT76_STATE_RUNNING, &dev->mt76.state);

out:
	mutex_unlock(&dev->mutex);
	return ret;
}