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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct bq24190_dev_info {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bq24190_cvc_vreg_values ; 

__attribute__((used)) static int bq24190_charger_get_voltage_max(struct bq24190_dev_info *bdi,
		union power_supply_propval *val)
{
	int idx = ARRAY_SIZE(bq24190_cvc_vreg_values) - 1;

	val->intval = bq24190_cvc_vreg_values[idx];
	return 0;
}