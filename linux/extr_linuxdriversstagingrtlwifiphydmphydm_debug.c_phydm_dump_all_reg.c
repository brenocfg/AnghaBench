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
struct phy_dm_struct {scalar_t__ rf_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASKDWORD ; 
 scalar_t__ ODM_1T1R ; 
 scalar_t__ ODM_2T2R ; 
 scalar_t__ ODM_3T3R ; 
 int /*<<< orphan*/  ODM_RF_PATH_A ; 
 int /*<<< orphan*/  ODM_RF_PATH_B ; 
 int /*<<< orphan*/  ODM_RF_PATH_C ; 
 int /*<<< orphan*/  ODM_RF_PATH_D ; 
 int /*<<< orphan*/  PHYDM_VAST_INFO_SNPRINTF (char*,int,char*,...) ; 
 int /*<<< orphan*/  RFREGOFFSETMASK ; 
 int /*<<< orphan*/  odm_get_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_get_rf_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydm_dump_bb_reg (struct phy_dm_struct*,int*,char*,int*) ; 

__attribute__((used)) static void phydm_dump_all_reg(void *dm_void, u32 *_used, char *output,
			       u32 *_out_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 addr = 0;
	u32 used = *_used;
	u32 out_len = *_out_len;

	/* dump MAC register */
	PHYDM_VAST_INFO_SNPRINTF(output + used, out_len - used,
				 "MAC==========\n");
	for (addr = 0; addr < 0x7ff; addr += 4)
		PHYDM_VAST_INFO_SNPRINTF(output + used, out_len - used,
					 "0x%04x 0x%08x\n", addr,
					 odm_get_bb_reg(dm, addr, MASKDWORD));

	for (addr = 0x1000; addr < 0x17ff; addr += 4)
		PHYDM_VAST_INFO_SNPRINTF(output + used, out_len - used,
					 "0x%04x 0x%08x\n", addr,
					 odm_get_bb_reg(dm, addr, MASKDWORD));

	/* dump BB register */
	PHYDM_VAST_INFO_SNPRINTF(output + used, out_len - used,
				 "BB==========\n");
	phydm_dump_bb_reg(dm, &used, output, &out_len);

	/* dump RF register */
	PHYDM_VAST_INFO_SNPRINTF(output + used, out_len - used,
				 "RF-A==========\n");
	for (addr = 0; addr < 0xFF; addr++)
		PHYDM_VAST_INFO_SNPRINTF(output + used, out_len - used,
					 "0x%02x 0x%05x\n", addr,
					 odm_get_rf_reg(dm, ODM_RF_PATH_A, addr,
							RFREGOFFSETMASK));

	if (dm->rf_type > ODM_1T1R) {
		PHYDM_VAST_INFO_SNPRINTF(output + used, out_len - used,
					 "RF-B==========\n");
		for (addr = 0; addr < 0xFF; addr++)
			PHYDM_VAST_INFO_SNPRINTF(
				output + used, out_len - used,
				"0x%02x 0x%05x\n", addr,
				odm_get_rf_reg(dm, ODM_RF_PATH_B, addr,
					       RFREGOFFSETMASK));
	}

	if (dm->rf_type > ODM_2T2R) {
		PHYDM_VAST_INFO_SNPRINTF(output + used, out_len - used,
					 "RF-C==========\n");
		for (addr = 0; addr < 0xFF; addr++)
			PHYDM_VAST_INFO_SNPRINTF(
				output + used, out_len - used,
				"0x%02x 0x%05x\n", addr,
				odm_get_rf_reg(dm, ODM_RF_PATH_C, addr,
					       RFREGOFFSETMASK));
	}

	if (dm->rf_type > ODM_3T3R) {
		PHYDM_VAST_INFO_SNPRINTF(output + used, out_len - used,
					 "RF-D==========\n");
		for (addr = 0; addr < 0xFF; addr++)
			PHYDM_VAST_INFO_SNPRINTF(
				output + used, out_len - used,
				"0x%02x 0x%05x\n", addr,
				odm_get_rf_reg(dm, ODM_RF_PATH_D, addr,
					       RFREGOFFSETMASK));
	}
}