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
typedef  size_t u32 ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 size_t ODM_RF_PATH_A ; 
 size_t ODM_RF_PATH_B ; 
 int /*<<< orphan*/  RFREGOFFSETMASK ; 
 size_t RF_REG_NUM_8822B ; 
 size_t odm_get_rf_reg (struct phy_dm_struct*,size_t,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _iqk_backup_rf_8822b(struct phy_dm_struct *dm, u32 RF_backup[][2],
				 u32 *backup_rf_reg)
{
	u32 i;

	for (i = 0; i < RF_REG_NUM_8822B; i++) {
		RF_backup[i][ODM_RF_PATH_A] = odm_get_rf_reg(
			dm, ODM_RF_PATH_A, backup_rf_reg[i], RFREGOFFSETMASK);
		RF_backup[i][ODM_RF_PATH_B] = odm_get_rf_reg(
			dm, ODM_RF_PATH_B, backup_rf_reg[i], RFREGOFFSETMASK);
	}
}