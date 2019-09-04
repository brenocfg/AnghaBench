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
typedef  int u16 ;
struct halmac_pg_efuse_info {int efuse_mask_size; int efuse_map_size; scalar_t__* efuse_mask; scalar_t__* efuse_map; } ;
struct TYPE_2__ {int eeprom_size; } ;
struct halmac_adapter {void* driver_adapter; TYPE_1__ hw_config_info; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HALMAC_RET_MALLOC_FAIL ; 
 int HALMAC_RET_SUCCESS ; 
 int halmac_read_logical_efuse_map_88xx (struct halmac_adapter*,scalar_t__*) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 

__attribute__((used)) static enum halmac_ret_status
halmac_update_eeprom_mask_88xx(struct halmac_adapter *halmac_adapter,
			       struct halmac_pg_efuse_info *pg_efuse_info,
			       u8 *eeprom_mask_updated)
{
	u8 *eeprom_map = NULL;
	u32 eeprom_size = halmac_adapter->hw_config_info.eeprom_size;
	u8 *eeprom_map_pg, *eeprom_mask;
	u16 i, j;
	u16 map_byte_offset, mask_byte_offset;
	enum halmac_ret_status status = HALMAC_RET_SUCCESS;

	void *driver_adapter = NULL;

	driver_adapter = halmac_adapter->driver_adapter;

	eeprom_map = kzalloc(eeprom_size, GFP_KERNEL);
	if (!eeprom_map)
		return HALMAC_RET_MALLOC_FAIL;

	memset(eeprom_map, 0xFF, eeprom_size);
	memset(eeprom_mask_updated, 0x00, pg_efuse_info->efuse_mask_size);

	status = halmac_read_logical_efuse_map_88xx(halmac_adapter, eeprom_map);

	if (status != HALMAC_RET_SUCCESS) {
		kfree(eeprom_map);
		return status;
	}

	eeprom_map_pg = pg_efuse_info->efuse_map;
	eeprom_mask = pg_efuse_info->efuse_mask;

	for (i = 0; i < pg_efuse_info->efuse_mask_size; i++)
		*(eeprom_mask_updated + i) = *(eeprom_mask + i);

	for (i = 0; i < pg_efuse_info->efuse_map_size; i = i + 16) {
		for (j = 0; j < 16; j = j + 2) {
			map_byte_offset = i + j;
			mask_byte_offset = i >> 4;
			if (*(eeprom_map_pg + map_byte_offset) ==
			    *(eeprom_map + map_byte_offset)) {
				if (*(eeprom_map_pg + map_byte_offset + 1) ==
				    *(eeprom_map + map_byte_offset + 1)) {
					switch (j) {
					case 0:
						*(eeprom_mask_updated +
						  mask_byte_offset) =
							*(eeprom_mask_updated +
							  mask_byte_offset) &
							(BIT(4) ^ 0xFF);
						break;
					case 2:
						*(eeprom_mask_updated +
						  mask_byte_offset) =
							*(eeprom_mask_updated +
							  mask_byte_offset) &
							(BIT(5) ^ 0xFF);
						break;
					case 4:
						*(eeprom_mask_updated +
						  mask_byte_offset) =
							*(eeprom_mask_updated +
							  mask_byte_offset) &
							(BIT(6) ^ 0xFF);
						break;
					case 6:
						*(eeprom_mask_updated +
						  mask_byte_offset) =
							*(eeprom_mask_updated +
							  mask_byte_offset) &
							(BIT(7) ^ 0xFF);
						break;
					case 8:
						*(eeprom_mask_updated +
						  mask_byte_offset) =
							*(eeprom_mask_updated +
							  mask_byte_offset) &
							(BIT(0) ^ 0xFF);
						break;
					case 10:
						*(eeprom_mask_updated +
						  mask_byte_offset) =
							*(eeprom_mask_updated +
							  mask_byte_offset) &
							(BIT(1) ^ 0xFF);
						break;
					case 12:
						*(eeprom_mask_updated +
						  mask_byte_offset) =
							*(eeprom_mask_updated +
							  mask_byte_offset) &
							(BIT(2) ^ 0xFF);
						break;
					case 14:
						*(eeprom_mask_updated +
						  mask_byte_offset) =
							*(eeprom_mask_updated +
							  mask_byte_offset) &
							(BIT(3) ^ 0xFF);
						break;
					default:
						break;
					}
				}
			}
		}
	}

	kfree(eeprom_map);

	return status;
}