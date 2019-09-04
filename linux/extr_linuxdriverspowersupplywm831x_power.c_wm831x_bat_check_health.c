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
struct wm831x {int dummy; } ;

/* Variables and functions */
 int POWER_SUPPLY_HEALTH_COLD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int POWER_SUPPLY_HEALTH_OVERVOLTAGE ; 
 int POWER_SUPPLY_HEALTH_UNSPEC_FAILURE ; 
 int WM831X_BATT_COLD_STS ; 
 int WM831X_BATT_HOT_STS ; 
 int WM831X_BATT_OV_STS ; 
 int /*<<< orphan*/  WM831X_CHARGER_STATUS ; 
#define  WM831X_CHG_STATE_DEFECTIVE 130 
#define  WM831X_CHG_STATE_FAST_OT 129 
 int WM831X_CHG_STATE_MASK ; 
#define  WM831X_CHG_STATE_TRICKLE_OT 128 
 int wm831x_reg_read (struct wm831x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm831x_bat_check_health(struct wm831x *wm831x, int *health)
{
	int ret;

	ret = wm831x_reg_read(wm831x, WM831X_CHARGER_STATUS);
	if (ret < 0)
		return ret;

	if (ret & WM831X_BATT_HOT_STS) {
		*health = POWER_SUPPLY_HEALTH_OVERHEAT;
		return 0;
	}

	if (ret & WM831X_BATT_COLD_STS) {
		*health = POWER_SUPPLY_HEALTH_COLD;
		return 0;
	}

	if (ret & WM831X_BATT_OV_STS) {
		*health = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		return 0;
	}

	switch (ret & WM831X_CHG_STATE_MASK) {
	case WM831X_CHG_STATE_TRICKLE_OT:
	case WM831X_CHG_STATE_FAST_OT:
		*health = POWER_SUPPLY_HEALTH_OVERHEAT;
		break;
	case WM831X_CHG_STATE_DEFECTIVE:
		*health = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		break;
	default:
		*health = POWER_SUPPLY_HEALTH_GOOD;
		break;
	}

	return 0;
}