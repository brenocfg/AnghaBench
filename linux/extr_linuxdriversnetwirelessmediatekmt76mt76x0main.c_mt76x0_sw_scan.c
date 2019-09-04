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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mt76x0_dev {TYPE_1__ mt76; int /*<<< orphan*/  cal_work; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct mt76x0_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_SCANNING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x0_agc_save (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt76x0_sw_scan(struct ieee80211_hw *hw,
		struct ieee80211_vif *vif,
		const u8 *mac_addr)
{
	struct mt76x0_dev *dev = hw->priv;

	cancel_delayed_work_sync(&dev->cal_work);
	mt76x0_agc_save(dev);
	set_bit(MT76_SCANNING, &dev->mt76.state);
}