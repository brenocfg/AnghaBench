#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct mt76x2_dev {TYPE_1__ mt76; int /*<<< orphan*/  cal_work; } ;
struct cfg80211_chan_def {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  MT76_RESET ; 
 int /*<<< orphan*/  MT_TXOP_CTRL_CFG ; 
 int /*<<< orphan*/  MT_TXOP_HLDR_ET ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set_channel (TYPE_1__*) ; 
 int /*<<< orphan*/  mt76_txq_schedule_all (TYPE_1__*) ; 
 int /*<<< orphan*/  mt76x2_mac_stop (struct mt76x2_dev*,int) ; 
 int /*<<< orphan*/  mt76x2u_mac_resume (struct mt76x2_dev*) ; 
 int mt76x2u_phy_set_channel (struct mt76x2_dev*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt76x2u_set_channel(struct mt76x2_dev *dev,
		    struct cfg80211_chan_def *chandef)
{
	int err;

	cancel_delayed_work_sync(&dev->cal_work);
	set_bit(MT76_RESET, &dev->mt76.state);

	mt76_set_channel(&dev->mt76);

	mt76_clear(dev, MT_TXOP_CTRL_CFG, BIT(20));
	mt76_clear(dev, MT_TXOP_HLDR_ET, BIT(1));
	mt76x2_mac_stop(dev, false);

	err = mt76x2u_phy_set_channel(dev, chandef);

	mt76x2u_mac_resume(dev);

	clear_bit(MT76_RESET, &dev->mt76.state);
	mt76_txq_schedule_all(&dev->mt76);

	return err;
}