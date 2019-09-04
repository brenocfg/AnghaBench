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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACT8945A_APCH_CFG ; 
 int /*<<< orphan*/  ACT8945A_APCH_STATE ; 
 int /*<<< orphan*/  ACT8945A_APCH_STATUS ; 
 unsigned int APCH_CFG_SUSCHG ; 
 unsigned int APCH_STATE_CSTATE ; 
#define  APCH_STATE_CSTATE_DISABLED 131 
#define  APCH_STATE_CSTATE_EOC 130 
#define  APCH_STATE_CSTATE_FAST 129 
#define  APCH_STATE_CSTATE_PRE 128 
 unsigned int APCH_STATE_CSTATE_SHIFT ; 
 unsigned int APCH_STATUS_INDAT ; 
 unsigned int APCH_STATUS_TEMPDAT ; 
 unsigned int APCH_STATUS_TIMRDAT ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int POWER_SUPPLY_HEALTH_OVERVOLTAGE ; 
 int POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE ; 
 int POWER_SUPPLY_HEALTH_UNKNOWN ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int act8945a_get_battery_health(struct regmap *regmap, int *val)
{
	int ret;
	unsigned int status, state, config;

	ret = regmap_read(regmap, ACT8945A_APCH_STATUS, &status);
	if (ret < 0)
		return ret;

	ret = regmap_read(regmap, ACT8945A_APCH_CFG, &config);
	if (ret < 0)
		return ret;

	ret = regmap_read(regmap, ACT8945A_APCH_STATE, &state);
	if (ret < 0)
		return ret;

	state &= APCH_STATE_CSTATE;
	state >>= APCH_STATE_CSTATE_SHIFT;

	switch (state) {
	case APCH_STATE_CSTATE_DISABLED:
		if (config & APCH_CFG_SUSCHG) {
			*val = POWER_SUPPLY_HEALTH_UNKNOWN;
		} else if (status & APCH_STATUS_INDAT) {
			if (!(status & APCH_STATUS_TEMPDAT))
				*val = POWER_SUPPLY_HEALTH_OVERHEAT;
			else if (status & APCH_STATUS_TIMRDAT)
				*val = POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
			else
				*val = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		} else {
			*val = POWER_SUPPLY_HEALTH_GOOD;
		}
		break;
	case APCH_STATE_CSTATE_PRE:
	case APCH_STATE_CSTATE_FAST:
	case APCH_STATE_CSTATE_EOC:
	default:
		*val = POWER_SUPPLY_HEALTH_GOOD;
		break;
	}

	return 0;
}