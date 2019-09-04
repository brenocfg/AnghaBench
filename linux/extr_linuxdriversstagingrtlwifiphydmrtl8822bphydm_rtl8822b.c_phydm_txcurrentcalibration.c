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
typedef  int /*<<< orphan*/  u32 ;
struct phy_dm_struct {int efuse0x3d8; int efuse0x3d7; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_COMMON ; 
 int /*<<< orphan*/  ODM_RF_PATH_A ; 
 int /*<<< orphan*/  ODM_RF_PATH_B ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _txa_bias_cali_4_each_path (struct phy_dm_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  odm_get_rf_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  odm_set_rf_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

void phydm_txcurrentcalibration(struct phy_dm_struct *dm)
{
	u8 efuse0x3D8, efuse0x3D7;
	u32 orig_rf0x18_path_a = 0, orig_rf0x18_path_b = 0;

	/* save original 0x18 value */
	orig_rf0x18_path_a = odm_get_rf_reg(dm, ODM_RF_PATH_A, 0x18, 0xFFFFF);
	orig_rf0x18_path_b = odm_get_rf_reg(dm, ODM_RF_PATH_B, 0x18, 0xFFFFF);

	/* define efuse content */
	efuse0x3D8 = dm->efuse0x3d8;
	efuse0x3D7 = dm->efuse0x3d7;

	/* check efuse content to judge whether need to calibration or not */
	if (efuse0x3D7 == 0xFF) {
		ODM_RT_TRACE(
			dm, ODM_COMP_COMMON,
			"efuse content 0x3D7 == 0xFF, No need to do TxA cali\n");
		return;
	}

	/* write RF register for calibration */
	_txa_bias_cali_4_each_path(dm, ODM_RF_PATH_A, efuse0x3D7);
	_txa_bias_cali_4_each_path(dm, ODM_RF_PATH_B, efuse0x3D8);

	/* restore original 0x18 value */
	odm_set_rf_reg(dm, ODM_RF_PATH_A, 0x18, 0xFFFFF, orig_rf0x18_path_a);
	odm_set_rf_reg(dm, ODM_RF_PATH_B, 0x18, 0xFFFFF, orig_rf0x18_path_b);
}