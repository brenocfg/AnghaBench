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
struct phy_dm_struct {int support_ability; } ;

/* Variables and functions */
 int ODM_BB_NHM_CNT ; 
 int /*<<< orphan*/  phydm_get_nhm_counter_statistics (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_nhm_counter_statistics_reset (struct phy_dm_struct*) ; 

void phydm_nhm_counter_statistics(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	if (!(dm->support_ability & ODM_BB_NHM_CNT))
		return;

	/*Get NHM report*/
	phydm_get_nhm_counter_statistics(dm);

	/*Reset NHM counter*/
	phydm_nhm_counter_statistics_reset(dm);
}