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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct mt76x0_dev {TYPE_2__* ee; TYPE_1__ mt76; } ;
struct TYPE_4__ {int has_5ghz; int has_2ghz; int pa_type; } ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int MT_EE_NIC_CONF_0 ; 
 int /*<<< orphan*/  MT_EE_NIC_CONF_0_BOARD_TYPE ; 
 int /*<<< orphan*/  MT_EE_NIC_CONF_0_PA_TYPE ; 
 int /*<<< orphan*/  MT_EE_NIC_CONF_0_RX_PATH ; 
 int /*<<< orphan*/  MT_EE_NIC_CONF_0_TX_PATH ; 
 int MT_EE_NIC_CONF_1 ; 
 int MT_EE_NIC_CONF_1_HW_RF_CTRL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  field_valid (int) ; 
 int get_unaligned_le16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt76x0_set_chip_cap(struct mt76x0_dev *dev, u8 *eeprom)
{
	enum mt76x2_board_type { BOARD_TYPE_2GHZ = 1, BOARD_TYPE_5GHZ = 2 };
	u16 nic_conf0 = get_unaligned_le16(eeprom + MT_EE_NIC_CONF_0);
	u16 nic_conf1 = get_unaligned_le16(eeprom + MT_EE_NIC_CONF_1);

	dev_dbg(dev->mt76.dev, "NIC_CONF0: %04x NIC_CONF1: %04x\n", nic_conf0, nic_conf1);

	switch (FIELD_GET(MT_EE_NIC_CONF_0_BOARD_TYPE, nic_conf0)) {
	case BOARD_TYPE_5GHZ:
		dev->ee->has_5ghz = true;
		break;
	case BOARD_TYPE_2GHZ:
		dev->ee->has_2ghz = true;
		break;
	default:
		dev->ee->has_2ghz = true;
		dev->ee->has_5ghz = true;
		break;
	}

	dev_dbg(dev->mt76.dev, "Has 2GHZ %d 5GHZ %d\n", dev->ee->has_2ghz, dev->ee->has_5ghz);

	if (!field_valid(nic_conf1 & 0xff))
		nic_conf1 &= 0xff00;

	if (nic_conf1 & MT_EE_NIC_CONF_1_HW_RF_CTRL)
		dev_err(dev->mt76.dev,
			"Error: this driver does not support HW RF ctrl\n");

	if (!field_valid(nic_conf0 >> 8))
		return;

	if (FIELD_GET(MT_EE_NIC_CONF_0_RX_PATH, nic_conf0) > 1 ||
	    FIELD_GET(MT_EE_NIC_CONF_0_TX_PATH, nic_conf0) > 1)
		dev_err(dev->mt76.dev,
			"Error: device has more than 1 RX/TX stream!\n");

	dev->ee->pa_type = FIELD_GET(MT_EE_NIC_CONF_0_PA_TYPE, nic_conf0);
	dev_dbg(dev->mt76.dev, "PA Type %d\n", dev->ee->pa_type);
}