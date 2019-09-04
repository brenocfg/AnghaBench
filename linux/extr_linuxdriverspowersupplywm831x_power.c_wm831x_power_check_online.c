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
union power_supply_propval {int intval; } ;
struct wm831x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM831X_SYSTEM_STATUS ; 
 int wm831x_reg_read (struct wm831x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm831x_power_check_online(struct wm831x *wm831x, int supply,
				     union power_supply_propval *val)
{
	int ret;

	ret = wm831x_reg_read(wm831x, WM831X_SYSTEM_STATUS);
	if (ret < 0)
		return ret;

	if (ret & supply)
		val->intval = 1;
	else
		val->intval = 0;

	return 0;
}