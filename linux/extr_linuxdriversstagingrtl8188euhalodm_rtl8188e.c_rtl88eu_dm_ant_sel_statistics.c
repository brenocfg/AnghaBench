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
typedef  size_t u32 ;
struct fast_ant_train {int /*<<< orphan*/ * AuxAnt_Cnt; int /*<<< orphan*/ * AuxAnt_Sum; int /*<<< orphan*/ * MainAnt_Cnt; int /*<<< orphan*/ * MainAnt_Sum; } ;
struct odm_dm_struct {scalar_t__ AntDivType; struct fast_ant_train DM_FatTable; } ;

/* Variables and functions */
 scalar_t__ CGCS_RX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_HW_ANTDIV ; 
 scalar_t__ MAIN_ANT_CGCS_RX ; 
 scalar_t__ MAIN_ANT_CG_TRX ; 

void rtl88eu_dm_ant_sel_statistics(struct odm_dm_struct *dm_odm,
				   u8 antsel_tr_mux, u32 mac_id, u8 rx_pwdb_all)
{
	struct fast_ant_train *dm_fat_tbl = &dm_odm->DM_FatTable;

	if (dm_odm->AntDivType == CG_TRX_HW_ANTDIV) {
		if (antsel_tr_mux == MAIN_ANT_CG_TRX) {
			dm_fat_tbl->MainAnt_Sum[mac_id] += rx_pwdb_all;
			dm_fat_tbl->MainAnt_Cnt[mac_id]++;
		} else {
			dm_fat_tbl->AuxAnt_Sum[mac_id] += rx_pwdb_all;
			dm_fat_tbl->AuxAnt_Cnt[mac_id]++;
		}
	} else if (dm_odm->AntDivType == CGCS_RX_HW_ANTDIV) {
		if (antsel_tr_mux == MAIN_ANT_CGCS_RX) {
			dm_fat_tbl->MainAnt_Sum[mac_id] += rx_pwdb_all;
			dm_fat_tbl->MainAnt_Cnt[mac_id]++;
		} else {
			dm_fat_tbl->AuxAnt_Sum[mac_id] += rx_pwdb_all;
			dm_fat_tbl->AuxAnt_Cnt[mac_id]++;
		}
	}
}