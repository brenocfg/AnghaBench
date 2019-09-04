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
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
#define  PHYDM_C2H_DBG 134 
#define  PHYDM_C2H_DBG_CODE 133 
#define  PHYDM_C2H_DYNAMIC_TX_PATH_RPT 132 
#define  PHYDM_C2H_EXTEND 131 
#define  PHYDM_C2H_IQK_FINISH 130 
#define  PHYDM_C2H_RA_PARA_RPT 129 
#define  PHYDM_C2H_RA_RPT 128 
 int PHYDM_EXTEND_C2H_DBG_PRINT ; 
 int /*<<< orphan*/  odm_c2h_ra_para_report_handler (struct phy_dm_struct*,int*,int) ; 
 int /*<<< orphan*/  phydm_c2h_ra_report_handler (struct phy_dm_struct*,int*,int) ; 
 int /*<<< orphan*/  phydm_fw_trace_handler (struct phy_dm_struct*,int*,int) ; 
 int /*<<< orphan*/  phydm_fw_trace_handler_8051 (struct phy_dm_struct*,int*,int) ; 
 int /*<<< orphan*/  phydm_fw_trace_handler_code (struct phy_dm_struct*,int*,int) ; 

u8 phydm_c2H_content_parsing(void *dm_void, u8 c2h_cmd_id, u8 c2h_cmd_len,
			     u8 *tmp_buf)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 extend_c2h_sub_id = 0;
	u8 find_c2h_cmd = true;

	switch (c2h_cmd_id) {
	case PHYDM_C2H_DBG:
		phydm_fw_trace_handler(dm, tmp_buf, c2h_cmd_len);
		break;

	case PHYDM_C2H_RA_RPT:
		phydm_c2h_ra_report_handler(dm, tmp_buf, c2h_cmd_len);
		break;

	case PHYDM_C2H_RA_PARA_RPT:
		odm_c2h_ra_para_report_handler(dm, tmp_buf, c2h_cmd_len);
		break;

	case PHYDM_C2H_DYNAMIC_TX_PATH_RPT:
		break;

	case PHYDM_C2H_IQK_FINISH:
		break;

	case PHYDM_C2H_DBG_CODE:
		phydm_fw_trace_handler_code(dm, tmp_buf, c2h_cmd_len);
		break;

	case PHYDM_C2H_EXTEND:
		extend_c2h_sub_id = tmp_buf[0];
		if (extend_c2h_sub_id == PHYDM_EXTEND_C2H_DBG_PRINT)
			phydm_fw_trace_handler_8051(dm, tmp_buf, c2h_cmd_len);

		break;

	default:
		find_c2h_cmd = false;
		break;
	}

	return find_c2h_cmd;
}