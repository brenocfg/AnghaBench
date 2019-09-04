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
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;
struct mt76x0_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cal_work; TYPE_1__ mt76; int /*<<< orphan*/  mac_work; } ;
struct ieee80211_hw {struct mt76x0_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_CALIBRATE_INTERVAL ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mt76x0_mac_start (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt76x0_start(struct ieee80211_hw *hw)
{
	struct mt76x0_dev *dev = hw->priv;
	int ret;

	mutex_lock(&dev->mutex);

	ret = mt76x0_mac_start(dev);
	if (ret)
		goto out;

	ieee80211_queue_delayed_work(dev->mt76.hw, &dev->mac_work,
				     MT_CALIBRATE_INTERVAL);
	ieee80211_queue_delayed_work(dev->mt76.hw, &dev->cal_work,
				     MT_CALIBRATE_INTERVAL);
out:
	mutex_unlock(&dev->mutex);
	return ret;
}