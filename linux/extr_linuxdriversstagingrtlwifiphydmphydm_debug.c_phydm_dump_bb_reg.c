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
struct phy_dm_struct {int support_ic_type; scalar_t__ rf_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASKDWORD ; 
 scalar_t__ ODM_2T2R ; 
 scalar_t__ ODM_3T3R ; 
 int ODM_IC_11N_SERIES ; 
 int ODM_RTL8814A ; 
 int ODM_RTL8821C ; 
 int ODM_RTL8822B ; 
 int /*<<< orphan*/  PHYDM_VAST_INFO_SNPRINTF (char*,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_get_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phydm_dump_bb_reg(void *dm_void, u32 *_used, char *output,
			      u32 *_out_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 addr = 0;
	u32 used = *_used;
	u32 out_len = *_out_len;

	/* For Nseries IC we only need to dump page8 to pageF using 3 digits*/
	for (addr = 0x800; addr < 0xfff; addr += 4) {
		if (dm->support_ic_type & ODM_IC_11N_SERIES)
			PHYDM_VAST_INFO_SNPRINTF(
				output + used, out_len - used,
				"0x%03x 0x%08x\n", addr,
				odm_get_bb_reg(dm, addr, MASKDWORD));
		else
			PHYDM_VAST_INFO_SNPRINTF(
				output + used, out_len - used,
				"0x%04x 0x%08x\n", addr,
				odm_get_bb_reg(dm, addr, MASKDWORD));
	}

	if (dm->support_ic_type &
	    (ODM_RTL8822B | ODM_RTL8814A | ODM_RTL8821C)) {
		if (dm->rf_type > ODM_2T2R) {
			for (addr = 0x1800; addr < 0x18ff; addr += 4)
				PHYDM_VAST_INFO_SNPRINTF(
					output + used, out_len - used,
					"0x%04x 0x%08x\n", addr,
					odm_get_bb_reg(dm, addr, MASKDWORD));
		}

		if (dm->rf_type > ODM_3T3R) {
			for (addr = 0x1a00; addr < 0x1aff; addr += 4)
				PHYDM_VAST_INFO_SNPRINTF(
					output + used, out_len - used,
					"0x%04x 0x%08x\n", addr,
					odm_get_bb_reg(dm, addr, MASKDWORD));
		}

		for (addr = 0x1900; addr < 0x19ff; addr += 4)
			PHYDM_VAST_INFO_SNPRINTF(
				output + used, out_len - used,
				"0x%04x 0x%08x\n", addr,
				odm_get_bb_reg(dm, addr, MASKDWORD));

		for (addr = 0x1c00; addr < 0x1cff; addr += 4)
			PHYDM_VAST_INFO_SNPRINTF(
				output + used, out_len - used,
				"0x%04x 0x%08x\n", addr,
				odm_get_bb_reg(dm, addr, MASKDWORD));

		for (addr = 0x1f00; addr < 0x1fff; addr += 4)
			PHYDM_VAST_INFO_SNPRINTF(
				output + used, out_len - used,
				"0x%04x 0x%08x\n", addr,
				odm_get_bb_reg(dm, addr, MASKDWORD));
	}
}