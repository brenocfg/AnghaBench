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
struct mt76x0_dev {int /*<<< orphan*/  hw_atomic_mutex; } ;
struct cfg80211_chan_def {int dummy; } ;

/* Variables and functions */
 int __mt76x0_phy_set_channel (struct mt76x0_dev*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mt76x0_phy_set_channel(struct mt76x0_dev *dev,
			   struct cfg80211_chan_def *chandef)
{
	int ret;

	mutex_lock(&dev->hw_atomic_mutex);
	ret = __mt76x0_phy_set_channel(dev, chandef);
	mutex_unlock(&dev->hw_atomic_mutex);

	return ret;
}