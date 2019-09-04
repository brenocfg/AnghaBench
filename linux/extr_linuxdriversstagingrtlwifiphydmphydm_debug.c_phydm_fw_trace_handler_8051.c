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
 int /*<<< orphan*/  ODM_FW_DEBUG_TRACE ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int*) ; 

void phydm_fw_trace_handler_8051(void *dm_void, u8 *buffer, u8 cmd_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	int i = 0;
	u8 extend_c2h_sub_id = 0, extend_c2h_dbg_len = 0,
	   extend_c2h_dbg_seq = 0;
	u8 fw_debug_trace[128];
	u8 *extend_c2h_dbg_content = NULL;

	if (cmd_len > 127)
		return;

	extend_c2h_sub_id = buffer[0];
	extend_c2h_dbg_len = buffer[1];
	extend_c2h_dbg_content = buffer + 2; /*DbgSeq+DbgContent  for show HEX*/

go_backfor_aggre_dbg_pkt:
	i = 0;
	extend_c2h_dbg_seq = buffer[2];
	extend_c2h_dbg_content = buffer + 3;

	for (;; i++) {
		fw_debug_trace[i] = extend_c2h_dbg_content[i];
		if (extend_c2h_dbg_content[i + 1] == '\0') {
			fw_debug_trace[i + 1] = '\0';
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "[FW DBG Msg] %s",
				     &fw_debug_trace[0]);
			break;
		} else if (extend_c2h_dbg_content[i] == '\n') {
			fw_debug_trace[i + 1] = '\0';
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "[FW DBG Msg] %s",
				     &fw_debug_trace[0]);
			buffer = extend_c2h_dbg_content + i + 3;
			goto go_backfor_aggre_dbg_pkt;
		}
	}
}