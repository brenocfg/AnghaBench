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
typedef  int u32 ;
struct dig_thres {int rf_gain_idx; int* big_jump_lmt; } ;
struct phy_dm_struct {struct dig_thres dm_dig_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_DIG ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int,int) ; 

void odm_update_agc_big_jump_lmt_8822b(struct phy_dm_struct *dm, u32 addr,
				       u32 data)
{
	struct dig_thres *dig_tab = &dm->dm_dig_table;
	u8 rf_gain_idx = (u8)((data & 0xFF000000) >> 24);
	u8 bb_gain_idx = (u8)((data & 0x00ff0000) >> 16);
	u8 agc_table_idx = (u8)((data & 0x00000f00) >> 8);
	static bool is_limit;

	if (addr != 0x81c)
		return;

	if (bb_gain_idx > 0x3c) {
		if ((rf_gain_idx == dig_tab->rf_gain_idx) && !is_limit) {
			is_limit = true;
			dig_tab->big_jump_lmt[agc_table_idx] = bb_gain_idx - 2;
			ODM_RT_TRACE(
				dm, ODM_COMP_DIG,
				"===> [AGC_TAB] big_jump_lmt [%d] = 0x%x\n",
				agc_table_idx,
				dig_tab->big_jump_lmt[agc_table_idx]);
		}
	} else {
		is_limit = false;
	}

	dig_tab->rf_gain_idx = rf_gain_idx;
}