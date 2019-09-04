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
struct dig_thres {int /*<<< orphan*/  cur_ig_value; } ;
struct phy_dm_struct {struct dig_thres dm_dig_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  odm_ant_div_reset (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_set_edcca_threshold_api (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 

void odm_dm_reset(struct phy_dm_struct *dm)
{
	struct dig_thres *dig_tab = &dm->dm_dig_table;

	odm_ant_div_reset(dm);
	phydm_set_edcca_threshold_api(dm, dig_tab->cur_ig_value);
}