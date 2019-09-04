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
typedef  int u32 ;
struct phy_dm_struct {int support_ic_type; } ;

/* Variables and functions */
 int MASKBYTE0 ; 
 int MASKBYTE1 ; 
 int MASKBYTE2 ; 
 int MASKBYTE3 ; 
 int /*<<< orphan*/  ODM_FW_DEBUG_TRACE ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  PHYDM_H2C_FW_TRACE_EN ; 
 int PHYDM_IC_3081_SERIES ; 
 int /*<<< orphan*/  odm_fill_h2c_cmd (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int*) ; 

void phydm_fw_trace_en_h2c(void *dm_void, bool enable, u32 fw_debug_component,
			   u32 monitor_mode, u32 macid)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 h2c_parameter[7] = {0};
	u8 cmd_length;

	if (dm->support_ic_type & PHYDM_IC_3081_SERIES) {
		h2c_parameter[0] = enable;
		h2c_parameter[1] = (u8)(fw_debug_component & MASKBYTE0);
		h2c_parameter[2] = (u8)((fw_debug_component & MASKBYTE1) >> 8);
		h2c_parameter[3] = (u8)((fw_debug_component & MASKBYTE2) >> 16);
		h2c_parameter[4] = (u8)((fw_debug_component & MASKBYTE3) >> 24);
		h2c_parameter[5] = (u8)monitor_mode;
		h2c_parameter[6] = (u8)macid;
		cmd_length = 7;

	} else {
		h2c_parameter[0] = enable;
		h2c_parameter[1] = (u8)monitor_mode;
		h2c_parameter[2] = (u8)macid;
		cmd_length = 3;
	}

	ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "---->\n");
	if (monitor_mode == 0)
		ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE,
			     "[H2C] FW_debug_en: (( %d ))\n", enable);
	else
		ODM_RT_TRACE(
			dm, ODM_FW_DEBUG_TRACE,
			"[H2C] FW_debug_en: (( %d )), mode: (( %d )), macid: (( %d ))\n",
			enable, monitor_mode, macid);
	odm_fill_h2c_cmd(dm, PHYDM_H2C_FW_TRACE_EN, cmd_length, h2c_parameter);
}