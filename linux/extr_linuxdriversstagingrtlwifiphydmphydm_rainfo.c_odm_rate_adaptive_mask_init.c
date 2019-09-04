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
struct odm_rate_adaptive {scalar_t__ type; int ldpc_thres; int is_use_ldpc; int high_rssi_thresh; int low_rssi_thresh; int /*<<< orphan*/  ratr_state; } ;
struct phy_dm_struct {int is_use_ra_mask; struct odm_rate_adaptive rate_adaptive; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_RATR_STA_INIT ; 
 scalar_t__ dm_type_by_driver ; 

void odm_rate_adaptive_mask_init(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct odm_rate_adaptive *odm_ra = &dm->rate_adaptive;

	odm_ra->type = dm_type_by_driver;
	if (odm_ra->type == dm_type_by_driver)
		dm->is_use_ra_mask = true;
	else
		dm->is_use_ra_mask = false;

	odm_ra->ratr_state = DM_RATR_STA_INIT;

	odm_ra->ldpc_thres = 35;
	odm_ra->is_use_ldpc = false;

	odm_ra->high_rssi_thresh = 50;
	odm_ra->low_rssi_thresh = 20;
}