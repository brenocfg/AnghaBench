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
struct dm_iqk_info {int* iqk_channel; int rf_reg18; } ;
struct phy_dm_struct {struct dm_iqk_info IQK_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_CALIBRATION ; 
 int /*<<< orphan*/  ODM_RF_PATH_A ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RFREGOFFSETMASK ; 
 int /*<<< orphan*/  _iqk_fill_iqk_report_8822b (struct phy_dm_struct*,int) ; 
 int /*<<< orphan*/  _iqk_reload_iqk_setting_8822b (struct phy_dm_struct*,int,int) ; 
 int odm_get_rf_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool _iqk_reload_iqk_8822b(struct phy_dm_struct *dm, bool reset)
{
	struct dm_iqk_info *iqk_info = &dm->IQK_info;
	u8 i;
	bool reload = false;

	if (reset) {
		for (i = 0; i < 2; i++)
			iqk_info->iqk_channel[i] = 0x0;
	} else {
		iqk_info->rf_reg18 = odm_get_rf_reg(dm, ODM_RF_PATH_A, 0x18,
						    RFREGOFFSETMASK);

		for (i = 0; i < 2; i++) {
			if (iqk_info->rf_reg18 == iqk_info->iqk_channel[i]) {
				_iqk_reload_iqk_setting_8822b(dm, i, 2);
				_iqk_fill_iqk_report_8822b(dm, i);
				ODM_RT_TRACE(
					dm, ODM_COMP_CALIBRATION,
					"[IQK]reload IQK result before!!!!\n");
				reload = true;
			}
		}
	}
	return reload;
}