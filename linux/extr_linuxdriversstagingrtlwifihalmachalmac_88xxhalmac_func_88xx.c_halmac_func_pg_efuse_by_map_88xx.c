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
typedef  int u32 ;
struct halmac_pg_efuse_info {int dummy; } ;
struct TYPE_2__ {int eeprom_size; } ;
struct halmac_adapter {TYPE_1__ hw_config_info; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_efuse_read_cfg { ____Placeholder_halmac_efuse_read_cfg } halmac_efuse_read_cfg ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HALMAC_RET_MALLOC_FAIL ; 
 int HALMAC_RET_SUCCESS ; 
 int halmac_check_efuse_enough_88xx (struct halmac_adapter*,struct halmac_pg_efuse_info*,int /*<<< orphan*/ *) ; 
 int halmac_program_efuse_88xx (struct halmac_adapter*,struct halmac_pg_efuse_info*,int /*<<< orphan*/ *) ; 
 int halmac_update_eeprom_mask_88xx (struct halmac_adapter*,struct halmac_pg_efuse_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

enum halmac_ret_status
halmac_func_pg_efuse_by_map_88xx(struct halmac_adapter *halmac_adapter,
				 struct halmac_pg_efuse_info *pg_efuse_info,
				 enum halmac_efuse_read_cfg cfg)
{
	u8 *eeprom_mask_updated = NULL;
	u32 eeprom_mask_size = halmac_adapter->hw_config_info.eeprom_size >> 4;
	enum halmac_ret_status status = HALMAC_RET_SUCCESS;

	eeprom_mask_updated = kzalloc(eeprom_mask_size, GFP_KERNEL);
	if (!eeprom_mask_updated)
		return HALMAC_RET_MALLOC_FAIL;

	status = halmac_update_eeprom_mask_88xx(halmac_adapter, pg_efuse_info,
						eeprom_mask_updated);

	if (status != HALMAC_RET_SUCCESS) {
		pr_err("[ERR]halmac_update_eeprom_mask_88xx error = %x\n",
		       status);
		kfree(eeprom_mask_updated);
		return status;
	}

	status = halmac_check_efuse_enough_88xx(halmac_adapter, pg_efuse_info,
						eeprom_mask_updated);

	if (status != HALMAC_RET_SUCCESS) {
		pr_err("[ERR]halmac_check_efuse_enough_88xx error = %x\n",
		       status);
		kfree(eeprom_mask_updated);
		return status;
	}

	status = halmac_program_efuse_88xx(halmac_adapter, pg_efuse_info,
					   eeprom_mask_updated);

	if (status != HALMAC_RET_SUCCESS) {
		pr_err("[ERR]halmac_program_efuse_88xx error = %x\n", status);
		kfree(eeprom_mask_updated);
		return status;
	}

	kfree(eeprom_mask_updated);

	return HALMAC_RET_SUCCESS;
}