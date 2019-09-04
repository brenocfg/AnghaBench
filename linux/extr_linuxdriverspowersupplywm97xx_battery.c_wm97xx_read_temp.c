#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wm97xx_batt_pdata {unsigned long temp_mult; unsigned long temp_div; int /*<<< orphan*/  temp_aux; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct wm97xx_batt_pdata* power_supply_get_drvdata (struct power_supply*) ; 
 unsigned long wm97xx_read_aux_adc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long wm97xx_read_temp(struct power_supply *bat_ps)
{
	struct wm97xx_batt_pdata *pdata = power_supply_get_drvdata(bat_ps);

	return wm97xx_read_aux_adc(dev_get_drvdata(bat_ps->dev.parent),
					pdata->temp_aux) * pdata->temp_mult /
					pdata->temp_div;
}