#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct ieee80211_channel* chan; } ;
struct TYPE_4__ {TYPE_1__ chandef; } ;
struct mt76x2_dev {TYPE_2__ mt76; } ;
struct ieee80211_channel {scalar_t__ band; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCU_CAL_LC ; 
 int /*<<< orphan*/  MCU_CAL_RXIQC_FI ; 
 int /*<<< orphan*/  MCU_CAL_TEMP_SENSOR ; 
 int /*<<< orphan*/  MCU_CAL_TXIQ ; 
 int /*<<< orphan*/  MCU_CAL_TX_LOFT ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ mt76x2_channel_silent (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2u_mac_resume (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2u_mac_stop (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76x2u_mcu_calibrate (struct mt76x2_dev*,int /*<<< orphan*/ ,int) ; 

void mt76x2u_phy_channel_calibrate(struct mt76x2_dev *dev)
{
	struct ieee80211_channel *chan = dev->mt76.chandef.chan;
	bool is_5ghz = chan->band == NL80211_BAND_5GHZ;

	if (mt76x2_channel_silent(dev))
		return;

	mt76x2u_mac_stop(dev);

	if (is_5ghz)
		mt76x2u_mcu_calibrate(dev, MCU_CAL_LC, 0);

	mt76x2u_mcu_calibrate(dev, MCU_CAL_TX_LOFT, is_5ghz);
	mt76x2u_mcu_calibrate(dev, MCU_CAL_TXIQ, is_5ghz);
	mt76x2u_mcu_calibrate(dev, MCU_CAL_RXIQC_FI, is_5ghz);
	mt76x2u_mcu_calibrate(dev, MCU_CAL_TEMP_SENSOR, 0);

	mt76x2u_mac_resume(dev);
}