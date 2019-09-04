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
typedef  int /*<<< orphan*/  u32 ;
struct halmac_efuse_state_set {int process_status; } ;
struct TYPE_4__ {struct halmac_efuse_state_set efuse_state_set; } ;
struct TYPE_3__ {int /*<<< orphan*/  eeprom_size; } ;
struct halmac_adapter {int /*<<< orphan*/  hal_efuse_map; void* driver_adapter; TYPE_2__ halmac_state; TYPE_1__ hw_config_info; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_cmd_process_status { ____Placeholder_halmac_cmd_process_status } halmac_cmd_process_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HALMAC_CMD_PROCESS_DONE ; 
 int HALMAC_RET_BUFFER_TOO_SMALL ; 
 int HALMAC_RET_EEPROM_PARSING_FAIL ; 
 int HALMAC_RET_MALLOC_FAIL ; 
 int HALMAC_RET_NULL_POINTER ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 scalar_t__ halmac_eeprom_parser_88xx (struct halmac_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

enum halmac_ret_status halmac_query_dump_logical_efuse_status_88xx(
	struct halmac_adapter *halmac_adapter,
	enum halmac_cmd_process_status *process_status, u8 *data, u32 *size)
{
	u8 *eeprom_map = NULL;
	u32 eeprom_size = halmac_adapter->hw_config_info.eeprom_size;
	void *driver_adapter = NULL;
	struct halmac_efuse_state_set *efuse_state_set =
		&halmac_adapter->halmac_state.efuse_state_set;

	driver_adapter = halmac_adapter->driver_adapter;

	*process_status = efuse_state_set->process_status;

	if (!data)
		return HALMAC_RET_NULL_POINTER;

	if (!size)
		return HALMAC_RET_NULL_POINTER;

	if (*process_status == HALMAC_CMD_PROCESS_DONE) {
		if (*size < eeprom_size) {
			*size = eeprom_size;
			return HALMAC_RET_BUFFER_TOO_SMALL;
		}

		*size = eeprom_size;

		eeprom_map = kzalloc(eeprom_size, GFP_KERNEL);
		if (!eeprom_map)
			return HALMAC_RET_MALLOC_FAIL;
		memset(eeprom_map, 0xFF, eeprom_size);

		if (halmac_eeprom_parser_88xx(
			    halmac_adapter, halmac_adapter->hal_efuse_map,
			    eeprom_map) != HALMAC_RET_SUCCESS) {
			kfree(eeprom_map);
			return HALMAC_RET_EEPROM_PARSING_FAIL;
		}

		memcpy(data, eeprom_map, *size);

		kfree(eeprom_map);
	}

	return HALMAC_RET_SUCCESS;
}