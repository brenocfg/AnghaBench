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
struct pcie_service_card {TYPE_1__* dev; } ;
struct mwifiex_adapter {int /*<<< orphan*/  fw_name; struct pcie_service_card* card; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 int CHIP_MAGIC_VALUE ; 
 int CHIP_VER_PCIEUART ; 
 int /*<<< orphan*/  PCIE8766_DEFAULT_FW_NAME ; 
#define  PCIE8897_A0 132 
 int /*<<< orphan*/  PCIE8897_A0_FW_NAME ; 
#define  PCIE8897_B0 131 
 int /*<<< orphan*/  PCIE8897_B0_FW_NAME ; 
 int /*<<< orphan*/  PCIE8897_DEFAULT_FW_NAME ; 
 int PCIE8997_A1 ; 
 int /*<<< orphan*/  PCIEUART8997_FW_NAME_V4 ; 
 int /*<<< orphan*/  PCIEUSB8997_FW_NAME_V4 ; 
#define  PCIE_DEVICE_ID_MARVELL_88W8766P 130 
#define  PCIE_DEVICE_ID_MARVELL_88W8897 129 
#define  PCIE_DEVICE_ID_MARVELL_88W8997 128 
 int /*<<< orphan*/  mwifiex_read_reg (struct mwifiex_adapter*,int,int*) ; 
 int /*<<< orphan*/  mwifiex_write_reg (struct mwifiex_adapter*,int,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mwifiex_pcie_get_fw_name(struct mwifiex_adapter *adapter)
{
	int revision_id = 0;
	int version, magic;
	struct pcie_service_card *card = adapter->card;

	switch (card->dev->device) {
	case PCIE_DEVICE_ID_MARVELL_88W8766P:
		strcpy(adapter->fw_name, PCIE8766_DEFAULT_FW_NAME);
		break;
	case PCIE_DEVICE_ID_MARVELL_88W8897:
		mwifiex_write_reg(adapter, 0x0c58, 0x80c00000);
		mwifiex_read_reg(adapter, 0x0c58, &revision_id);
		revision_id &= 0xff00;
		switch (revision_id) {
		case PCIE8897_A0:
			strcpy(adapter->fw_name, PCIE8897_A0_FW_NAME);
			break;
		case PCIE8897_B0:
			strcpy(adapter->fw_name, PCIE8897_B0_FW_NAME);
			break;
		default:
			strcpy(adapter->fw_name, PCIE8897_DEFAULT_FW_NAME);

			break;
		}
		break;
	case PCIE_DEVICE_ID_MARVELL_88W8997:
		mwifiex_read_reg(adapter, 0x8, &revision_id);
		mwifiex_read_reg(adapter, 0x0cd0, &version);
		mwifiex_read_reg(adapter, 0x0cd4, &magic);
		revision_id &= 0xff;
		version &= 0x7;
		magic &= 0xff;
		if (revision_id == PCIE8997_A1 &&
		    magic == CHIP_MAGIC_VALUE &&
		    version == CHIP_VER_PCIEUART)
			strcpy(adapter->fw_name, PCIEUART8997_FW_NAME_V4);
		else
			strcpy(adapter->fw_name, PCIEUSB8997_FW_NAME_V4);
		break;
	default:
		break;
	}
}