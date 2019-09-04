#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_7__ {int mcu_gain; int /*<<< orphan*/  lna_gain; } ;
struct TYPE_8__ {TYPE_3__ rx; } ;
struct TYPE_5__ {struct ieee80211_channel* chan; } ;
struct TYPE_6__ {TYPE_1__ chandef; } ;
struct mt76x2_dev {TYPE_4__ cal; TYPE_2__ mt76; } ;
struct ieee80211_channel {int hw_value; scalar_t__ band; } ;
typedef  int s8 ;
typedef  int /*<<< orphan*/  lna_5g ;

/* Variables and functions */
 int /*<<< orphan*/  MT_EE_LNA_GAIN ; 
 int /*<<< orphan*/  MT_EE_NIC_CONF_1 ; 
 int MT_EE_NIC_CONF_1_LNA_EXT_2G ; 
 int MT_EE_NIC_CONF_1_LNA_EXT_5G ; 
 int /*<<< orphan*/  MT_EE_RF_2G_RX_HIGH_GAIN ; 
 int /*<<< orphan*/  MT_EE_RSSI_OFFSET_2G_0 ; 
 int /*<<< orphan*/  MT_EE_RSSI_OFFSET_2G_1 ; 
 int /*<<< orphan*/  MT_EE_RSSI_OFFSET_5G_0 ; 
 int /*<<< orphan*/  MT_EE_RSSI_OFFSET_5G_1 ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  field_valid (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int mt76x2_eeprom_get (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 
 int mt76x2_get_5g_rx_gain (struct mt76x2_dev*,int) ; 
 int /*<<< orphan*/  mt76x2_set_rssi_offset (struct mt76x2_dev*,int,int) ; 
 int /*<<< orphan*/  mt76x2_set_rx_gain_group (struct mt76x2_dev*,int) ; 
 int /*<<< orphan*/  mt76x2_sign_extend (int,int) ; 

void mt76x2_read_rx_gain(struct mt76x2_dev *dev)
{
	struct ieee80211_channel *chan = dev->mt76.chandef.chan;
	int channel = chan->hw_value;
	s8 lna_5g[3], lna_2g;
	u8 lna;
	u16 val;

	if (chan->band == NL80211_BAND_2GHZ)
		val = mt76x2_eeprom_get(dev, MT_EE_RF_2G_RX_HIGH_GAIN) >> 8;
	else
		val = mt76x2_get_5g_rx_gain(dev, channel);

	mt76x2_set_rx_gain_group(dev, val);

	if (chan->band == NL80211_BAND_2GHZ) {
		val = mt76x2_eeprom_get(dev, MT_EE_RSSI_OFFSET_2G_0);
		mt76x2_set_rssi_offset(dev, 0, val);
		mt76x2_set_rssi_offset(dev, 1, val >> 8);
	} else {
		val = mt76x2_eeprom_get(dev, MT_EE_RSSI_OFFSET_5G_0);
		mt76x2_set_rssi_offset(dev, 0, val);
		mt76x2_set_rssi_offset(dev, 1, val >> 8);
	}

	val = mt76x2_eeprom_get(dev, MT_EE_LNA_GAIN);
	lna_2g = val & 0xff;
	lna_5g[0] = val >> 8;

	val = mt76x2_eeprom_get(dev, MT_EE_RSSI_OFFSET_2G_1);
	lna_5g[1] = val >> 8;

	val = mt76x2_eeprom_get(dev, MT_EE_RSSI_OFFSET_5G_1);
	lna_5g[2] = val >> 8;

	if (!field_valid(lna_5g[1]))
		lna_5g[1] = lna_5g[0];

	if (!field_valid(lna_5g[2]))
		lna_5g[2] = lna_5g[0];

	dev->cal.rx.mcu_gain =  (lna_2g & 0xff);
	dev->cal.rx.mcu_gain |= (lna_5g[0] & 0xff) << 8;
	dev->cal.rx.mcu_gain |= (lna_5g[1] & 0xff) << 16;
	dev->cal.rx.mcu_gain |= (lna_5g[2] & 0xff) << 24;

	val = mt76x2_eeprom_get(dev, MT_EE_NIC_CONF_1);
	if (val & MT_EE_NIC_CONF_1_LNA_EXT_2G)
		lna_2g = 0;
	if (val & MT_EE_NIC_CONF_1_LNA_EXT_5G)
		memset(lna_5g, 0, sizeof(lna_5g));

	if (chan->band == NL80211_BAND_2GHZ)
		lna = lna_2g;
	else if (channel <= 64)
		lna = lna_5g[0];
	else if (channel <= 128)
		lna = lna_5g[1];
	else
		lna = lna_5g[2];

	if (lna == 0xff)
		lna = 0;

	dev->cal.rx.lna_gain = mt76x2_sign_extend(lna, 8);
}