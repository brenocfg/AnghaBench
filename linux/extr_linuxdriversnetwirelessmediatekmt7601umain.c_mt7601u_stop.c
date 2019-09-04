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
struct mt7601u_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  mac_work; int /*<<< orphan*/  cal_work; } ;
struct ieee80211_hw {struct mt7601u_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt7601u_mac_stop (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt7601u_stop(struct ieee80211_hw *hw)
{
	struct mt7601u_dev *dev = hw->priv;

	mutex_lock(&dev->mutex);

	cancel_delayed_work_sync(&dev->cal_work);
	cancel_delayed_work_sync(&dev->mac_work);
	mt7601u_mac_stop(dev);

	mutex_unlock(&dev->mutex);
}