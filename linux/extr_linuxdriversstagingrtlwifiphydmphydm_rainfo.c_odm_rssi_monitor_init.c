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
struct ra_table {int firstconnect; } ;
struct phy_dm_struct {struct ra_table dm_ra_table; } ;

/* Variables and functions */

void odm_rssi_monitor_init(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct ra_table *ra_tab = &dm->dm_ra_table;

	ra_tab->firstconnect = false;
}