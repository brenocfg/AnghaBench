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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct halmac_pg_efuse_info {int efuse_map_size; int* efuse_map; } ;
struct halmac_adapter {int efuse_end; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int HALMAC_RET_SUCCESS ; 
 int halmac_func_write_efuse_88xx (struct halmac_adapter*,int,int) ; 

__attribute__((used)) static enum halmac_ret_status
halmac_program_efuse_88xx(struct halmac_adapter *halmac_adapter,
			  struct halmac_pg_efuse_info *pg_efuse_info,
			  u8 *eeprom_mask_updated)
{
	u8 pre_word_enb, word_enb;
	u8 pg_efuse_header, pg_efuse_header2;
	u8 pg_block;
	u16 i, j;
	u32 efuse_end;
	u32 tmp_eeprom_offset;
	enum halmac_ret_status status = HALMAC_RET_SUCCESS;

	efuse_end = halmac_adapter->efuse_end;

	for (i = 0; i < pg_efuse_info->efuse_map_size; i = i + 8) {
		tmp_eeprom_offset = i;

		if (((tmp_eeprom_offset >> 3) & 1) > 0) {
			pre_word_enb =
				(*(eeprom_mask_updated + (i >> 4)) & 0x0F);
			word_enb = pre_word_enb ^ 0x0F;
		} else {
			pre_word_enb = (*(eeprom_mask_updated + (i >> 4)) >> 4);
			word_enb = pre_word_enb ^ 0x0F;
		}

		pg_block = (u8)(tmp_eeprom_offset >> 3);

		if (pre_word_enb <= 0)
			continue;

		if (tmp_eeprom_offset > 0x7f) {
			pg_efuse_header =
				(((pg_block & 0x07) << 5) & 0xE0) | 0x0F;
			pg_efuse_header2 =
				(u8)(((pg_block & 0x78) << 1) + word_enb);
		} else {
			pg_efuse_header = (u8)((pg_block << 4) + word_enb);
		}

		if (tmp_eeprom_offset > 0x7f) {
			halmac_func_write_efuse_88xx(halmac_adapter, efuse_end,
						     pg_efuse_header);
			status = halmac_func_write_efuse_88xx(halmac_adapter,
							      efuse_end + 1,
							      pg_efuse_header2);
			efuse_end = efuse_end + 2;
			for (j = 0; j < 4; j++) {
				if (((pre_word_enb >> j) & 0x1) > 0) {
					halmac_func_write_efuse_88xx(
						halmac_adapter, efuse_end,
						*(pg_efuse_info->efuse_map +
						  tmp_eeprom_offset +
						  (j << 1)));
					status = halmac_func_write_efuse_88xx(
						halmac_adapter, efuse_end + 1,
						*(pg_efuse_info->efuse_map +
						  tmp_eeprom_offset + (j << 1) +
						  1));
					efuse_end = efuse_end + 2;
				}
			}
		} else {
			status = halmac_func_write_efuse_88xx(
				halmac_adapter, efuse_end, pg_efuse_header);
			efuse_end = efuse_end + 1;
			for (j = 0; j < 4; j++) {
				if (((pre_word_enb >> j) & 0x1) > 0) {
					halmac_func_write_efuse_88xx(
						halmac_adapter, efuse_end,
						*(pg_efuse_info->efuse_map +
						  tmp_eeprom_offset +
						  (j << 1)));
					status = halmac_func_write_efuse_88xx(
						halmac_adapter, efuse_end + 1,
						*(pg_efuse_info->efuse_map +
						  tmp_eeprom_offset + (j << 1) +
						  1));
					efuse_end = efuse_end + 2;
				}
			}
		}
	}

	return status;
}