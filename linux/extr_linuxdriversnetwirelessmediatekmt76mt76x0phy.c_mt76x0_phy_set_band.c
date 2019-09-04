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
struct mt76x0_dev {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  MT_RF (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_TX0_RF_GAIN_CORR ; 
 int /*<<< orphan*/  MT_TX_ALC_VGA3 ; 
 int /*<<< orphan*/  MT_TX_BAND_CFG ; 
 int /*<<< orphan*/  MT_TX_BAND_CFG_2G ; 
 int /*<<< orphan*/  MT_TX_BAND_CFG_5G ; 
#define  NL80211_BAND_2GHZ 129 
#define  NL80211_BAND_5GHZ 128 
 int /*<<< orphan*/  RF_RANDOM_WRITE (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x0_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x0_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x0_rf_2g_channel_0_tab ; 
 int /*<<< orphan*/  mt76x0_rf_5g_channel_0_tab ; 
 int /*<<< orphan*/  rf_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mt76x0_phy_set_band(struct mt76x0_dev *dev, enum nl80211_band band)
{
	switch (band) {
	case NL80211_BAND_2GHZ:
		RF_RANDOM_WRITE(dev, mt76x0_rf_2g_channel_0_tab);

		rf_wr(dev, MT_RF(5, 0), 0x45);
		rf_wr(dev, MT_RF(6, 0), 0x44);

		mt76_set(dev, MT_TX_BAND_CFG, MT_TX_BAND_CFG_2G);
		mt76_clear(dev, MT_TX_BAND_CFG, MT_TX_BAND_CFG_5G);

		mt76_wr(dev, MT_TX_ALC_VGA3, 0x00050007);
		mt76_wr(dev, MT_TX0_RF_GAIN_CORR, 0x003E0002);
		break;
	case NL80211_BAND_5GHZ:
		RF_RANDOM_WRITE(dev, mt76x0_rf_5g_channel_0_tab);

		rf_wr(dev, MT_RF(5, 0), 0x44);
		rf_wr(dev, MT_RF(6, 0), 0x45);

		mt76_clear(dev, MT_TX_BAND_CFG, MT_TX_BAND_CFG_2G);
		mt76_set(dev, MT_TX_BAND_CFG, MT_TX_BAND_CFG_5G);

		mt76_wr(dev, MT_TX_ALC_VGA3, 0x00000005);
		mt76_wr(dev, MT_TX0_RF_GAIN_CORR, 0x01010102);
		break;
	default:
		break;
	}
}