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
typedef  void* u8 ;
typedef  int u32 ;
struct ra_table {int RA_offset_direction; void* RA_threshold_offset; } ;
struct phy_dm_struct {struct ra_table dm_ra_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHYDM_SNPRINTF (char*,int,char*,...) ; 

void phydm_RA_debug_PCR(void *dm_void, u32 *const dm_value, u32 *_used,
			char *output, u32 *_out_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct ra_table *ra_tab = &dm->dm_ra_table;
	u32 used = *_used;
	u32 out_len = *_out_len;

	if (dm_value[0] == 100) {
		PHYDM_SNPRINTF(
			output + used, out_len - used,
			"[Get] PCR RA_threshold_offset = (( %s%d ))\n",
			((ra_tab->RA_threshold_offset == 0) ?
				 " " :
				 ((ra_tab->RA_offset_direction) ? "+" : "-")),
			ra_tab->RA_threshold_offset);
		/**/
	} else if (dm_value[0] == 0) {
		ra_tab->RA_offset_direction = 0;
		ra_tab->RA_threshold_offset = (u8)dm_value[1];
		PHYDM_SNPRINTF(output + used, out_len - used,
			       "[Set] PCR RA_threshold_offset = (( -%d ))\n",
			       ra_tab->RA_threshold_offset);
	} else if (dm_value[0] == 1) {
		ra_tab->RA_offset_direction = 1;
		ra_tab->RA_threshold_offset = (u8)dm_value[1];
		PHYDM_SNPRINTF(output + used, out_len - used,
			       "[Set] PCR RA_threshold_offset = (( +%d ))\n",
			       ra_tab->RA_threshold_offset);
	} else {
		PHYDM_SNPRINTF(output + used, out_len - used, "[Set] Error\n");
		/**/
	}
}