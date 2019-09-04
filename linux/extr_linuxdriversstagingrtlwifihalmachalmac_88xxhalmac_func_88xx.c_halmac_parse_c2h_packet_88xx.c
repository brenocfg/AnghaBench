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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int rxdesc_size; } ;
struct halmac_adapter {void* driver_adapter; TYPE_1__ hw_config_info; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 scalar_t__ C2H_HDR_GET_C2H_SUB_CMD_ID (int*) ; 
 scalar_t__ C2H_HDR_GET_CMD_ID (int*) ; 
#define  C2H_SUB_CMD_ID_BT_COEX_INFO 133 
#define  C2H_SUB_CMD_ID_C2H_DBG 132 
#define  C2H_SUB_CMD_ID_EFUSE_DATA 131 
#define  C2H_SUB_CMD_ID_H2C_ACK_HDR 130 
#define  C2H_SUB_CMD_ID_PSD_DATA 129 
#define  C2H_SUB_CMD_ID_SCAN_STATUS_RPT 128 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  HALMAC_MSG_H2C ; 
 int HALMAC_RET_C2H_NOT_HANDLED ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int halmac_parse_c2h_debug_88xx (struct halmac_adapter*,int*,int) ; 
 int halmac_parse_efuse_data_88xx (struct halmac_adapter*,int*,int) ; 
 int halmac_parse_h2c_ack_88xx (struct halmac_adapter*,int*,int) ; 
 int halmac_parse_psd_data_88xx (struct halmac_adapter*,int*,int) ; 
 int halmac_parse_scan_status_rpt_88xx (struct halmac_adapter*,int*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

enum halmac_ret_status
halmac_parse_c2h_packet_88xx(struct halmac_adapter *halmac_adapter,
			     u8 *halmac_buf, u32 halmac_size)
{
	u8 c2h_cmd, c2h_sub_cmd_id;
	u8 *c2h_buf = halmac_buf + halmac_adapter->hw_config_info.rxdesc_size;
	u32 c2h_size = halmac_size - halmac_adapter->hw_config_info.rxdesc_size;
	void *driver_adapter = halmac_adapter->driver_adapter;
	enum halmac_ret_status status = HALMAC_RET_SUCCESS;

	c2h_cmd = (u8)C2H_HDR_GET_CMD_ID(c2h_buf);

	/* FW offload C2H cmd is 0xFF */
	if (c2h_cmd != 0xFF) {
		HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_H2C, DBG_DMESG,
				"C2H_PKT not for FwOffloadC2HFormat!!\n");
		return HALMAC_RET_C2H_NOT_HANDLED;
	}

	/* Get C2H sub cmd ID */
	c2h_sub_cmd_id = (u8)C2H_HDR_GET_C2H_SUB_CMD_ID(c2h_buf);

	switch (c2h_sub_cmd_id) {
	case C2H_SUB_CMD_ID_C2H_DBG:
		status = halmac_parse_c2h_debug_88xx(halmac_adapter, c2h_buf,
						     c2h_size);
		break;
	case C2H_SUB_CMD_ID_H2C_ACK_HDR:
		status = halmac_parse_h2c_ack_88xx(halmac_adapter, c2h_buf,
						   c2h_size);
		break;
	case C2H_SUB_CMD_ID_BT_COEX_INFO:
		status = HALMAC_RET_C2H_NOT_HANDLED;
		break;
	case C2H_SUB_CMD_ID_SCAN_STATUS_RPT:
		status = halmac_parse_scan_status_rpt_88xx(halmac_adapter,
							   c2h_buf, c2h_size);
		break;
	case C2H_SUB_CMD_ID_PSD_DATA:
		status = halmac_parse_psd_data_88xx(halmac_adapter, c2h_buf,
						    c2h_size);
		break;

	case C2H_SUB_CMD_ID_EFUSE_DATA:
		status = halmac_parse_efuse_data_88xx(halmac_adapter, c2h_buf,
						      c2h_size);
		break;
	default:
		pr_err("c2h_sub_cmd_id switch case out of boundary!!\n");
		pr_err("[ERR]c2h pkt : %.8X %.8X!!\n", *(u32 *)c2h_buf,
		       *(u32 *)(c2h_buf + 4));
		status = HALMAC_RET_C2H_NOT_HANDLED;
		break;
	}

	return status;
}