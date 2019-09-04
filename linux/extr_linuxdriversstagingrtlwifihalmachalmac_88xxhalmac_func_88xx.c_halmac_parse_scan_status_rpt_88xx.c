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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int process_status; } ;
struct TYPE_4__ {TYPE_1__ scan_state_set; } ;
struct halmac_adapter {TYPE_2__ halmac_state; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_h2c_return_code { ____Placeholder_halmac_h2c_return_code } halmac_h2c_return_code ;
typedef  enum halmac_cmd_process_status { ____Placeholder_halmac_cmd_process_status } halmac_cmd_process_status ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DMESG ; 
 int HALMAC_CMD_PROCESS_DONE ; 
 int HALMAC_CMD_PROCESS_ERROR ; 
 int /*<<< orphan*/  HALMAC_FEATURE_CHANNEL_SWITCH ; 
 int HALMAC_H2C_RETURN_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_MSG_H2C ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  PLATFORM_EVENT_INDICATION (void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SCAN_STATUS_RPT_GET_H2C_RETURN_CODE (scalar_t__*) ; 

__attribute__((used)) static enum halmac_ret_status
halmac_parse_scan_status_rpt_88xx(struct halmac_adapter *halmac_adapter,
				  u8 *c2h_buf, u32 c2h_size)
{
	u8 h2c_return_code;
	void *driver_adapter = halmac_adapter->driver_adapter;
	enum halmac_cmd_process_status process_status;

	h2c_return_code = (u8)SCAN_STATUS_RPT_GET_H2C_RETURN_CODE(c2h_buf);
	process_status = (enum halmac_h2c_return_code)h2c_return_code ==
					 HALMAC_H2C_RETURN_SUCCESS ?
				 HALMAC_CMD_PROCESS_DONE :
				 HALMAC_CMD_PROCESS_ERROR;

	PLATFORM_EVENT_INDICATION(driver_adapter, HALMAC_FEATURE_CHANNEL_SWITCH,
				  process_status, NULL, 0);

	halmac_adapter->halmac_state.scan_state_set.process_status =
		process_status;

	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_H2C, DBG_DMESG,
			"[TRACE]scan status : %X\n", process_status);

	return HALMAC_RET_SUCCESS;
}