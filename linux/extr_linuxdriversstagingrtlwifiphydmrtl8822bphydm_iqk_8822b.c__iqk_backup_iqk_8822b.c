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
struct dm_iqk_info {int /*<<< orphan*/ ** bypass_iqk; int /*<<< orphan*/ ** lok_idac; int /*<<< orphan*/  rf_reg18; int /*<<< orphan*/ * iqk_channel; } ;
struct phy_dm_struct {struct dm_iqk_info IQK_info; } ;
typedef  enum odm_rf_radio_path { ____Placeholder_odm_rf_radio_path } odm_rf_radio_path ;

/* Variables and functions */
 int BIT (int) ; 
 int MASKDWORD ; 
 int /*<<< orphan*/  RFREGOFFSETMASK ; 
 int /*<<< orphan*/  odm_get_bb_reg (struct phy_dm_struct*,int,int) ; 
 int /*<<< orphan*/  odm_get_rf_reg (struct phy_dm_struct*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 
 int /*<<< orphan*/  phydm_backup_iqk_information (struct dm_iqk_info*) ; 
 int /*<<< orphan*/  phydm_set_iqk_cfir (struct phy_dm_struct*,struct dm_iqk_info*,int) ; 

__attribute__((used)) static void _iqk_backup_iqk_8822b(struct phy_dm_struct *dm, u8 step)
{
	struct dm_iqk_info *iqk_info = &dm->IQK_info;
	u8 path;
	u16 iqk_apply[2] = {0xc94, 0xe94};

	if (step == 0x0) {
		phydm_backup_iqk_information(iqk_info);
	} else {
		iqk_info->iqk_channel[0] = iqk_info->rf_reg18;
		for (path = 0; path < 2; path++) {
			iqk_info->lok_idac[0][path] =
				odm_get_rf_reg(dm, (enum odm_rf_radio_path)path,
					       0x58, RFREGOFFSETMASK);
			iqk_info->bypass_iqk[0][path] =
				odm_get_bb_reg(dm, iqk_apply[path], MASKDWORD);

			phydm_set_iqk_cfir(dm, iqk_info, path);
			odm_set_bb_reg(dm, 0x1bd8, MASKDWORD, 0x0);
			odm_set_bb_reg(dm, 0x1b0c, BIT(13) | BIT(12), 0x0);
		}
	}
}