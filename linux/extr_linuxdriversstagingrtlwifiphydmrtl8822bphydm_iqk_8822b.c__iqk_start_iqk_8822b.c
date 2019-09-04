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
typedef  int u32 ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  ODM_RF_PATH_A ; 
 int /*<<< orphan*/  ODM_RF_PATH_B ; 
 int /*<<< orphan*/  RFREGOFFSETMASK ; 
 int /*<<< orphan*/  _iqk_iqk_by_path_8822b (struct phy_dm_struct*,int) ; 
 int odm_get_rf_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_set_rf_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _iqk_start_iqk_8822b(struct phy_dm_struct *dm, bool segment_iqk)
{
	u32 tmp;

	/*GNT_WL = 1*/
	tmp = odm_get_rf_reg(dm, ODM_RF_PATH_A, 0x1, RFREGOFFSETMASK);
	tmp = tmp | BIT(5) | BIT(0);
	odm_set_rf_reg(dm, ODM_RF_PATH_A, 0x1, RFREGOFFSETMASK, tmp);

	tmp = odm_get_rf_reg(dm, ODM_RF_PATH_B, 0x1, RFREGOFFSETMASK);
	tmp = tmp | BIT(5) | BIT(0);
	odm_set_rf_reg(dm, ODM_RF_PATH_B, 0x1, RFREGOFFSETMASK, tmp);

	_iqk_iqk_by_path_8822b(dm, segment_iqk);
}