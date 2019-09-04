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
struct power_supply_info {scalar_t__ charge_full_design; } ;
struct gab_platform_data {struct power_supply_info battery_info; } ;
struct gab {scalar_t__ level; int status; struct gab_platform_data* pdata; } ;

/* Variables and functions */
 int POWER_SUPPLY_STATUS_FULL ; 

__attribute__((used)) static int gab_get_status(struct gab *adc_bat)
{
	struct gab_platform_data *pdata = adc_bat->pdata;
	struct power_supply_info *bat_info;

	bat_info = &pdata->battery_info;
	if (adc_bat->level == bat_info->charge_full_design)
		return POWER_SUPPLY_STATUS_FULL;
	return adc_bat->status;
}