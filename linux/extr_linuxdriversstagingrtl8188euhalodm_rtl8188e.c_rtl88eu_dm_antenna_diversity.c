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
struct fast_ant_train {scalar_t__ bBecomeLinked; } ;
struct odm_dm_struct {int SupportAbility; scalar_t__ AntDivType; scalar_t__ bLinked; struct adapter* Adapter; struct fast_ant_train DM_FatTable; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ CGCS_RX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_HW_ANTDIV ; 
 int ODM_BB_ANT_DIV ; 
 int /*<<< orphan*/  ODM_COMP_ANT_DIV ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_REG_CCK_ANTDIV_PARA1_11N ; 
 int /*<<< orphan*/  ODM_REG_IGI_A_11N ; 
 int /*<<< orphan*/  ODM_REG_TX_ANT_CTRL_11N ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  phy_set_bb_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl88eu_dm_hw_ant_div (struct odm_dm_struct*) ; 

void rtl88eu_dm_antenna_diversity(struct odm_dm_struct *dm_odm)
{
	struct fast_ant_train *dm_fat_tbl = &dm_odm->DM_FatTable;
	struct adapter *adapter = dm_odm->Adapter;

	if (!(dm_odm->SupportAbility & ODM_BB_ANT_DIV))
		return;
	if (!dm_odm->bLinked) {
		ODM_RT_TRACE(dm_odm, ODM_COMP_ANT_DIV, ODM_DBG_LOUD,
			     ("ODM_AntennaDiversity_88E(): No Link.\n"));
		if (dm_fat_tbl->bBecomeLinked) {
			ODM_RT_TRACE(dm_odm, ODM_COMP_ANT_DIV, ODM_DBG_LOUD,
				     ("Need to Turn off HW AntDiv\n"));
			phy_set_bb_reg(adapter, ODM_REG_IGI_A_11N, BIT(7), 0);
			phy_set_bb_reg(adapter, ODM_REG_CCK_ANTDIV_PARA1_11N,
				       BIT(15), 0);
			if (dm_odm->AntDivType == CG_TRX_HW_ANTDIV)
				phy_set_bb_reg(adapter, ODM_REG_TX_ANT_CTRL_11N,
					       BIT(21), 0);
			dm_fat_tbl->bBecomeLinked = dm_odm->bLinked;
		}
		return;
	} else {
		if (!dm_fat_tbl->bBecomeLinked) {
			ODM_RT_TRACE(dm_odm, ODM_COMP_ANT_DIV, ODM_DBG_LOUD,
				     ("Need to Turn on HW AntDiv\n"));
			phy_set_bb_reg(adapter, ODM_REG_IGI_A_11N, BIT(7), 1);
			phy_set_bb_reg(adapter, ODM_REG_CCK_ANTDIV_PARA1_11N,
				       BIT(15), 1);
			if (dm_odm->AntDivType == CG_TRX_HW_ANTDIV)
				phy_set_bb_reg(adapter, ODM_REG_TX_ANT_CTRL_11N,
					       BIT(21), 1);
			dm_fat_tbl->bBecomeLinked = dm_odm->bLinked;
		}
	}
	if ((dm_odm->AntDivType == CG_TRX_HW_ANTDIV) ||
	    (dm_odm->AntDivType == CGCS_RX_HW_ANTDIV))
		rtl88eu_dm_hw_ant_div(dm_odm);
}