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
typedef  scalar_t__ u32 ;
struct halmac_efuse_state_set {int process_status; } ;
struct TYPE_3__ {scalar_t__ efuse_size; } ;
struct TYPE_4__ {struct halmac_efuse_state_set efuse_state_set; } ;
struct halmac_adapter {int /*<<< orphan*/  hal_efuse_map; TYPE_1__ hw_config_info; void* driver_adapter; TYPE_2__ halmac_state; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_cmd_process_status { ____Placeholder_halmac_cmd_process_status } halmac_cmd_process_status ;

/* Variables and functions */
 int HALMAC_CMD_PROCESS_DONE ; 
 int HALMAC_RET_BUFFER_TOO_SMALL ; 
 int HALMAC_RET_NULL_POINTER ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

enum halmac_ret_status halmac_query_dump_physical_efuse_status_88xx(
	struct halmac_adapter *halmac_adapter,
	enum halmac_cmd_process_status *process_status, u8 *data, u32 *size)
{
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
		if (*size < halmac_adapter->hw_config_info.efuse_size) {
			*size = halmac_adapter->hw_config_info.efuse_size;
			return HALMAC_RET_BUFFER_TOO_SMALL;
		}

		*size = halmac_adapter->hw_config_info.efuse_size;
		memcpy(data, halmac_adapter->hal_efuse_map, *size);
	}

	return HALMAC_RET_SUCCESS;
}