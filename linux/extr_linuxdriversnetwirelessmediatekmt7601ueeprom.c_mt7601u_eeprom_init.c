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
typedef  scalar_t__ u8 ;
struct mt7601u_dev {TYPE_1__* ee; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ lna_gain; scalar_t__ ref_temp; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MT7601U_EEPROM_SIZE ; 
 scalar_t__ MT7601U_EE_MAX_VER ; 
 size_t MT_EE_LNA_GAIN ; 
 int MT_EE_MAC_ADDR ; 
 int /*<<< orphan*/  MT_EE_READ ; 
 size_t MT_EE_REF_TEMP ; 
 size_t MT_EE_VERSION_EE ; 
 size_t MT_EE_VERSION_FAE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 TYPE_1__* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7601u_config_tx_power_per_rate (struct mt7601u_dev*,scalar_t__*) ; 
 int mt7601u_efuse_physical_size_check (struct mt7601u_dev*) ; 
 int mt7601u_efuse_read (struct mt7601u_dev*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7601u_init_tssi_params (struct mt7601u_dev*,scalar_t__*) ; 
 int /*<<< orphan*/  mt7601u_set_channel_power (struct mt7601u_dev*,scalar_t__*) ; 
 int /*<<< orphan*/  mt7601u_set_chip_cap (struct mt7601u_dev*,scalar_t__*) ; 
 int /*<<< orphan*/  mt7601u_set_country_reg (struct mt7601u_dev*,scalar_t__*) ; 
 int /*<<< orphan*/  mt7601u_set_macaddr (struct mt7601u_dev*,scalar_t__*) ; 
 int /*<<< orphan*/  mt7601u_set_rf_freq_off (struct mt7601u_dev*,scalar_t__*) ; 
 int /*<<< orphan*/  mt7601u_set_rssi_offset (struct mt7601u_dev*,scalar_t__*) ; 

int
mt7601u_eeprom_init(struct mt7601u_dev *dev)
{
	u8 *eeprom;
	int i, ret;

	ret = mt7601u_efuse_physical_size_check(dev);
	if (ret)
		return ret;

	dev->ee = devm_kzalloc(dev->dev, sizeof(*dev->ee), GFP_KERNEL);
	if (!dev->ee)
		return -ENOMEM;

	eeprom = kmalloc(MT7601U_EEPROM_SIZE, GFP_KERNEL);
	if (!eeprom)
		return -ENOMEM;

	for (i = 0; i + 16 <= MT7601U_EEPROM_SIZE; i += 16) {
		ret = mt7601u_efuse_read(dev, i, eeprom + i, MT_EE_READ);
		if (ret)
			goto out;
	}

	if (eeprom[MT_EE_VERSION_EE] > MT7601U_EE_MAX_VER)
		dev_warn(dev->dev,
			 "Warning: unsupported EEPROM version %02hhx\n",
			 eeprom[MT_EE_VERSION_EE]);
	dev_info(dev->dev, "EEPROM ver:%02hhx fae:%02hhx\n",
		 eeprom[MT_EE_VERSION_EE], eeprom[MT_EE_VERSION_FAE]);

	mt7601u_set_macaddr(dev, eeprom + MT_EE_MAC_ADDR);
	mt7601u_set_chip_cap(dev, eeprom);
	mt7601u_set_channel_power(dev, eeprom);
	mt7601u_set_country_reg(dev, eeprom);
	mt7601u_set_rf_freq_off(dev, eeprom);
	mt7601u_set_rssi_offset(dev, eeprom);
	dev->ee->ref_temp = eeprom[MT_EE_REF_TEMP];
	dev->ee->lna_gain = eeprom[MT_EE_LNA_GAIN];

	mt7601u_config_tx_power_per_rate(dev, eeprom);

	mt7601u_init_tssi_params(dev, eeprom);
out:
	kfree(eeprom);
	return ret;
}