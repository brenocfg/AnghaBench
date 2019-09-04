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
typedef  void* u16 ;
struct ccx_info {int nhm_inexclude_cca; int nhm_inexclude_txon; int NHM_period; int* NHM_th; int NHM_inexclude_cca_restore; int NHM_inexclude_txon_restore; int NHM_period_restore; int* NHM_th_restore; } ;
struct phy_dm_struct {int support_ic_type; struct ccx_info dm_ccx_info; } ;
typedef  enum nhm_inexclude_txon { ____Placeholder_nhm_inexclude_txon } nhm_inexclude_txon ;
typedef  enum nhm_inexclude_cca { ____Placeholder_nhm_inexclude_cca } nhm_inexclude_cca ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int CCX_EN ; 
 int /*<<< orphan*/  MASKBYTE0 ; 
 int /*<<< orphan*/  MASKBYTE1 ; 
 int /*<<< orphan*/  MASKBYTE2 ; 
 int /*<<< orphan*/  MASKBYTE3 ; 
 int /*<<< orphan*/  MASKHWORD ; 
 int ODM_IC_11AC_SERIES ; 
 int ODM_IC_11N_SERIES ; 
 int /*<<< orphan*/  ODM_REG_CCX_PERIOD_11AC ; 
 int /*<<< orphan*/  ODM_REG_CCX_PERIOD_11N ; 
 int /*<<< orphan*/  ODM_REG_NHM_TH3_TO_TH0_11AC ; 
 int /*<<< orphan*/  ODM_REG_NHM_TH3_TO_TH0_11N ; 
 int /*<<< orphan*/  ODM_REG_NHM_TH7_TO_TH4_11AC ; 
 int /*<<< orphan*/  ODM_REG_NHM_TH7_TO_TH4_11N ; 
 int /*<<< orphan*/  ODM_REG_NHM_TH8_11AC ; 
 int /*<<< orphan*/  ODM_REG_NHM_TH8_11N ; 
 int /*<<< orphan*/  ODM_REG_NHM_TH9_TH10_11AC ; 
 int /*<<< orphan*/  ODM_REG_NHM_TH9_TH10_11N ; 
 scalar_t__ RESTORE_NHM_SETTING ; 
 scalar_t__ SET_NHM_SETTING ; 
 scalar_t__ STORE_NHM_SETTING ; 
 scalar_t__ odm_get_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void phydm_nhm_setting(void *dm_void, u8 nhm_setting)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct ccx_info *ccx_info = &dm->dm_ccx_info;

	if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		if (nhm_setting == SET_NHM_SETTING) {
			/*Set inexclude_cca, inexclude_txon*/
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11AC, BIT(9),
				       ccx_info->nhm_inexclude_cca);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11AC, BIT(10),
				       ccx_info->nhm_inexclude_txon);

			/*Set NHM period*/
			odm_set_bb_reg(dm, ODM_REG_CCX_PERIOD_11AC, MASKHWORD,
				       ccx_info->NHM_period);

			/*Set NHM threshold*/
			odm_set_bb_reg(dm, ODM_REG_NHM_TH3_TO_TH0_11AC,
				       MASKBYTE0, ccx_info->NHM_th[0]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH3_TO_TH0_11AC,
				       MASKBYTE1, ccx_info->NHM_th[1]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH3_TO_TH0_11AC,
				       MASKBYTE2, ccx_info->NHM_th[2]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH3_TO_TH0_11AC,
				       MASKBYTE3, ccx_info->NHM_th[3]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH7_TO_TH4_11AC,
				       MASKBYTE0, ccx_info->NHM_th[4]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH7_TO_TH4_11AC,
				       MASKBYTE1, ccx_info->NHM_th[5]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH7_TO_TH4_11AC,
				       MASKBYTE2, ccx_info->NHM_th[6]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH7_TO_TH4_11AC,
				       MASKBYTE3, ccx_info->NHM_th[7]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH8_11AC, MASKBYTE0,
				       ccx_info->NHM_th[8]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11AC, MASKBYTE2,
				       ccx_info->NHM_th[9]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11AC, MASKBYTE3,
				       ccx_info->NHM_th[10]);

			/*CCX EN*/
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11AC, BIT(8),
				       CCX_EN);
		} else if (nhm_setting == STORE_NHM_SETTING) {
			/*Store prev. disable_ignore_cca, disable_ignore_txon*/
			ccx_info->NHM_inexclude_cca_restore =
				(enum nhm_inexclude_cca)odm_get_bb_reg(
					dm, ODM_REG_NHM_TH9_TH10_11AC, BIT(9));
			ccx_info->NHM_inexclude_txon_restore =
				(enum nhm_inexclude_txon)odm_get_bb_reg(
					dm, ODM_REG_NHM_TH9_TH10_11AC, BIT(10));

			/*Store pervious NHM period*/
			ccx_info->NHM_period_restore = (u16)odm_get_bb_reg(
				dm, ODM_REG_CCX_PERIOD_11AC, MASKHWORD);

			/*Store NHM threshold*/
			ccx_info->NHM_th_restore[0] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH3_TO_TH0_11AC, MASKBYTE0);
			ccx_info->NHM_th_restore[1] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH3_TO_TH0_11AC, MASKBYTE1);
			ccx_info->NHM_th_restore[2] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH3_TO_TH0_11AC, MASKBYTE2);
			ccx_info->NHM_th_restore[3] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH3_TO_TH0_11AC, MASKBYTE3);
			ccx_info->NHM_th_restore[4] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH7_TO_TH4_11AC, MASKBYTE0);
			ccx_info->NHM_th_restore[5] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH7_TO_TH4_11AC, MASKBYTE1);
			ccx_info->NHM_th_restore[6] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH7_TO_TH4_11AC, MASKBYTE2);
			ccx_info->NHM_th_restore[7] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH7_TO_TH4_11AC, MASKBYTE3);
			ccx_info->NHM_th_restore[8] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH8_11AC, MASKBYTE0);
			ccx_info->NHM_th_restore[9] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH9_TH10_11AC, MASKBYTE2);
			ccx_info->NHM_th_restore[10] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH9_TH10_11AC, MASKBYTE3);
		} else if (nhm_setting == RESTORE_NHM_SETTING) {
			/*Set disable_ignore_cca, disable_ignore_txon*/
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11AC, BIT(9),
				       ccx_info->NHM_inexclude_cca_restore);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11AC, BIT(10),
				       ccx_info->NHM_inexclude_txon_restore);

			/*Set NHM period*/
			odm_set_bb_reg(dm, ODM_REG_CCX_PERIOD_11AC, MASKHWORD,
				       ccx_info->NHM_period);

			/*Set NHM threshold*/
			odm_set_bb_reg(dm, ODM_REG_NHM_TH3_TO_TH0_11AC,
				       MASKBYTE0, ccx_info->NHM_th_restore[0]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH3_TO_TH0_11AC,
				       MASKBYTE1, ccx_info->NHM_th_restore[1]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH3_TO_TH0_11AC,
				       MASKBYTE2, ccx_info->NHM_th_restore[2]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH3_TO_TH0_11AC,
				       MASKBYTE3, ccx_info->NHM_th_restore[3]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH7_TO_TH4_11AC,
				       MASKBYTE0, ccx_info->NHM_th_restore[4]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH7_TO_TH4_11AC,
				       MASKBYTE1, ccx_info->NHM_th_restore[5]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH7_TO_TH4_11AC,
				       MASKBYTE2, ccx_info->NHM_th_restore[6]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH7_TO_TH4_11AC,
				       MASKBYTE3, ccx_info->NHM_th_restore[7]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH8_11AC, MASKBYTE0,
				       ccx_info->NHM_th_restore[8]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11AC, MASKBYTE2,
				       ccx_info->NHM_th_restore[9]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11AC, MASKBYTE3,
				       ccx_info->NHM_th_restore[10]);
		} else {
			return;
		}
	}

	else if (dm->support_ic_type & ODM_IC_11N_SERIES) {
		if (nhm_setting == SET_NHM_SETTING) {
			/*Set disable_ignore_cca, disable_ignore_txon*/
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11N, BIT(9),
				       ccx_info->nhm_inexclude_cca);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11N, BIT(10),
				       ccx_info->nhm_inexclude_txon);

			/*Set NHM period*/
			odm_set_bb_reg(dm, ODM_REG_CCX_PERIOD_11N, MASKHWORD,
				       ccx_info->NHM_period);

			/*Set NHM threshold*/
			odm_set_bb_reg(dm, ODM_REG_NHM_TH3_TO_TH0_11N,
				       MASKBYTE0, ccx_info->NHM_th[0]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH3_TO_TH0_11N,
				       MASKBYTE1, ccx_info->NHM_th[1]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH3_TO_TH0_11N,
				       MASKBYTE2, ccx_info->NHM_th[2]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH3_TO_TH0_11N,
				       MASKBYTE3, ccx_info->NHM_th[3]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH7_TO_TH4_11N,
				       MASKBYTE0, ccx_info->NHM_th[4]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH7_TO_TH4_11N,
				       MASKBYTE1, ccx_info->NHM_th[5]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH7_TO_TH4_11N,
				       MASKBYTE2, ccx_info->NHM_th[6]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH7_TO_TH4_11N,
				       MASKBYTE3, ccx_info->NHM_th[7]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH8_11N, MASKBYTE0,
				       ccx_info->NHM_th[8]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11N, MASKBYTE2,
				       ccx_info->NHM_th[9]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11N, MASKBYTE3,
				       ccx_info->NHM_th[10]);

			/*CCX EN*/
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11N, BIT(8),
				       CCX_EN);
		} else if (nhm_setting == STORE_NHM_SETTING) {
			/*Store prev. disable_ignore_cca, disable_ignore_txon*/
			ccx_info->NHM_inexclude_cca_restore =
				(enum nhm_inexclude_cca)odm_get_bb_reg(
					dm, ODM_REG_NHM_TH9_TH10_11N, BIT(9));
			ccx_info->NHM_inexclude_txon_restore =
				(enum nhm_inexclude_txon)odm_get_bb_reg(
					dm, ODM_REG_NHM_TH9_TH10_11N, BIT(10));

			/*Store pervious NHM period*/
			ccx_info->NHM_period_restore = (u16)odm_get_bb_reg(
				dm, ODM_REG_CCX_PERIOD_11N, MASKHWORD);

			/*Store NHM threshold*/
			ccx_info->NHM_th_restore[0] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH3_TO_TH0_11N, MASKBYTE0);
			ccx_info->NHM_th_restore[1] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH3_TO_TH0_11N, MASKBYTE1);
			ccx_info->NHM_th_restore[2] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH3_TO_TH0_11N, MASKBYTE2);
			ccx_info->NHM_th_restore[3] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH3_TO_TH0_11N, MASKBYTE3);
			ccx_info->NHM_th_restore[4] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH7_TO_TH4_11N, MASKBYTE0);
			ccx_info->NHM_th_restore[5] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH7_TO_TH4_11N, MASKBYTE1);
			ccx_info->NHM_th_restore[6] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH7_TO_TH4_11N, MASKBYTE2);
			ccx_info->NHM_th_restore[7] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH7_TO_TH4_11N, MASKBYTE3);
			ccx_info->NHM_th_restore[8] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH8_11N, MASKBYTE0);
			ccx_info->NHM_th_restore[9] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH9_TH10_11N, MASKBYTE2);
			ccx_info->NHM_th_restore[10] = (u8)odm_get_bb_reg(
				dm, ODM_REG_NHM_TH9_TH10_11N, MASKBYTE3);
		} else if (nhm_setting == RESTORE_NHM_SETTING) {
			/*Set disable_ignore_cca, disable_ignore_txon*/
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11N, BIT(9),
				       ccx_info->NHM_inexclude_cca_restore);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11N, BIT(10),
				       ccx_info->NHM_inexclude_txon_restore);

			/*Set NHM period*/
			odm_set_bb_reg(dm, ODM_REG_CCX_PERIOD_11N, MASKHWORD,
				       ccx_info->NHM_period_restore);

			/*Set NHM threshold*/
			odm_set_bb_reg(dm, ODM_REG_NHM_TH3_TO_TH0_11N,
				       MASKBYTE0, ccx_info->NHM_th_restore[0]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH3_TO_TH0_11N,
				       MASKBYTE1, ccx_info->NHM_th_restore[1]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH3_TO_TH0_11N,
				       MASKBYTE2, ccx_info->NHM_th_restore[2]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH3_TO_TH0_11N,
				       MASKBYTE3, ccx_info->NHM_th_restore[3]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH7_TO_TH4_11N,
				       MASKBYTE0, ccx_info->NHM_th_restore[4]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH7_TO_TH4_11N,
				       MASKBYTE1, ccx_info->NHM_th_restore[5]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH7_TO_TH4_11N,
				       MASKBYTE2, ccx_info->NHM_th_restore[6]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH7_TO_TH4_11N,
				       MASKBYTE3, ccx_info->NHM_th_restore[7]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH8_11N, MASKBYTE0,
				       ccx_info->NHM_th_restore[8]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11N, MASKBYTE2,
				       ccx_info->NHM_th_restore[9]);
			odm_set_bb_reg(dm, ODM_REG_NHM_TH9_TH10_11N, MASKBYTE3,
				       ccx_info->NHM_th_restore[10]);
		} else {
			return;
		}
	}
}