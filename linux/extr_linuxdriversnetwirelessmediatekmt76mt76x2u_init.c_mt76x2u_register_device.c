#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wiphy {int /*<<< orphan*/  interface_modes; } ;
struct TYPE_8__ {int /*<<< orphan*/  sband; } ;
struct TYPE_7__ {int /*<<< orphan*/  sband; } ;
struct TYPE_9__ {TYPE_2__ sband_5g; TYPE_1__ sband_2g; int /*<<< orphan*/  state; } ;
struct mt76x2_dev {TYPE_3__ mt76; int /*<<< orphan*/  cal_work; } ;
struct ieee80211_hw {int max_tx_fragments; struct wiphy* wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT76_STATE_INITIALIZED ; 
 int MT_SG_MAX_SIZE ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 struct ieee80211_hw* mt76_hw (struct mt76x2_dev*) ; 
 int mt76_register_device (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt76u_alloc_queues (TYPE_3__*) ; 
 scalar_t__ mt76u_check_sg (TYPE_3__*) ; 
 int mt76u_mcu_init_rx (TYPE_3__*) ; 
 int /*<<< orphan*/  mt76x2_init_debugfs (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2_init_device (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2_init_txpower (struct mt76x2_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x2_rates ; 
 int /*<<< orphan*/  mt76x2u_cleanup (struct mt76x2_dev*) ; 
 int mt76x2u_init_eeprom (struct mt76x2_dev*) ; 
 int mt76x2u_init_hardware (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2u_phy_calibrate ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mt76x2u_register_device(struct mt76x2_dev *dev)
{
	struct ieee80211_hw *hw = mt76_hw(dev);
	struct wiphy *wiphy = hw->wiphy;
	int err;

	INIT_DELAYED_WORK(&dev->cal_work, mt76x2u_phy_calibrate);
	mt76x2_init_device(dev);

	err = mt76x2u_init_eeprom(dev);
	if (err < 0)
		return err;

	err = mt76u_mcu_init_rx(&dev->mt76);
	if (err < 0)
		return err;

	err = mt76u_alloc_queues(&dev->mt76);
	if (err < 0)
		goto fail;

	err = mt76x2u_init_hardware(dev);
	if (err < 0)
		goto fail;

	wiphy->interface_modes = BIT(NL80211_IFTYPE_STATION);

	err = mt76_register_device(&dev->mt76, true, mt76x2_rates,
				   ARRAY_SIZE(mt76x2_rates));
	if (err)
		goto fail;

	/* check hw sg support in order to enable AMSDU */
	if (mt76u_check_sg(&dev->mt76))
		hw->max_tx_fragments = MT_SG_MAX_SIZE;
	else
		hw->max_tx_fragments = 1;

	set_bit(MT76_STATE_INITIALIZED, &dev->mt76.state);

	mt76x2_init_debugfs(dev);
	mt76x2_init_txpower(dev, &dev->mt76.sband_2g.sband);
	mt76x2_init_txpower(dev, &dev->mt76.sband_5g.sband);

	return 0;

fail:
	mt76x2u_cleanup(dev);
	return err;
}