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
typedef  int u32 ;
struct TYPE_2__ {int eeprom_size; scalar_t__ efuse_size; } ;
struct halmac_adapter {int efuse_end; TYPE_1__ hw_config_info; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HALMAC_PROTECTED_EFUSE_SIZE_88XX ; 
 int HALMAC_RET_EFUSE_NOT_ENOUGH ; 
 int HALMAC_RET_MALLOC_FAIL ; 
 int HALMAC_RET_SUCCESS ; 
 int halmac_func_write_efuse_88xx (struct halmac_adapter*,int,scalar_t__) ; 
 int halmac_read_logical_efuse_map_88xx (struct halmac_adapter*,scalar_t__*) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

enum halmac_ret_status
halmac_func_write_logical_efuse_88xx(struct halmac_adapter *halmac_adapter,
				     u32 offset, u8 value)
{
	u8 pg_efuse_byte1, pg_efuse_byte2;
	u8 pg_block, pg_block_index;
	u8 pg_efuse_header, pg_efuse_header2;
	u8 *eeprom_map = NULL;
	u32 eeprom_size = halmac_adapter->hw_config_info.eeprom_size;
	u32 efuse_end, pg_efuse_num;
	void *driver_adapter = NULL;
	enum halmac_ret_status status = HALMAC_RET_SUCCESS;

	driver_adapter = halmac_adapter->driver_adapter;

	eeprom_map = kzalloc(eeprom_size, GFP_KERNEL);
	if (!eeprom_map)
		return HALMAC_RET_MALLOC_FAIL;
	memset(eeprom_map, 0xFF, eeprom_size);

	status = halmac_read_logical_efuse_map_88xx(halmac_adapter, eeprom_map);
	if (status != HALMAC_RET_SUCCESS) {
		pr_err("[ERR]halmac_read_logical_efuse_map_88xx error = %x\n",
		       status);
		kfree(eeprom_map);
		return status;
	}

	if (*(eeprom_map + offset) != value) {
		efuse_end = halmac_adapter->efuse_end;
		pg_block = (u8)(offset >> 3);
		pg_block_index = (u8)((offset & (8 - 1)) >> 1);

		if (offset > 0x7f) {
			pg_efuse_header =
				(((pg_block & 0x07) << 5) & 0xE0) | 0x0F;
			pg_efuse_header2 =
				(u8)(((pg_block & 0x78) << 1) +
				     ((0x1 << pg_block_index) ^ 0x0F));
		} else {
			pg_efuse_header =
				(u8)((pg_block << 4) +
				     ((0x01 << pg_block_index) ^ 0x0F));
		}

		if ((offset & 1) == 0) {
			pg_efuse_byte1 = value;
			pg_efuse_byte2 = *(eeprom_map + offset + 1);
		} else {
			pg_efuse_byte1 = *(eeprom_map + offset - 1);
			pg_efuse_byte2 = value;
		}

		if (offset > 0x7f) {
			pg_efuse_num = 4;
			if (halmac_adapter->hw_config_info.efuse_size <=
			    (pg_efuse_num + HALMAC_PROTECTED_EFUSE_SIZE_88XX +
			     halmac_adapter->efuse_end)) {
				kfree(eeprom_map);
				return HALMAC_RET_EFUSE_NOT_ENOUGH;
			}
			halmac_func_write_efuse_88xx(halmac_adapter, efuse_end,
						     pg_efuse_header);
			halmac_func_write_efuse_88xx(halmac_adapter,
						     efuse_end + 1,
						     pg_efuse_header2);
			halmac_func_write_efuse_88xx(
				halmac_adapter, efuse_end + 2, pg_efuse_byte1);
			status = halmac_func_write_efuse_88xx(
				halmac_adapter, efuse_end + 3, pg_efuse_byte2);
		} else {
			pg_efuse_num = 3;
			if (halmac_adapter->hw_config_info.efuse_size <=
			    (pg_efuse_num + HALMAC_PROTECTED_EFUSE_SIZE_88XX +
			     halmac_adapter->efuse_end)) {
				kfree(eeprom_map);
				return HALMAC_RET_EFUSE_NOT_ENOUGH;
			}
			halmac_func_write_efuse_88xx(halmac_adapter, efuse_end,
						     pg_efuse_header);
			halmac_func_write_efuse_88xx(
				halmac_adapter, efuse_end + 1, pg_efuse_byte1);
			status = halmac_func_write_efuse_88xx(
				halmac_adapter, efuse_end + 2, pg_efuse_byte2);
		}

		if (status != HALMAC_RET_SUCCESS) {
			pr_err("[ERR]halmac_write_logical_efuse error = %x\n",
			       status);
			kfree(eeprom_map);
			return status;
		}
	}

	kfree(eeprom_map);

	return HALMAC_RET_SUCCESS;
}