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
struct phy_dm_struct {int fw_debug_components; int support_ic_type; int /*<<< orphan*/  debug_components; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_FW_DEBUG_TRACE ; 
 int PHYDM_FW_COMP_MU ; 
 int PHYDM_FW_COMP_PHY_CONFIG ; 
 int PHYDM_FW_COMP_RA ; 
 int PHYDM_IC_3081_SERIES ; 
 int /*<<< orphan*/  PHYDM_SNPRINTF (char*,int,char*,char*) ; 
 int /*<<< orphan*/  phydm_fw_trace_en_h2c (struct phy_dm_struct*,int,int,int,int) ; 

__attribute__((used)) static void phydm_fw_debug_trace(void *dm_void, u32 *const dm_value, u32 *_used,
				 char *output, u32 *_out_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 pre_fw_debug_components, one = 1;
	u32 used = *_used;
	u32 out_len = *_out_len;

	pre_fw_debug_components = dm->fw_debug_components;

	PHYDM_SNPRINTF(output + used, out_len - used, "\n%s\n",
		       "================================");
	if (dm_value[0] == 100) {
		PHYDM_SNPRINTF(output + used, out_len - used, "%s\n",
			       "[FW Debug Component]");
		PHYDM_SNPRINTF(output + used, out_len - used, "%s\n",
			       "================================");
		PHYDM_SNPRINTF(
			output + used, out_len - used, "00. (( %s ))RA\n",
			((dm->fw_debug_components & PHYDM_FW_COMP_RA) ? ("V") :
									(".")));

		if (dm->support_ic_type & PHYDM_IC_3081_SERIES) {
			PHYDM_SNPRINTF(
				output + used, out_len - used,
				"01. (( %s ))MU\n",
				((dm->fw_debug_components & PHYDM_FW_COMP_MU) ?
					 ("V") :
					 (".")));
			PHYDM_SNPRINTF(output + used, out_len - used,
				       "02. (( %s ))path Div\n",
				       ((dm->fw_debug_components &
					 PHYDM_FW_COMP_PHY_CONFIG) ?
						("V") :
						(".")));
			PHYDM_SNPRINTF(output + used, out_len - used,
				       "03. (( %s ))Phy Config\n",
				       ((dm->fw_debug_components &
					 PHYDM_FW_COMP_PHY_CONFIG) ?
						("V") :
						(".")));
		}
		PHYDM_SNPRINTF(output + used, out_len - used, "%s\n",
			       "================================");

	} else {
		if (dm_value[0] == 101) {
			dm->fw_debug_components = 0;
			PHYDM_SNPRINTF(output + used, out_len - used, "%s\n",
				       "Clear all fw debug components");
		} else {
			if (dm_value[1] == 1) /*enable*/
				dm->fw_debug_components |= (one << dm_value[0]);
			else if (dm_value[1] == 2) /*disable*/
				dm->fw_debug_components &=
					~(one << dm_value[0]);
			else
				PHYDM_SNPRINTF(
					output + used, out_len - used, "%s\n",
					"[Warning!!!]  1:enable,  2:disable");
		}

		if (dm->fw_debug_components == 0) {
			dm->debug_components &= ~ODM_FW_DEBUG_TRACE;
			phydm_fw_trace_en_h2c(
				dm, false, dm->fw_debug_components, dm_value[2],
				dm_value[3]); /*H2C to enable C2H Msg*/
		} else {
			dm->debug_components |= ODM_FW_DEBUG_TRACE;
			phydm_fw_trace_en_h2c(
				dm, true, dm->fw_debug_components, dm_value[2],
				dm_value[3]); /*H2C to enable C2H Msg*/
		}
	}
}