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
struct dig_thres {int enable_adjust_big_jump; int big_jump_step3; int big_jump_step2; int big_jump_step1; } ;
struct phy_dm_struct {struct dig_thres dm_dig_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 

__attribute__((used)) static void phydm_enable_big_jump(struct phy_dm_struct *dm, bool state)
{
	struct dig_thres *dig_tab = &dm->dm_dig_table;

	if (!state) {
		dm->dm_dig_table.enable_adjust_big_jump = false;
		odm_set_bb_reg(dm, 0x8c8, 0xfe,
			       ((dig_tab->big_jump_step3 << 5) |
				(dig_tab->big_jump_step2 << 3) |
				dig_tab->big_jump_step1));
	} else {
		dm->dm_dig_table.enable_adjust_big_jump = true;
	}
}