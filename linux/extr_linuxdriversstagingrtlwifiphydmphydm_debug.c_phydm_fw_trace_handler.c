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
struct phy_dm_struct {int support_ic_type; int pre_c2h_seq; int fw_buff_is_enpty; char* fw_debug_trace; size_t c2h_cmd_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_FW_DEBUG_TRACE ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,char*) ; 
 int PHYDM_IC_3081_SERIES ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

void phydm_fw_trace_handler(void *dm_void, u8 *cmd_buf, u8 cmd_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	/*u8	debug_trace_11byte[60];*/
	u8 freg_num, c2h_seq, buf_0 = 0;

	if (!(dm->support_ic_type & PHYDM_IC_3081_SERIES))
		return;

	if (cmd_len > 12)
		return;

	buf_0 = cmd_buf[0];
	freg_num = (buf_0 & 0xf);
	c2h_seq = (buf_0 & 0xf0) >> 4;

	if (c2h_seq != dm->pre_c2h_seq && !dm->fw_buff_is_enpty) {
		dm->fw_debug_trace[dm->c2h_cmd_start] = '\0';
		ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE,
			     "[FW Dbg Queue Overflow] %s\n",
			     dm->fw_debug_trace);
		dm->c2h_cmd_start = 0;
	}

	if ((cmd_len - 1) > (60 - dm->c2h_cmd_start)) {
		dm->fw_debug_trace[dm->c2h_cmd_start] = '\0';
		ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE,
			     "[FW Dbg Queue error: wrong C2H length] %s\n",
			     dm->fw_debug_trace);
		dm->c2h_cmd_start = 0;
		return;
	}

	strncpy((char *)&dm->fw_debug_trace[dm->c2h_cmd_start],
		(char *)&cmd_buf[1], (cmd_len - 1));
	dm->c2h_cmd_start += (cmd_len - 1);
	dm->fw_buff_is_enpty = false;

	if (freg_num == 0 || dm->c2h_cmd_start >= 60) {
		if (dm->c2h_cmd_start < 60)
			dm->fw_debug_trace[dm->c2h_cmd_start] = '\0';
		else
			dm->fw_debug_trace[59] = '\0';

		ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "[FW DBG Msg] %s\n",
			     dm->fw_debug_trace);
		/*dbg_print("[FW DBG Msg] %s\n", dm->fw_debug_trace);*/
		dm->c2h_cmd_start = 0;
		dm->fw_buff_is_enpty = true;
	}

	dm->pre_c2h_seq = c2h_seq;
}