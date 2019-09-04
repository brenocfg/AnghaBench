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
struct psd_info {int /*<<< orphan*/  psd_report_reg; int /*<<< orphan*/  psd_reg; } ;
struct phy_dm_struct {struct psd_info dm_psd_table; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  ODM_delay_us (int) ; 
 int odm_convert_to_db (int) ; 
 int odm_get_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int) ; 

u32 phydm_get_psd_data(void *dm_void, u32 psd_tone_idx, u32 igi)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct psd_info *dm_psd_table = &dm->dm_psd_table;
	u32 psd_report = 0;

	odm_set_bb_reg(dm, dm_psd_table->psd_reg, 0x3ff, psd_tone_idx);

	odm_set_bb_reg(dm, dm_psd_table->psd_reg, BIT(22),
		       1); /*PSD trigger start*/
	ODM_delay_us(10);
	odm_set_bb_reg(dm, dm_psd_table->psd_reg, BIT(22),
		       0); /*PSD trigger stop*/

	psd_report = odm_get_bb_reg(dm, dm_psd_table->psd_report_reg, 0xffff);
	psd_report = odm_convert_to_db(psd_report) + igi;

	return psd_report;
}