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
typedef  scalar_t__ u32 ;
struct phy_dm_struct {int support_ic_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ CSI_MASK_ENABLE ; 
 int /*<<< orphan*/  ODM_COMP_API ; 
 int ODM_IC_11AC_SERIES ; 
 int ODM_IC_11N_SERIES ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void phydm_csi_mask_enable(void *dm_void, u32 enable)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 reg_value = 0;

	reg_value = (enable == CSI_MASK_ENABLE) ? 1 : 0;

	if (dm->support_ic_type & ODM_IC_11N_SERIES) {
		odm_set_bb_reg(dm, 0xD2C, BIT(28), reg_value);
		ODM_RT_TRACE(dm, ODM_COMP_API,
			     "Enable CSI Mask:  Reg 0xD2C[28] = ((0x%x))\n",
			     reg_value);

	} else if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		odm_set_bb_reg(dm, 0x874, BIT(0), reg_value);
		ODM_RT_TRACE(dm, ODM_COMP_API,
			     "Enable CSI Mask:  Reg 0x874[0] = ((0x%x))\n",
			     reg_value);
	}
}