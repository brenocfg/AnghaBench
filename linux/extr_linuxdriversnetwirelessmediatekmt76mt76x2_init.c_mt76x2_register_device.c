#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct wiphy {int n_addresses; int n_iface_combinations; int interface_modes; int /*<<< orphan*/  reg_notifier; TYPE_4__* iface_combinations; TYPE_4__* addresses; } ;
struct mt76x2_tx_status {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  sband; } ;
struct TYPE_10__ {int /*<<< orphan*/  sband; } ;
struct TYPE_9__ {int /*<<< orphan*/  blink_set; int /*<<< orphan*/  brightness_set; } ;
struct TYPE_13__ {TYPE_3__ sband_5g; TYPE_2__ sband_2g; TYPE_1__ led_cdev; int /*<<< orphan*/  macaddr; int /*<<< orphan*/  dev; } ;
struct mt76x2_dev {TYPE_5__ mt76; TYPE_4__* macaddr_list; int /*<<< orphan*/  mac_work; int /*<<< orphan*/  cal_work; int /*<<< orphan*/  txstatus_fifo; } ;
struct ieee80211_hw {struct wiphy* wiphy; } ;
struct TYPE_12__ {int* addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  CONFIG_MT76_LEDS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_VHT_IBSS ; 
 int NL80211_IFTYPE_ADHOC ; 
 int NL80211_IFTYPE_AP ; 
 int NL80211_IFTYPE_STATION ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* if_comb ; 
 int /*<<< orphan*/  kfifo_init (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_hw* mt76_hw (struct mt76x2_dev*) ; 
 int mt76_register_device (TYPE_5__*,int,TYPE_4__*,int) ; 
 int /*<<< orphan*/  mt76x2_dfs_init_detector (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2_init_debugfs (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2_init_device (struct mt76x2_dev*) ; 
 int mt76x2_init_hardware (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2_init_txpower (struct mt76x2_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x2_led_set_blink ; 
 int /*<<< orphan*/  mt76x2_led_set_brightness ; 
 int /*<<< orphan*/  mt76x2_mac_work ; 
 int /*<<< orphan*/  mt76x2_phy_calibrate ; 
 TYPE_4__* mt76x2_rates ; 
 int /*<<< orphan*/  mt76x2_regd_notifier ; 
 int /*<<< orphan*/  mt76x2_stop_hardware (struct mt76x2_dev*) ; 
 int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  wiphy_ext_feature_set (struct wiphy*,int /*<<< orphan*/ ) ; 

int mt76x2_register_device(struct mt76x2_dev *dev)
{
	struct ieee80211_hw *hw = mt76_hw(dev);
	struct wiphy *wiphy = hw->wiphy;
	void *status_fifo;
	int fifo_size;
	int i, ret;

	fifo_size = roundup_pow_of_two(32 * sizeof(struct mt76x2_tx_status));
	status_fifo = devm_kzalloc(dev->mt76.dev, fifo_size, GFP_KERNEL);
	if (!status_fifo)
		return -ENOMEM;

	kfifo_init(&dev->txstatus_fifo, status_fifo, fifo_size);
	INIT_DELAYED_WORK(&dev->cal_work, mt76x2_phy_calibrate);
	INIT_DELAYED_WORK(&dev->mac_work, mt76x2_mac_work);

	mt76x2_init_device(dev);

	ret = mt76x2_init_hardware(dev);
	if (ret)
		return ret;

	for (i = 0; i < ARRAY_SIZE(dev->macaddr_list); i++) {
		u8 *addr = dev->macaddr_list[i].addr;

		memcpy(addr, dev->mt76.macaddr, ETH_ALEN);

		if (!i)
			continue;

		addr[0] |= BIT(1);
		addr[0] ^= ((i - 1) << 2);
	}
	wiphy->addresses = dev->macaddr_list;
	wiphy->n_addresses = ARRAY_SIZE(dev->macaddr_list);

	wiphy->iface_combinations = if_comb;
	wiphy->n_iface_combinations = ARRAY_SIZE(if_comb);

	wiphy->reg_notifier = mt76x2_regd_notifier;

	wiphy->interface_modes =
		BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_AP) |
#ifdef CONFIG_MAC80211_MESH
		BIT(NL80211_IFTYPE_MESH_POINT) |
#endif
		BIT(NL80211_IFTYPE_ADHOC);

	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_VHT_IBSS);

	mt76x2_dfs_init_detector(dev);

	/* init led callbacks */
	if (IS_ENABLED(CONFIG_MT76_LEDS)) {
		dev->mt76.led_cdev.brightness_set = mt76x2_led_set_brightness;
		dev->mt76.led_cdev.blink_set = mt76x2_led_set_blink;
	}

	ret = mt76_register_device(&dev->mt76, true, mt76x2_rates,
				   ARRAY_SIZE(mt76x2_rates));
	if (ret)
		goto fail;

	mt76x2_init_debugfs(dev);
	mt76x2_init_txpower(dev, &dev->mt76.sband_2g.sband);
	mt76x2_init_txpower(dev, &dev->mt76.sband_5g.sband);

	return 0;

fail:
	mt76x2_stop_hardware(dev);
	return ret;
}