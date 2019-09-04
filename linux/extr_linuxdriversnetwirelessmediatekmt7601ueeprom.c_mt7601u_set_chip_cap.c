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
typedef  int u16 ;
struct mt7601u_dev {int /*<<< orphan*/  dev; TYPE_1__* ee; } ;
struct TYPE_2__ {int tssi_enabled; } ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int MT_EE_NIC_CONF_0 ; 
 int /*<<< orphan*/  MT_EE_NIC_CONF_0_RX_PATH ; 
 int /*<<< orphan*/  MT_EE_NIC_CONF_0_TX_PATH ; 
 int MT_EE_NIC_CONF_1 ; 
 int MT_EE_NIC_CONF_1_HW_RF_CTRL ; 
 int MT_EE_NIC_CONF_1_TEMP_TX_ALC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  field_valid (int) ; 
 int get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 scalar_t__ mt7601u_has_tssi (struct mt7601u_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt7601u_set_chip_cap(struct mt7601u_dev *dev, u8 *eeprom)
{
	u16 nic_conf0 = get_unaligned_le16(eeprom + MT_EE_NIC_CONF_0);
	u16 nic_conf1 = get_unaligned_le16(eeprom + MT_EE_NIC_CONF_1);

	if (!field_valid(nic_conf1 & 0xff))
		nic_conf1 &= 0xff00;

	dev->ee->tssi_enabled = mt7601u_has_tssi(dev, eeprom) &&
				!(nic_conf1 & MT_EE_NIC_CONF_1_TEMP_TX_ALC);

	if (nic_conf1 & MT_EE_NIC_CONF_1_HW_RF_CTRL)
		dev_err(dev->dev,
			"Error: this driver does not support HW RF ctrl\n");

	if (!field_valid(nic_conf0 >> 8))
		return;

	if (FIELD_GET(MT_EE_NIC_CONF_0_RX_PATH, nic_conf0) > 1 ||
	    FIELD_GET(MT_EE_NIC_CONF_0_TX_PATH, nic_conf0) > 1)
		dev_err(dev->dev,
			"Error: device has more than 1 RX/TX stream!\n");
}