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
typedef  int u16 ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_FW_DEBUG_TRACE ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int,...) ; 

void phydm_fw_trace_handler_code(void *dm_void, u8 *buffer, u8 cmd_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 function = buffer[0];
	u8 dbg_num = buffer[1];
	u16 content_0 = (((u16)buffer[3]) << 8) | ((u16)buffer[2]);
	u16 content_1 = (((u16)buffer[5]) << 8) | ((u16)buffer[4]);
	u16 content_2 = (((u16)buffer[7]) << 8) | ((u16)buffer[6]);
	u16 content_3 = (((u16)buffer[9]) << 8) | ((u16)buffer[8]);
	u16 content_4 = (((u16)buffer[11]) << 8) | ((u16)buffer[10]);

	if (cmd_len > 12)
		ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE,
			     "[FW Msg] Invalid cmd length (( %d )) >12\n",
			     cmd_len);

	/*--------------------------------------------*/
	ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE,
		     "[FW][general][%d, %d, %d] = {%d, %d, %d, %d}\n", function,
		     dbg_num, content_0, content_1, content_2, content_3,
		     content_4);
	/*--------------------------------------------*/
}