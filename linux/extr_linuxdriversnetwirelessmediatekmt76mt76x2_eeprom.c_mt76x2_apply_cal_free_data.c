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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_3__ {int* data; } ;
struct TYPE_4__ {TYPE_1__ eeprom; } ;
struct mt76x2_dev {TYPE_2__ mt76; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int MT_EE_BT_PMUCFG ; 
 int MT_EE_BT_RCAL_RESULT ; 
 int MT_EE_BT_VCDL_CALIBRATION ; 
#define  MT_EE_RF_2G_RX_HIGH_GAIN 139 
#define  MT_EE_RF_2G_TSSI_OFF_TXPOWER 138 
#define  MT_EE_RF_5G_GRP0_1_RX_HIGH_GAIN 137 
#define  MT_EE_RF_5G_GRP2_3_RX_HIGH_GAIN 136 
#define  MT_EE_RF_5G_GRP4_5_RX_HIGH_GAIN 135 
#define  MT_EE_TX_POWER_0_START_2G 134 
#define  MT_EE_TX_POWER_0_START_5G 133 
#define  MT_EE_TX_POWER_1_START_2G 132 
#define  MT_EE_TX_POWER_1_START_5G 131 
#define  MT_EE_TX_POWER_EXT_PA_5G 130 
#define  MT_EE_XTAL_TRIM_1 129 
#define  MT_TX_POWER_GROUP_SIZE_5G 128 
 int get_unaligned_le16 (int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  mt76x2_has_cal_free_data (struct mt76x2_dev*,int*) ; 

__attribute__((used)) static void
mt76x2_apply_cal_free_data(struct mt76x2_dev *dev, u8 *efuse)
{
#define GROUP_5G(_id)							   \
	MT_EE_TX_POWER_0_START_5G + MT_TX_POWER_GROUP_SIZE_5G * (_id),	   \
	MT_EE_TX_POWER_0_START_5G + MT_TX_POWER_GROUP_SIZE_5G * (_id) + 1, \
	MT_EE_TX_POWER_1_START_5G + MT_TX_POWER_GROUP_SIZE_5G * (_id),	   \
	MT_EE_TX_POWER_1_START_5G + MT_TX_POWER_GROUP_SIZE_5G * (_id) + 1

	static const u8 cal_free_bytes[] = {
		MT_EE_XTAL_TRIM_1,
		MT_EE_TX_POWER_EXT_PA_5G + 1,
		MT_EE_TX_POWER_0_START_2G,
		MT_EE_TX_POWER_0_START_2G + 1,
		MT_EE_TX_POWER_1_START_2G,
		MT_EE_TX_POWER_1_START_2G + 1,
		GROUP_5G(0),
		GROUP_5G(1),
		GROUP_5G(2),
		GROUP_5G(3),
		GROUP_5G(4),
		GROUP_5G(5),
		MT_EE_RF_2G_TSSI_OFF_TXPOWER,
		MT_EE_RF_2G_RX_HIGH_GAIN + 1,
		MT_EE_RF_5G_GRP0_1_RX_HIGH_GAIN,
		MT_EE_RF_5G_GRP0_1_RX_HIGH_GAIN + 1,
		MT_EE_RF_5G_GRP2_3_RX_HIGH_GAIN,
		MT_EE_RF_5G_GRP2_3_RX_HIGH_GAIN + 1,
		MT_EE_RF_5G_GRP4_5_RX_HIGH_GAIN,
		MT_EE_RF_5G_GRP4_5_RX_HIGH_GAIN + 1,
	};
	u8 *eeprom = dev->mt76.eeprom.data;
	u8 prev_grp0[4] = {
		eeprom[MT_EE_TX_POWER_0_START_5G],
		eeprom[MT_EE_TX_POWER_0_START_5G + 1],
		eeprom[MT_EE_TX_POWER_1_START_5G],
		eeprom[MT_EE_TX_POWER_1_START_5G + 1]
	};
	u16 val;
	int i;

	if (!mt76x2_has_cal_free_data(dev, efuse))
		return;

	for (i = 0; i < ARRAY_SIZE(cal_free_bytes); i++) {
		int offset = cal_free_bytes[i];

		eeprom[offset] = efuse[offset];
	}

	if (!(efuse[MT_EE_TX_POWER_0_START_5G] |
	      efuse[MT_EE_TX_POWER_0_START_5G + 1]))
		memcpy(eeprom + MT_EE_TX_POWER_0_START_5G, prev_grp0, 2);
	if (!(efuse[MT_EE_TX_POWER_1_START_5G] |
	      efuse[MT_EE_TX_POWER_1_START_5G + 1]))
		memcpy(eeprom + MT_EE_TX_POWER_1_START_5G, prev_grp0 + 2, 2);

	val = get_unaligned_le16(efuse + MT_EE_BT_RCAL_RESULT);
	if (val != 0xffff)
		eeprom[MT_EE_BT_RCAL_RESULT] = val & 0xff;

	val = get_unaligned_le16(efuse + MT_EE_BT_VCDL_CALIBRATION);
	if (val != 0xffff)
		eeprom[MT_EE_BT_VCDL_CALIBRATION + 1] = val >> 8;

	val = get_unaligned_le16(efuse + MT_EE_BT_PMUCFG);
	if (val != 0xffff)
		eeprom[MT_EE_BT_PMUCFG] = val & 0xff;
}