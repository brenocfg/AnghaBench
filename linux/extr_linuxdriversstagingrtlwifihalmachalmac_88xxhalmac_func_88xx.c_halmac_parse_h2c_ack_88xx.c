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
typedef  int /*<<< orphan*/  u32 ;
struct halmac_adapter {void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_h2c_return_code { ____Placeholder_halmac_h2c_return_code } halmac_h2c_return_code ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DMESG ; 
 scalar_t__ H2C_ACK_HDR_GET_H2C_CMD_ID (int*) ; 
 scalar_t__ H2C_ACK_HDR_GET_H2C_RETURN_CODE (int*) ; 
 scalar_t__ H2C_ACK_HDR_GET_H2C_SUB_CMD_ID (int*) ; 
#define  H2C_SUB_CMD_ID_CFG_PARAMETER_ACK 136 
#define  H2C_SUB_CMD_ID_CHANNEL_SWITCH_ACK 135 
#define  H2C_SUB_CMD_ID_DUMP_PHYSICAL_EFUSE_ACK 134 
#define  H2C_SUB_CMD_ID_IQK_ACK 133 
#define  H2C_SUB_CMD_ID_POWER_TRACKING_ACK 132 
#define  H2C_SUB_CMD_ID_PSD_ACK 131 
#define  H2C_SUB_CMD_ID_RUN_DATAPACK_ACK 130 
#define  H2C_SUB_CMD_ID_UPDATE_DATAPACK_ACK 129 
#define  H2C_SUB_CMD_ID_UPDATE_PACKET_ACK 128 
 int HALMAC_H2C_RETURN_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_MSG_H2C ; 
 int HALMAC_RET_C2H_NOT_HANDLED ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int halmac_parse_h2c_ack_cfg_para_88xx (struct halmac_adapter*,int*,int /*<<< orphan*/ ) ; 
 int halmac_parse_h2c_ack_channel_switch_88xx (struct halmac_adapter*,int*,int /*<<< orphan*/ ) ; 
 int halmac_parse_h2c_ack_iqk_88xx (struct halmac_adapter*,int*,int /*<<< orphan*/ ) ; 
 int halmac_parse_h2c_ack_phy_efuse_88xx (struct halmac_adapter*,int*,int /*<<< orphan*/ ) ; 
 int halmac_parse_h2c_ack_power_tracking_88xx (struct halmac_adapter*,int*,int /*<<< orphan*/ ) ; 
 int halmac_parse_h2c_ack_run_datapack_88xx (struct halmac_adapter*,int*,int /*<<< orphan*/ ) ; 
 int halmac_parse_h2c_ack_update_datapack_88xx (struct halmac_adapter*,int*,int /*<<< orphan*/ ) ; 
 int halmac_parse_h2c_ack_update_packet_88xx (struct halmac_adapter*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static enum halmac_ret_status
halmac_parse_h2c_ack_88xx(struct halmac_adapter *halmac_adapter, u8 *c2h_buf,
			  u32 c2h_size)
{
	u8 h2c_cmd_id, h2c_sub_cmd_id;
	u8 h2c_return_code;
	void *driver_adapter = halmac_adapter->driver_adapter;
	enum halmac_ret_status status = HALMAC_RET_SUCCESS;

	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_H2C, DBG_DMESG,
			"Ack for C2H!!\n");

	h2c_return_code = (u8)H2C_ACK_HDR_GET_H2C_RETURN_CODE(c2h_buf);
	if ((enum halmac_h2c_return_code)h2c_return_code !=
	    HALMAC_H2C_RETURN_SUCCESS)
		HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_H2C, DBG_DMESG,
				"C2H_PKT Status Error!! Status = %d\n",
				h2c_return_code);

	h2c_cmd_id = (u8)H2C_ACK_HDR_GET_H2C_CMD_ID(c2h_buf);

	if (h2c_cmd_id != 0xFF) {
		pr_err("original h2c ack is not handled!!\n");
		status = HALMAC_RET_C2H_NOT_HANDLED;
	} else {
		h2c_sub_cmd_id = (u8)H2C_ACK_HDR_GET_H2C_SUB_CMD_ID(c2h_buf);

		switch (h2c_sub_cmd_id) {
		case H2C_SUB_CMD_ID_DUMP_PHYSICAL_EFUSE_ACK:
			status = halmac_parse_h2c_ack_phy_efuse_88xx(
				halmac_adapter, c2h_buf, c2h_size);
			break;
		case H2C_SUB_CMD_ID_CFG_PARAMETER_ACK:
			status = halmac_parse_h2c_ack_cfg_para_88xx(
				halmac_adapter, c2h_buf, c2h_size);
			break;
		case H2C_SUB_CMD_ID_UPDATE_PACKET_ACK:
			status = halmac_parse_h2c_ack_update_packet_88xx(
				halmac_adapter, c2h_buf, c2h_size);
			break;
		case H2C_SUB_CMD_ID_UPDATE_DATAPACK_ACK:
			status = halmac_parse_h2c_ack_update_datapack_88xx(
				halmac_adapter, c2h_buf, c2h_size);
			break;
		case H2C_SUB_CMD_ID_RUN_DATAPACK_ACK:
			status = halmac_parse_h2c_ack_run_datapack_88xx(
				halmac_adapter, c2h_buf, c2h_size);
			break;
		case H2C_SUB_CMD_ID_CHANNEL_SWITCH_ACK:
			status = halmac_parse_h2c_ack_channel_switch_88xx(
				halmac_adapter, c2h_buf, c2h_size);
			break;
		case H2C_SUB_CMD_ID_IQK_ACK:
			status = halmac_parse_h2c_ack_iqk_88xx(
				halmac_adapter, c2h_buf, c2h_size);
			break;
		case H2C_SUB_CMD_ID_POWER_TRACKING_ACK:
			status = halmac_parse_h2c_ack_power_tracking_88xx(
				halmac_adapter, c2h_buf, c2h_size);
			break;
		case H2C_SUB_CMD_ID_PSD_ACK:
			break;
		default:
			pr_err("h2c_sub_cmd_id switch case out of boundary!!\n");
			status = HALMAC_RET_C2H_NOT_HANDLED;
			break;
		}
	}

	return status;
}