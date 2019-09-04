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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int eeprom_size; int efuse_size; } ;
struct halmac_adapter {int efuse_end; TYPE_1__ hw_config_info; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int HALMAC_PROTECTED_EFUSE_SIZE_88XX ; 
 int HALMAC_RET_EEPROM_PARSING_FAIL ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 

enum halmac_ret_status
halmac_eeprom_parser_88xx(struct halmac_adapter *halmac_adapter,
			  u8 *physical_efuse_map, u8 *logical_efuse_map)
{
	u8 j;
	u8 value8;
	u8 block_index;
	u8 valid_word_enable, word_enable;
	u8 efuse_read_header, efuse_read_header2 = 0;
	u32 eeprom_index;
	u32 efuse_index = 0;
	u32 eeprom_size = halmac_adapter->hw_config_info.eeprom_size;
	void *driver_adapter = NULL;

	driver_adapter = halmac_adapter->driver_adapter;

	memset(logical_efuse_map, 0xFF, eeprom_size);

	do {
		value8 = *(physical_efuse_map + efuse_index);
		efuse_read_header = value8;

		if ((efuse_read_header & 0x1f) == 0x0f) {
			efuse_index++;
			value8 = *(physical_efuse_map + efuse_index);
			efuse_read_header2 = value8;
			block_index = ((efuse_read_header2 & 0xF0) >> 1) |
				      ((efuse_read_header >> 5) & 0x07);
			word_enable = efuse_read_header2 & 0x0F;
		} else {
			block_index = (efuse_read_header & 0xF0) >> 4;
			word_enable = efuse_read_header & 0x0F;
		}

		if (efuse_read_header == 0xff)
			break;

		efuse_index++;

		if (efuse_index >= halmac_adapter->hw_config_info.efuse_size -
					   HALMAC_PROTECTED_EFUSE_SIZE_88XX - 1)
			return HALMAC_RET_EEPROM_PARSING_FAIL;

		for (j = 0; j < 4; j++) {
			valid_word_enable =
				(u8)((~(word_enable >> j)) & BIT(0));
			if (valid_word_enable != 1)
				continue;

			eeprom_index = (block_index << 3) + (j << 1);

			if ((eeprom_index + 1) > eeprom_size) {
				pr_err("Error: EEPROM addr exceeds eeprom_size:0x%X, at eFuse 0x%X\n",
				       eeprom_size, efuse_index - 1);
				if ((efuse_read_header & 0x1f) == 0x0f)
					pr_err("Error: EEPROM header: 0x%X, 0x%X,\n",
					       efuse_read_header,
					       efuse_read_header2);
				else
					pr_err("Error: EEPROM header: 0x%X,\n",
					       efuse_read_header);

				return HALMAC_RET_EEPROM_PARSING_FAIL;
			}

			value8 = *(physical_efuse_map + efuse_index);
			*(logical_efuse_map + eeprom_index) = value8;

			eeprom_index++;
			efuse_index++;

			if (efuse_index >
			    halmac_adapter->hw_config_info.efuse_size -
				    HALMAC_PROTECTED_EFUSE_SIZE_88XX - 1)
				return HALMAC_RET_EEPROM_PARSING_FAIL;

			value8 = *(physical_efuse_map + efuse_index);
			*(logical_efuse_map + eeprom_index) = value8;

			efuse_index++;

			if (efuse_index >
			    halmac_adapter->hw_config_info.efuse_size -
				    HALMAC_PROTECTED_EFUSE_SIZE_88XX)
				return HALMAC_RET_EEPROM_PARSING_FAIL;
		}
	} while (1);

	halmac_adapter->efuse_end = efuse_index;

	return HALMAC_RET_SUCCESS;
}