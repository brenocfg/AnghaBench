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
typedef  int /*<<< orphan*/  u32 ;
struct phy_dm_struct {int support_ic_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  ODM_COMP_API ; 
 int ODM_IC_11AC_SERIES ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_get_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ) ; 

u32 phydm_get_bb_dbg_port_value(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 dbg_port_value = 0;

	if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		dbg_port_value = odm_get_bb_reg(dm, 0xfa0, MASKDWORD);
		/**/
	} else /*if (dm->support_ic_type & ODM_IC_11N_SERIES)*/ {
		dbg_port_value = odm_get_bb_reg(dm, 0xdf4, MASKDWORD);
		/**/
	}
	ODM_RT_TRACE(dm, ODM_COMP_API, "dbg_port_value = 0x%x\n",
		     dbg_port_value);
	return dbg_port_value;
}