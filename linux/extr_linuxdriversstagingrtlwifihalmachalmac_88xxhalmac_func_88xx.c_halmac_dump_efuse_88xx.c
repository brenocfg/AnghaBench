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
typedef  scalar_t__ u32 ;
struct halmac_api {int dummy; } ;
struct TYPE_3__ {int process_status; } ;
struct TYPE_4__ {scalar_t__ dlfw_state; TYPE_1__ efuse_state_set; } ;
struct halmac_adapter {TYPE_2__ halmac_state; void* driver_adapter; scalar_t__ halmac_api; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_efuse_read_cfg { ____Placeholder_halmac_efuse_read_cfg } halmac_efuse_read_cfg ;
typedef  enum halmac_cmd_process_status { ____Placeholder_halmac_cmd_process_status } halmac_cmd_process_status ;

/* Variables and functions */
 int HALMAC_CMD_PROCESS_SENDING ; 
 scalar_t__ HALMAC_DLFW_NONE ; 
 int /*<<< orphan*/  HALMAC_EFUSE_CMD_CONSTRUCT_H2C_SENT ; 
 int HALMAC_EFUSE_R_AUTO ; 
 int HALMAC_EFUSE_R_FW ; 
 scalar_t__ HALMAC_REG_READ_32 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int HALMAC_RET_ERROR_STATE ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  REG_H2C_PKT_READADDR ; 
 int halmac_dump_efuse_drv_88xx (struct halmac_adapter*) ; 
 int halmac_dump_efuse_fw_88xx (struct halmac_adapter*) ; 
 scalar_t__ halmac_transition_efuse_state_88xx (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

enum halmac_ret_status
halmac_dump_efuse_88xx(struct halmac_adapter *halmac_adapter,
		       enum halmac_efuse_read_cfg cfg)
{
	u32 chk_h2c_init;
	void *driver_adapter = NULL;
	struct halmac_api *halmac_api =
		(struct halmac_api *)halmac_adapter->halmac_api;
	enum halmac_ret_status status = HALMAC_RET_SUCCESS;
	enum halmac_cmd_process_status *process_status =
		&halmac_adapter->halmac_state.efuse_state_set.process_status;

	driver_adapter = halmac_adapter->driver_adapter;

	*process_status = HALMAC_CMD_PROCESS_SENDING;

	if (halmac_transition_efuse_state_88xx(
		    halmac_adapter, HALMAC_EFUSE_CMD_CONSTRUCT_H2C_SENT) !=
	    HALMAC_RET_SUCCESS)
		return HALMAC_RET_ERROR_STATE;

	if (cfg == HALMAC_EFUSE_R_AUTO) {
		chk_h2c_init = HALMAC_REG_READ_32(halmac_adapter,
						  REG_H2C_PKT_READADDR);
		if (halmac_adapter->halmac_state.dlfw_state ==
			    HALMAC_DLFW_NONE ||
		    chk_h2c_init == 0)
			status = halmac_dump_efuse_drv_88xx(halmac_adapter);
		else
			status = halmac_dump_efuse_fw_88xx(halmac_adapter);
	} else if (cfg == HALMAC_EFUSE_R_FW) {
		status = halmac_dump_efuse_fw_88xx(halmac_adapter);
	} else {
		status = halmac_dump_efuse_drv_88xx(halmac_adapter);
	}

	if (status != HALMAC_RET_SUCCESS) {
		pr_err("halmac_read_efuse error = %x\n", status);
		return status;
	}

	return status;
}