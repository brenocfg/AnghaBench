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
typedef  int /*<<< orphan*/  u8 ;
struct psd_info {int /*<<< orphan*/ * psd_result; } ;
struct phy_dm_struct {struct psd_info dm_psd_table; } ;

/* Variables and functions */

u8 phydm_get_psd_result_table(void *dm_void, int index)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct psd_info *dm_psd_table = &dm->dm_psd_table;
	u8 temp_result = 0;

	if (index < 128)
		temp_result = dm_psd_table->psd_result[index];

	return temp_result;
}