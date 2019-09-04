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
typedef  scalar_t__ u8 ;
struct phy_dm_struct {int support_ic_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_FW_DEBUG_TRACE ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  PHYDM_COMP_RA_DBG ; 
 int PHYDM_IC_3081_SERIES ; 
 scalar_t__ RADBG_DEBUG_MONITOR1 ; 
 scalar_t__ RADBG_DEBUG_MONITOR2 ; 
 scalar_t__ RADBG_DEBUG_MONITOR3 ; 
 scalar_t__ RADBG_DEBUG_MONITOR4 ; 
 scalar_t__ RADBG_DEBUG_MONITOR5 ; 

void odm_c2h_ra_para_report_handler(void *dm_void, u8 *cmd_buf, u8 cmd_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	u8 para_idx = cmd_buf[0]; /*Retry Penalty, NH, NL*/
	u8 i;

	ODM_RT_TRACE(dm, PHYDM_COMP_RA_DBG,
		     "[ From FW C2H RA Para ]  cmd_buf[0]= (( %d ))\n",
		     cmd_buf[0]);

	if (para_idx == RADBG_DEBUG_MONITOR1) {
		ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE,
			     "-------------------------------\n");
		if (dm->support_ic_type & PHYDM_IC_3081_SERIES) {
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %d\n",
				     "RSSI =", cmd_buf[1]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  0x%x\n",
				     "rate =", cmd_buf[2] & 0x7f);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %d\n",
				     "SGI =", (cmd_buf[2] & 0x80) >> 7);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %d\n",
				     "BW =", cmd_buf[3]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %d\n",
				     "BW_max =", cmd_buf[4]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  0x%x\n",
				     "multi_rate0 =", cmd_buf[5]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  0x%x\n",
				     "multi_rate1 =", cmd_buf[6]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %d\n",
				     "DISRA =", cmd_buf[7]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %d\n",
				     "VHT_EN =", cmd_buf[8]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %d\n",
				     "SGI_support =", cmd_buf[9]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %d\n",
				     "try_ness =", cmd_buf[10]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  0x%x\n",
				     "pre_rate =", cmd_buf[11]);
		} else {
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %d\n",
				     "RSSI =", cmd_buf[1]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %x\n",
				     "BW =", cmd_buf[2]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %d\n",
				     "DISRA =", cmd_buf[3]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %d\n",
				     "VHT_EN =", cmd_buf[4]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %d\n",
				     "Hightest rate =", cmd_buf[5]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  0x%x\n",
				     "Lowest rate =", cmd_buf[6]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  0x%x\n",
				     "SGI_support =", cmd_buf[7]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %d\n",
				     "Rate_ID =", cmd_buf[8]);
		}
		ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE,
			     "-------------------------------\n");
	} else if (para_idx == RADBG_DEBUG_MONITOR2) {
		ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE,
			     "-------------------------------\n");
		if (dm->support_ic_type & PHYDM_IC_3081_SERIES) {
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %d\n",
				     "rate_id =", cmd_buf[1]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  0x%x\n",
				     "highest_rate =", cmd_buf[2]);
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  0x%x\n",
				     "lowest_rate =", cmd_buf[3]);

			for (i = 4; i <= 11; i++)
				ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE,
					     "RAMASK =  0x%x\n", cmd_buf[i]);
		} else {
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE,
				     "%5s  %x%x  %x%x  %x%x  %x%x\n",
				     "RA Mask:", cmd_buf[8], cmd_buf[7],
				     cmd_buf[6], cmd_buf[5], cmd_buf[4],
				     cmd_buf[3], cmd_buf[2], cmd_buf[1]);
		}
		ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE,
			     "-------------------------------\n");
	} else if (para_idx == RADBG_DEBUG_MONITOR3) {
		for (i = 0; i < (cmd_len - 1); i++)
			ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE,
				     "content[%d] = %d\n", i, cmd_buf[1 + i]);
	} else if (para_idx == RADBG_DEBUG_MONITOR4) {
		ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  {%d.%d}\n",
			     "RA version =", cmd_buf[1], cmd_buf[2]);
	} else if (para_idx == RADBG_DEBUG_MONITOR5) {
		ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  0x%x\n",
			     "Current rate =", cmd_buf[1]);
		ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %d\n",
			     "Retry ratio =", cmd_buf[2]);
		ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  %d\n",
			     "rate down ratio =", cmd_buf[3]);
		ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  0x%x\n",
			     "highest rate =", cmd_buf[4]);
		ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  {0x%x 0x%x}\n",
			     "Muti-try =", cmd_buf[5], cmd_buf[6]);
		ODM_RT_TRACE(dm, ODM_FW_DEBUG_TRACE, "%5s  0x%x%x%x%x%x\n",
			     "RA mask =", cmd_buf[11], cmd_buf[10], cmd_buf[9],
			     cmd_buf[8], cmd_buf[7]);
	}
}