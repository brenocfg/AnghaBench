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
typedef  int u8 ;
struct lp8788_charger {int /*<<< orphan*/  lp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP8788_CHG_STATUS ; 
 int LP8788_NO_BATT_M ; 
 int lp8788_read_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int lp8788_get_battery_present(struct lp8788_charger *pchg,
				union power_supply_propval *val)
{
	u8 data;
	int ret;

	ret = lp8788_read_byte(pchg->lp, LP8788_CHG_STATUS, &data);
	if (ret)
		return ret;

	val->intval = !(data & LP8788_NO_BATT_M);
	return 0;
}