#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ seq_num; scalar_t__ process_status; scalar_t__ fw_return_code; } ;
struct TYPE_6__ {TYPE_2__ cfg_para_state_set; } ;
struct TYPE_4__ {scalar_t__ offset_accumulation; scalar_t__ value_accumulation; } ;
struct halmac_adapter {TYPE_3__ halmac_state; TYPE_1__ config_para_info; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_h2c_return_code { ____Placeholder_halmac_h2c_return_code } halmac_h2c_return_code ;
typedef  enum halmac_cmd_process_status { ____Placeholder_halmac_cmd_process_status } halmac_cmd_process_status ;

/* Variables and functions */
 scalar_t__ CFG_PARAMETER_ACK_GET_OFFSET_ACCUMULATION (scalar_t__*) ; 
 scalar_t__ CFG_PARAMETER_ACK_GET_VALUE_ACCUMULATION (scalar_t__*) ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 scalar_t__ H2C_ACK_HDR_GET_H2C_RETURN_CODE (scalar_t__*) ; 
 scalar_t__ H2C_ACK_HDR_GET_H2C_SEQ (scalar_t__*) ; 
 int HALMAC_CMD_PROCESS_DONE ; 
 int HALMAC_CMD_PROCESS_ERROR ; 
 scalar_t__ HALMAC_CMD_PROCESS_SENDING ; 
 int HALMAC_CMD_PROCESS_UNDEFINE ; 
 int /*<<< orphan*/  HALMAC_FEATURE_CFG_PARA ; 
 int HALMAC_H2C_RETURN_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_MSG_H2C ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PLATFORM_EVENT_INDICATION (void*,int /*<<< orphan*/ ,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static enum halmac_ret_status
halmac_parse_h2c_ack_cfg_para_88xx(struct halmac_adapter *halmac_adapter,
				   u8 *c2h_buf, u32 c2h_size)
{
	u8 h2c_seq = 0;
	u8 h2c_return_code;
	u32 offset_accu = 0, value_accu = 0;
	void *driver_adapter = halmac_adapter->driver_adapter;
	enum halmac_cmd_process_status process_status =
		HALMAC_CMD_PROCESS_UNDEFINE;

	h2c_seq = (u8)H2C_ACK_HDR_GET_H2C_SEQ(c2h_buf);
	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_H2C, DBG_DMESG,
			"Seq num : h2c -> %d c2h -> %d\n",
			halmac_adapter->halmac_state.cfg_para_state_set.seq_num,
			h2c_seq);
	if (h2c_seq !=
	    halmac_adapter->halmac_state.cfg_para_state_set.seq_num) {
		pr_err("Seq num mismatch : h2c -> %d c2h -> %d\n",
		       halmac_adapter->halmac_state.cfg_para_state_set.seq_num,
		       h2c_seq);
		return HALMAC_RET_SUCCESS;
	}

	if (halmac_adapter->halmac_state.cfg_para_state_set.process_status !=
	    HALMAC_CMD_PROCESS_SENDING) {
		pr_err("Not in HALMAC_CMD_PROCESS_SENDING\n");
		return HALMAC_RET_SUCCESS;
	}

	h2c_return_code = (u8)H2C_ACK_HDR_GET_H2C_RETURN_CODE(c2h_buf);
	halmac_adapter->halmac_state.cfg_para_state_set.fw_return_code =
		h2c_return_code;
	offset_accu = CFG_PARAMETER_ACK_GET_OFFSET_ACCUMULATION(c2h_buf);
	value_accu = CFG_PARAMETER_ACK_GET_VALUE_ACCUMULATION(c2h_buf);

	if ((offset_accu !=
	     halmac_adapter->config_para_info.offset_accumulation) ||
	    (value_accu !=
	     halmac_adapter->config_para_info.value_accumulation)) {
		pr_err("[C2H]offset_accu : %x, value_accu : %x!!\n",
		       offset_accu, value_accu);
		pr_err("[Adapter]offset_accu : %x, value_accu : %x!!\n",
		       halmac_adapter->config_para_info.offset_accumulation,
		       halmac_adapter->config_para_info.value_accumulation);
		process_status = HALMAC_CMD_PROCESS_ERROR;
	}

	if ((enum halmac_h2c_return_code)h2c_return_code ==
		    HALMAC_H2C_RETURN_SUCCESS &&
	    process_status != HALMAC_CMD_PROCESS_ERROR) {
		process_status = HALMAC_CMD_PROCESS_DONE;
		halmac_adapter->halmac_state.cfg_para_state_set.process_status =
			process_status;
		PLATFORM_EVENT_INDICATION(driver_adapter,
					  HALMAC_FEATURE_CFG_PARA,
					  process_status, NULL, 0);
	} else {
		process_status = HALMAC_CMD_PROCESS_ERROR;
		halmac_adapter->halmac_state.cfg_para_state_set.process_status =
			process_status;
		PLATFORM_EVENT_INDICATION(
			driver_adapter, HALMAC_FEATURE_CFG_PARA, process_status,
			&halmac_adapter->halmac_state.cfg_para_state_set
				 .fw_return_code,
			1);
	}

	return HALMAC_RET_SUCCESS;
}