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
typedef  scalar_t__ u8 ;
struct ra_table {scalar_t__ RA_threshold_offset; scalar_t__ RA_offset_direction; } ;
struct phy_dm_struct {struct ra_table dm_ra_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_RA_MASK ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 

void phydm_modify_RA_PCR_threshold(void *dm_void, u8 RA_offset_direction,
				   u8 RA_threshold_offset

				   )
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct ra_table *ra_tab = &dm->dm_ra_table;

	ra_tab->RA_offset_direction = RA_offset_direction;
	ra_tab->RA_threshold_offset = RA_threshold_offset;
	ODM_RT_TRACE(dm, ODM_COMP_RA_MASK,
		     "Set RA_threshold_offset = (( %s%d ))\n",
		     ((RA_threshold_offset == 0) ?
			      " " :
			      ((RA_offset_direction) ? "+" : "-")),
		     RA_threshold_offset);
}