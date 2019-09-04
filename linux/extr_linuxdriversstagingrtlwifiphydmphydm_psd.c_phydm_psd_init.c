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
struct psd_info {int psd_in_progress; int psd_reg; int psd_report_reg; int psd_bw_rf_reg; scalar_t__ psd_pwr_common_offset; } ;
struct phy_dm_struct {int support_ic_type; struct psd_info dm_psd_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_API ; 
 scalar_t__ ODM_IC_11AC_2_SERIES ; 
 int ODM_IC_11AC_SERIES ; 
 int ODM_RTL8812 ; 
 int ODM_RTL8821 ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  phydm_psd_para_setting (struct phy_dm_struct*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void phydm_psd_init(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct psd_info *dm_psd_table = &dm->dm_psd_table;

	ODM_RT_TRACE(dm, ODM_COMP_API, "PSD para init\n");

	dm_psd_table->psd_in_progress = false;

	if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		dm_psd_table->psd_reg = 0x910;
		dm_psd_table->psd_report_reg = 0xF44;

		if (ODM_IC_11AC_2_SERIES)
			dm_psd_table->psd_bw_rf_reg =
				1; /*2b'11: 20MHz, 2b'10: 40MHz, 2b'01: 80MHz */
		else
			dm_psd_table->psd_bw_rf_reg =
				2; /*2b'11: 20MHz, 2b'10: 40MHz, 2b'01: 80MHz */

	} else {
		dm_psd_table->psd_reg = 0x808;
		dm_psd_table->psd_report_reg = 0x8B4;
		dm_psd_table->psd_bw_rf_reg =
			2; /*2b'11: 20MHz, 2b'10: 40MHz, 2b'01: 80MHz */
	}

	if (dm->support_ic_type == ODM_RTL8812)
		dm_psd_table->psd_pwr_common_offset = 0;
	else if (dm->support_ic_type == ODM_RTL8821)
		dm_psd_table->psd_pwr_common_offset = 0;
	else
		dm_psd_table->psd_pwr_common_offset = 0;

	phydm_psd_para_setting(dm, 1, 2, 3, 128, 0, 0, 7, 0);
	/*phydm_psd(dm, 0x3c, 0, 127);*/ /* target at -50dBm */
}