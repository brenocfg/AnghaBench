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
struct mt7601u_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cal_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  mac_work; } ;
struct ieee80211_hw {struct mt7601u_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_CALIBRATE_INTERVAL ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mt7601u_mac_start (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt7601u_start(struct ieee80211_hw *hw)
{
	struct mt7601u_dev *dev = hw->priv;
	int ret;

	mutex_lock(&dev->mutex);

	ret = mt7601u_mac_start(dev);
	if (ret)
		goto out;

	ieee80211_queue_delayed_work(dev->hw, &dev->mac_work,
				     MT_CALIBRATE_INTERVAL);
	ieee80211_queue_delayed_work(dev->hw, &dev->cal_work,
				     MT_CALIBRATE_INTERVAL);
out:
	mutex_unlock(&dev->mutex);
	return ret;
}