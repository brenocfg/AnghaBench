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
typedef  int u16 ;
struct phy_dm_struct {int nhm_cnt_0; int nhm_cnt_1; } ;

/* Variables and functions */

bool phydm_cal_nhm_cnt(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u16 base = 0;

	base = dm->nhm_cnt_0 + dm->nhm_cnt_1;

	if (base != 0) {
		dm->nhm_cnt_0 = ((dm->nhm_cnt_0) << 8) / base;
		dm->nhm_cnt_1 = ((dm->nhm_cnt_1) << 8) / base;
	}
	if ((dm->nhm_cnt_0 - dm->nhm_cnt_1) >= 100)
		return true; /*clean environment*/
	else
		return false; /*noisy environment*/
}