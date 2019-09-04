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
struct dyn_pwr_saving {scalar_t__ initialize; scalar_t__ rssi_val_min; void* cur_rf_state; void* pre_rf_state; void* cur_cca_state; void* pre_cca_state; } ;
struct phy_dm_struct {struct dyn_pwr_saving dm_ps_table; } ;

/* Variables and functions */
 void* CCA_MAX ; 
 void* RF_MAX ; 

void odm_dynamic_bb_power_saving_init(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct dyn_pwr_saving *dm_ps_table = &dm->dm_ps_table;

	dm_ps_table->pre_cca_state = CCA_MAX;
	dm_ps_table->cur_cca_state = CCA_MAX;
	dm_ps_table->pre_rf_state = RF_MAX;
	dm_ps_table->cur_rf_state = RF_MAX;
	dm_ps_table->rssi_val_min = 0;
	dm_ps_table->initialize = 0;
}