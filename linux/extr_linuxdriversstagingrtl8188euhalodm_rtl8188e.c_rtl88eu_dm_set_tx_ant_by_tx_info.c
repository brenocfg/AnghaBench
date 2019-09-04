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
typedef  size_t u8 ;
struct fast_ant_train {int /*<<< orphan*/ * antsel_c; int /*<<< orphan*/ * antsel_b; int /*<<< orphan*/ * antsel_a; } ;
struct odm_dm_struct {scalar_t__ AntDivType; struct fast_ant_train DM_FatTable; } ;

/* Variables and functions */
 scalar_t__ CG_TRX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_SMART_ANTDIV ; 
 int /*<<< orphan*/  SET_TX_DESC_ANTSEL_A_88E (size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_ANTSEL_B_88E (size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_ANTSEL_C_88E (size_t*,int /*<<< orphan*/ ) ; 

void rtl88eu_dm_set_tx_ant_by_tx_info(struct odm_dm_struct *dm_odm,
				      u8 *desc, u8 mac_id)
{
	struct fast_ant_train *dm_fat_tbl = &dm_odm->DM_FatTable;

	if ((dm_odm->AntDivType == CG_TRX_HW_ANTDIV) ||
	    (dm_odm->AntDivType == CG_TRX_SMART_ANTDIV)) {
		SET_TX_DESC_ANTSEL_A_88E(desc, dm_fat_tbl->antsel_a[mac_id]);
		SET_TX_DESC_ANTSEL_B_88E(desc, dm_fat_tbl->antsel_b[mac_id]);
		SET_TX_DESC_ANTSEL_C_88E(desc, dm_fat_tbl->antsel_c[mac_id]);
	}
}