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
struct mt76x2_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  coverage_class; } ;
struct ieee80211_hw {struct mt76x2_dev* priv; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  mt76x2_set_tx_ackto (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt76x2_set_coverage_class(struct ieee80211_hw *hw,
				      s16 coverage_class)
{
	struct mt76x2_dev *dev = hw->priv;

	mutex_lock(&dev->mutex);
	dev->coverage_class = coverage_class;
	mt76x2_set_tx_ackto(dev);
	mutex_unlock(&dev->mutex);
}