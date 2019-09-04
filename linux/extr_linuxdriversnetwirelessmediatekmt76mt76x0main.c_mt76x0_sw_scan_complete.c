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
struct TYPE_2__ {int /*<<< orphan*/  hw; int /*<<< orphan*/  state; } ;
struct mt76x0_dev {int /*<<< orphan*/  cal_work; TYPE_1__ mt76; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct mt76x0_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_SCANNING ; 
 int /*<<< orphan*/  MT_CALIBRATE_INTERVAL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x0_agc_restore (struct mt76x0_dev*) ; 

__attribute__((used)) static void
mt76x0_sw_scan_complete(struct ieee80211_hw *hw,
			 struct ieee80211_vif *vif)
{
	struct mt76x0_dev *dev = hw->priv;

	mt76x0_agc_restore(dev);
	clear_bit(MT76_SCANNING, &dev->mt76.state);

	ieee80211_queue_delayed_work(dev->mt76.hw, &dev->cal_work,
				     MT_CALIBRATE_INTERVAL);
}