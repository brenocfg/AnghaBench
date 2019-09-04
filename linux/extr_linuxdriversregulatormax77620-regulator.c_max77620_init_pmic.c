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
struct max77620_regulator_pdata {int active_fps_src; scalar_t__ ramp_rate_setting; } ;
struct max77620_regulator {int* current_power_mode; int* enable_power_mode; struct max77620_regulator_pdata* reg_pdata; } ;

/* Variables and functions */
 int MAX77620_FPS_SRC_DEF ; 
 int MAX77620_FPS_SRC_NONE ; 
 int MAX77620_POWER_MODE_NORMAL ; 
 int /*<<< orphan*/  max77620_config_power_ok (struct max77620_regulator*,int) ; 
 int max77620_regulator_get_fps_src (struct max77620_regulator*,int) ; 
 int max77620_regulator_get_power_mode (struct max77620_regulator*,int) ; 
 int max77620_regulator_set_fps_slots (struct max77620_regulator*,int,int) ; 
 int max77620_regulator_set_fps_src (struct max77620_regulator*,int,int) ; 
 int max77620_regulator_set_power_mode (struct max77620_regulator*,int,int) ; 
 int max77620_set_slew_rate (struct max77620_regulator*,int,scalar_t__) ; 

__attribute__((used)) static int max77620_init_pmic(struct max77620_regulator *pmic, int id)
{
	struct max77620_regulator_pdata *rpdata = &pmic->reg_pdata[id];
	int ret;

	max77620_config_power_ok(pmic, id);

	/* Update power mode */
	ret = max77620_regulator_get_power_mode(pmic, id);
	if (ret < 0)
		return ret;

	pmic->current_power_mode[id] = ret;
	pmic->enable_power_mode[id] = MAX77620_POWER_MODE_NORMAL;

	if (rpdata->active_fps_src == MAX77620_FPS_SRC_DEF) {
		ret = max77620_regulator_get_fps_src(pmic, id);
		if (ret < 0)
			return ret;
		rpdata->active_fps_src = ret;
	}

	 /* If rails are externally control of FPS then enable it always. */
	if (rpdata->active_fps_src == MAX77620_FPS_SRC_NONE) {
		ret = max77620_regulator_set_power_mode(pmic,
					pmic->enable_power_mode[id], id);
		if (ret < 0)
			return ret;
	} else {
		if (pmic->current_power_mode[id] !=
		     pmic->enable_power_mode[id]) {
			ret = max77620_regulator_set_power_mode(pmic,
					pmic->enable_power_mode[id], id);
			if (ret < 0)
				return ret;
		}
	}

	ret = max77620_regulator_set_fps_src(pmic, rpdata->active_fps_src, id);
	if (ret < 0)
		return ret;

	ret = max77620_regulator_set_fps_slots(pmic, id, false);
	if (ret < 0)
		return ret;

	if (rpdata->ramp_rate_setting) {
		ret = max77620_set_slew_rate(pmic, id,
					     rpdata->ramp_rate_setting);
		if (ret < 0)
			return ret;
	}

	return 0;
}