#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_8__ {int physical_efuse_map; int logical_efuse_map; } ;
struct TYPE_6__ {scalar_t__ seq_num; int process_status; scalar_t__ fw_return_code; } ;
struct TYPE_7__ {TYPE_2__ efuse_state_set; } ;
struct TYPE_5__ {int eeprom_size; int efuse_size; } ;
struct halmac_adapter {scalar_t__ efuse_segment_size; scalar_t__* hal_efuse_map; int hal_efuse_map_valid; TYPE_4__ event_trigger; TYPE_3__ halmac_state; TYPE_1__ hw_config_info; int /*<<< orphan*/  efuse_lock; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_h2c_return_code { ____Placeholder_halmac_h2c_return_code } halmac_h2c_return_code ;
typedef  enum halmac_cmd_process_status { ____Placeholder_halmac_cmd_process_status } halmac_cmd_process_status ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  EFUSE_DATA_GET_END_SEGMENT (scalar_t__*) ; 
 scalar_t__ EFUSE_DATA_GET_H2C_SEQ (scalar_t__*) ; 
 scalar_t__ EFUSE_DATA_GET_SEGMENT_ID (scalar_t__*) ; 
 scalar_t__ EFUSE_DATA_GET_SEGMENT_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HALMAC_C2H_DATA_OFFSET_88XX ; 
 int HALMAC_CMD_PROCESS_DONE ; 
 int HALMAC_CMD_PROCESS_ERROR ; 
 int HALMAC_CMD_PROCESS_SENDING ; 
 int /*<<< orphan*/  HALMAC_FEATURE_DUMP_LOGICAL_EFUSE ; 
 int /*<<< orphan*/  HALMAC_FEATURE_DUMP_PHYSICAL_EFUSE ; 
 int HALMAC_H2C_RETURN_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_MSG_H2C ; 
 int HALMAC_RET_EEPROM_PARSING_FAIL ; 
 int HALMAC_RET_MALLOC_FAIL ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PLATFORM_EVENT_INDICATION (void*,int /*<<< orphan*/ ,int,scalar_t__*,int) ; 
 int halmac_eeprom_parser_88xx (struct halmac_adapter*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum halmac_ret_status
halmac_parse_efuse_data_88xx(struct halmac_adapter *halmac_adapter, u8 *c2h_buf,
			     u32 c2h_size)
{
	u8 segment_id = 0, segment_size = 0, h2c_seq = 0;
	u8 *eeprom_map = NULL;
	u32 eeprom_size = halmac_adapter->hw_config_info.eeprom_size;
	u8 h2c_return_code = 0;
	void *driver_adapter = halmac_adapter->driver_adapter;
	enum halmac_cmd_process_status process_status;

	h2c_seq = (u8)EFUSE_DATA_GET_H2C_SEQ(c2h_buf);
	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_H2C, DBG_DMESG,
			"[TRACE]Seq num : h2c -> %d c2h -> %d\n",
			halmac_adapter->halmac_state.efuse_state_set.seq_num,
			h2c_seq);
	if (h2c_seq != halmac_adapter->halmac_state.efuse_state_set.seq_num) {
		pr_err("[ERR]Seq num mismatch : h2c -> %d c2h -> %d\n",
		       halmac_adapter->halmac_state.efuse_state_set.seq_num,
		       h2c_seq);
		return HALMAC_RET_SUCCESS;
	}

	if (halmac_adapter->halmac_state.efuse_state_set.process_status !=
	    HALMAC_CMD_PROCESS_SENDING) {
		pr_err("[ERR]Not in HALMAC_CMD_PROCESS_SENDING\n");
		return HALMAC_RET_SUCCESS;
	}

	segment_id = (u8)EFUSE_DATA_GET_SEGMENT_ID(c2h_buf);
	segment_size = (u8)EFUSE_DATA_GET_SEGMENT_SIZE(c2h_buf);
	if (segment_id == 0)
		halmac_adapter->efuse_segment_size = segment_size;

	eeprom_map = kzalloc(eeprom_size, GFP_KERNEL);
	if (!eeprom_map)
		return HALMAC_RET_MALLOC_FAIL;
	memset(eeprom_map, 0xFF, eeprom_size);

	spin_lock(&halmac_adapter->efuse_lock);
	memcpy(halmac_adapter->hal_efuse_map +
		       segment_id * halmac_adapter->efuse_segment_size,
	       c2h_buf + HALMAC_C2H_DATA_OFFSET_88XX, segment_size);
	spin_unlock(&halmac_adapter->efuse_lock);

	if (!EFUSE_DATA_GET_END_SEGMENT(c2h_buf)) {
		kfree(eeprom_map);
		return HALMAC_RET_SUCCESS;
	}

	h2c_return_code =
		halmac_adapter->halmac_state.efuse_state_set.fw_return_code;

	if ((enum halmac_h2c_return_code)h2c_return_code ==
	    HALMAC_H2C_RETURN_SUCCESS) {
		process_status = HALMAC_CMD_PROCESS_DONE;
		halmac_adapter->halmac_state.efuse_state_set.process_status =
			process_status;

		spin_lock(&halmac_adapter->efuse_lock);
		halmac_adapter->hal_efuse_map_valid = true;
		spin_unlock(&halmac_adapter->efuse_lock);

		if (halmac_adapter->event_trigger.physical_efuse_map == 1) {
			PLATFORM_EVENT_INDICATION(
				driver_adapter,
				HALMAC_FEATURE_DUMP_PHYSICAL_EFUSE,
				process_status, halmac_adapter->hal_efuse_map,
				halmac_adapter->hw_config_info.efuse_size);
			halmac_adapter->event_trigger.physical_efuse_map = 0;
		}

		if (halmac_adapter->event_trigger.logical_efuse_map == 1) {
			if (halmac_eeprom_parser_88xx(
				    halmac_adapter,
				    halmac_adapter->hal_efuse_map,
				    eeprom_map) != HALMAC_RET_SUCCESS) {
				kfree(eeprom_map);
				return HALMAC_RET_EEPROM_PARSING_FAIL;
			}
			PLATFORM_EVENT_INDICATION(
				driver_adapter,
				HALMAC_FEATURE_DUMP_LOGICAL_EFUSE,
				process_status, eeprom_map, eeprom_size);
			halmac_adapter->event_trigger.logical_efuse_map = 0;
		}
	} else {
		process_status = HALMAC_CMD_PROCESS_ERROR;
		halmac_adapter->halmac_state.efuse_state_set.process_status =
			process_status;

		if (halmac_adapter->event_trigger.physical_efuse_map == 1) {
			PLATFORM_EVENT_INDICATION(
				driver_adapter,
				HALMAC_FEATURE_DUMP_PHYSICAL_EFUSE,
				process_status,
				&halmac_adapter->halmac_state.efuse_state_set
					 .fw_return_code,
				1);
			halmac_adapter->event_trigger.physical_efuse_map = 0;
		}

		if (halmac_adapter->event_trigger.logical_efuse_map == 1) {
			if (halmac_eeprom_parser_88xx(
				    halmac_adapter,
				    halmac_adapter->hal_efuse_map,
				    eeprom_map) != HALMAC_RET_SUCCESS) {
				kfree(eeprom_map);
				return HALMAC_RET_EEPROM_PARSING_FAIL;
			}
			PLATFORM_EVENT_INDICATION(
				driver_adapter,
				HALMAC_FEATURE_DUMP_LOGICAL_EFUSE,
				process_status,
				&halmac_adapter->halmac_state.efuse_state_set
					 .fw_return_code,
				1);
			halmac_adapter->event_trigger.logical_efuse_map = 0;
		}
	}

	kfree(eeprom_map);

	return HALMAC_RET_SUCCESS;
}