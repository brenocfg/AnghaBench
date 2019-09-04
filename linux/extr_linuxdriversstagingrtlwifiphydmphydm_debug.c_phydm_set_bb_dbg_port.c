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
typedef  int /*<<< orphan*/  u32 ;
struct phy_dm_struct {scalar_t__ pre_dbg_priority; int support_ic_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  ODM_COMP_API ; 
 int ODM_IC_11AC_SERIES ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 phydm_set_bb_dbg_port(void *dm_void, u8 curr_dbg_priority, u32 debug_port)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 dbg_port_result = false;

	if (curr_dbg_priority > dm->pre_dbg_priority) {
		if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
			odm_set_bb_reg(dm, 0x8fc, MASKDWORD, debug_port);
			/**/
		} else /*if (dm->support_ic_type & ODM_IC_11N_SERIES)*/ {
			odm_set_bb_reg(dm, 0x908, MASKDWORD, debug_port);
			/**/
		}
		ODM_RT_TRACE(
			dm, ODM_COMP_API,
			"DbgPort set success, Reg((0x%x)), Cur_priority=((%d)), Pre_priority=((%d))\n",
			debug_port, curr_dbg_priority, dm->pre_dbg_priority);
		dm->pre_dbg_priority = curr_dbg_priority;
		dbg_port_result = true;
	}

	return dbg_port_result;
}