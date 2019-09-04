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
struct fast_ant_train {scalar_t__ RxIdleAnt; } ;
struct odm_dm_struct {scalar_t__ AntDivType; struct adapter* Adapter; struct fast_ant_train DM_FatTable; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_ANT_CGCS_RX ; 
 int /*<<< orphan*/  AUX_ANT_CG_TRX ; 
 int BIT (int) ; 
 scalar_t__ CGCS_RX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_HW_ANTDIV ; 
 scalar_t__ MAIN_ANT ; 
 int /*<<< orphan*/  MAIN_ANT_CGCS_RX ; 
 int /*<<< orphan*/  MAIN_ANT_CG_TRX ; 
 int /*<<< orphan*/  ODM_REG_ANTSEL_CTRL_11N ; 
 int /*<<< orphan*/  ODM_REG_RESP_TX_11N ; 
 int /*<<< orphan*/  ODM_REG_RX_ANT_CTRL_11N ; 
 int /*<<< orphan*/  phy_set_bb_reg (struct adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void rtl88eu_dm_update_rx_idle_ant(struct odm_dm_struct *dm_odm, u8 ant)
{
	struct fast_ant_train *dm_fat_tbl = &dm_odm->DM_FatTable;
	struct adapter *adapter = dm_odm->Adapter;
	u32 default_ant, optional_ant;

	if (dm_fat_tbl->RxIdleAnt != ant) {
		if (ant == MAIN_ANT) {
			default_ant = (dm_odm->AntDivType == CG_TRX_HW_ANTDIV) ?
				       MAIN_ANT_CG_TRX : MAIN_ANT_CGCS_RX;
			optional_ant = (dm_odm->AntDivType == CG_TRX_HW_ANTDIV) ?
					AUX_ANT_CG_TRX : AUX_ANT_CGCS_RX;
		} else {
			default_ant = (dm_odm->AntDivType == CG_TRX_HW_ANTDIV) ?
				       AUX_ANT_CG_TRX : AUX_ANT_CGCS_RX;
			optional_ant = (dm_odm->AntDivType == CG_TRX_HW_ANTDIV) ?
					MAIN_ANT_CG_TRX : MAIN_ANT_CGCS_RX;
		}

		if (dm_odm->AntDivType == CG_TRX_HW_ANTDIV) {
			phy_set_bb_reg(adapter, ODM_REG_RX_ANT_CTRL_11N,
				       BIT(5) | BIT(4) | BIT(3), default_ant);
			phy_set_bb_reg(adapter, ODM_REG_RX_ANT_CTRL_11N,
				       BIT(8) | BIT(7) | BIT(6), optional_ant);
			phy_set_bb_reg(adapter, ODM_REG_ANTSEL_CTRL_11N,
				       BIT(14) | BIT(13) | BIT(12), default_ant);
			phy_set_bb_reg(adapter, ODM_REG_RESP_TX_11N,
				       BIT(6) | BIT(7), default_ant);
		} else if (dm_odm->AntDivType == CGCS_RX_HW_ANTDIV) {
			phy_set_bb_reg(adapter, ODM_REG_RX_ANT_CTRL_11N,
				       BIT(5) | BIT(4) | BIT(3), default_ant);
			phy_set_bb_reg(adapter, ODM_REG_RX_ANT_CTRL_11N,
				       BIT(8) | BIT(7) | BIT(6), optional_ant);
		}
	}
	dm_fat_tbl->RxIdleAnt = ant;
}