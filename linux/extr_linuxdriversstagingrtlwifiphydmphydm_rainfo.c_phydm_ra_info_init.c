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
struct ra_table {scalar_t__ RA_offset_direction; scalar_t__ RA_threshold_offset; scalar_t__ highest_client_tx_order; scalar_t__ highest_client_tx_rate_order; } ;
struct phy_dm_struct {struct ra_table dm_ra_table; } ;

/* Variables and functions */

void phydm_ra_info_init(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct ra_table *ra_tab = &dm->dm_ra_table;

	ra_tab->highest_client_tx_rate_order = 0;
	ra_tab->highest_client_tx_order = 0;
	ra_tab->RA_threshold_offset = 0;
	ra_tab->RA_offset_direction = 0;
}