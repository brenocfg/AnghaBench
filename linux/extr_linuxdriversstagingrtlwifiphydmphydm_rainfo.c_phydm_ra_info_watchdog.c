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
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  odm_refresh_basic_rate_mask (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_refresh_rate_adaptive_mask (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_ra_common_info_update (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_ra_dynamic_retry_count (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_ra_dynamic_retry_limit (struct phy_dm_struct*) ; 

void phydm_ra_info_watchdog(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	phydm_ra_common_info_update(dm);
	phydm_ra_dynamic_retry_limit(dm);
	phydm_ra_dynamic_retry_count(dm);
	odm_refresh_rate_adaptive_mask(dm);
	odm_refresh_basic_rate_mask(dm);
}