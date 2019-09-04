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
struct bq27xxx_device_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ27XXX_REG_VOLT ; 
 int bq27xxx_read (struct bq27xxx_device_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int bq27xxx_battery_voltage(struct bq27xxx_device_info *di,
				   union power_supply_propval *val)
{
	int volt;

	volt = bq27xxx_read(di, BQ27XXX_REG_VOLT, false);
	if (volt < 0) {
		dev_err(di->dev, "error reading voltage\n");
		return volt;
	}

	val->intval = volt * 1000;

	return 0;
}