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
struct phy_dm_struct {int support_ic_type; } ;
typedef  enum odm_rf_radio_path { ____Placeholder_odm_rf_radio_path } odm_rf_radio_path ;

/* Variables and functions */
 int ODM_RATEMCS15 ; 
 int ODM_RATEVHTSS2MCS9 ; 
 int ODM_RTL8197F ; 
 int ODM_RTL8821C ; 
 int ODM_RTL8822B ; 
 int /*<<< orphan*/  PHYDM_SNPRINTF (char*,int,char*,char*,int,char*,...) ; 
 int phydm_api_set_txagc (struct phy_dm_struct*,int,int,int,int) ; 

__attribute__((used)) static inline void phydm_check_dmval_txagc(struct phy_dm_struct *dm, u32 used,
					   u32 out_len, u32 *const dm_value,
					   char *output)
{
	if ((u8)dm_value[2] != 0xff) {
		if (phydm_api_set_txagc(dm, dm_value[3],
					(enum odm_rf_radio_path)dm_value[1],
					(u8)dm_value[2], true))
			PHYDM_SNPRINTF(output + used, out_len - used,
				       "  %s%d   %s%x%s%x\n", "Write path-",
				       dm_value[1], "rate index-0x",
				       dm_value[2], " = 0x", dm_value[3]);
		else
			PHYDM_SNPRINTF(output + used, out_len - used,
				       "  %s%d   %s%x%s\n", "Write path-",
				       (dm_value[1] & 0x1), "rate index-0x",
				       (dm_value[2] & 0x7f), " fail");
	} else {
		u8 i;
		u32 power_index;
		bool status = true;

		power_index = (dm_value[3] & 0x3f);

		if (dm->support_ic_type & (ODM_RTL8822B | ODM_RTL8821C)) {
			power_index = (power_index << 24) |
				      (power_index << 16) | (power_index << 8) |
				      (power_index);
			for (i = 0; i < ODM_RATEVHTSS2MCS9; i += 4)
				status = (status &
					  phydm_api_set_txagc(
						  dm, power_index,
						  (enum odm_rf_radio_path)
							  dm_value[1],
						  i, false));
		} else if (dm->support_ic_type & ODM_RTL8197F) {
			for (i = 0; i <= ODM_RATEMCS15; i++)
				status = (status &
					  phydm_api_set_txagc(
						  dm, power_index,
						  (enum odm_rf_radio_path)
							  dm_value[1],
						  i, false));
		}

		if (status)
			PHYDM_SNPRINTF(output + used, out_len - used,
				       "  %s%d   %s%x\n",
				       "Write all TXAGC of path-", dm_value[1],
				       " = 0x", dm_value[3]);
		else
			PHYDM_SNPRINTF(output + used, out_len - used,
				       "  %s%d   %s\n",
				       "Write all TXAGC of path-", dm_value[1],
				       " fail");
	}
}