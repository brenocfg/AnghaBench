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
struct phy_dm_struct {int rssi_min; } ;
struct dyn_pwr_saving {scalar_t__ pre_rf_state; void* cur_rf_state; } ;

/* Variables and functions */
 void* RF_MAX ; 
 scalar_t__ rf_normal ; 
 void* rf_save ; 

__attribute__((used)) static inline void phydm_update_rf_state(struct phy_dm_struct *dm,
					 struct dyn_pwr_saving *dm_ps_table,
					 int _rssi_up_bound,
					 int _rssi_low_bound,
					 int _is_force_in_normal)
{
	if (_is_force_in_normal) {
		dm_ps_table->cur_rf_state = rf_normal;
		return;
	}

	if (dm->rssi_min == 0xFF) {
		dm_ps_table->cur_rf_state = RF_MAX;
		return;
	}

	if (dm_ps_table->pre_rf_state == rf_normal) {
		if (dm->rssi_min >= _rssi_up_bound)
			dm_ps_table->cur_rf_state = rf_save;
		else
			dm_ps_table->cur_rf_state = rf_normal;
	} else {
		if (dm->rssi_min <= _rssi_low_bound)
			dm_ps_table->cur_rf_state = rf_normal;
		else
			dm_ps_table->cur_rf_state = rf_save;
	}
}