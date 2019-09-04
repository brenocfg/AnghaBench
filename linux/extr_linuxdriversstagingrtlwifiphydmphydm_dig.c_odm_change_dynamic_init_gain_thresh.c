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
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
struct dig_thres {int dig_enable_flag; void* rx_gain_range_max; void* rx_gain_range_min; void* backoff_val; scalar_t__ rssi_low_thresh; scalar_t__ rssi_high_thresh; } ;
struct phy_dm_struct {struct dig_thres dm_dig_table; } ;

/* Variables and functions */
 scalar_t__ DIG_TYPE_BACKOFF ; 
 scalar_t__ DIG_TYPE_DISABLE ; 
 scalar_t__ DIG_TYPE_ENABLE ; 
 scalar_t__ DIG_TYPE_RX_GAIN_MAX ; 
 scalar_t__ DIG_TYPE_RX_GAIN_MIN ; 
 scalar_t__ DIG_TYPE_THRESH_HIGH ; 
 scalar_t__ DIG_TYPE_THRESH_LOW ; 

void odm_change_dynamic_init_gain_thresh(void *dm_void, u32 dm_type,
					 u32 dm_value)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct dig_thres *dig_tab = &dm->dm_dig_table;

	if (dm_type == DIG_TYPE_THRESH_HIGH) {
		dig_tab->rssi_high_thresh = dm_value;
	} else if (dm_type == DIG_TYPE_THRESH_LOW) {
		dig_tab->rssi_low_thresh = dm_value;
	} else if (dm_type == DIG_TYPE_ENABLE) {
		dig_tab->dig_enable_flag = true;
	} else if (dm_type == DIG_TYPE_DISABLE) {
		dig_tab->dig_enable_flag = false;
	} else if (dm_type == DIG_TYPE_BACKOFF) {
		if (dm_value > 30)
			dm_value = 30;
		dig_tab->backoff_val = (u8)dm_value;
	} else if (dm_type == DIG_TYPE_RX_GAIN_MIN) {
		if (dm_value == 0)
			dm_value = 0x1;
		dig_tab->rx_gain_range_min = (u8)dm_value;
	} else if (dm_type == DIG_TYPE_RX_GAIN_MAX) {
		if (dm_value > 0x50)
			dm_value = 0x50;
		dig_tab->rx_gain_range_max = (u8)dm_value;
	}
}