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
struct bq27xxx_device_info {int opts; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BQ27XXX_O_ZERO ; 
 int /*<<< orphan*/  BQ27XXX_REG_FLAGS ; 
 int POWER_SUPPLY_HEALTH_COLD ; 
 int POWER_SUPPLY_HEALTH_DEAD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int /*<<< orphan*/  bq27xxx_battery_dead (struct bq27xxx_device_info*,int) ; 
 int /*<<< orphan*/  bq27xxx_battery_overtemp (struct bq27xxx_device_info*,int) ; 
 int /*<<< orphan*/  bq27xxx_battery_undertemp (struct bq27xxx_device_info*,int) ; 
 int bq27xxx_read (struct bq27xxx_device_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq27xxx_battery_read_health(struct bq27xxx_device_info *di)
{
	int flags;
	bool has_singe_flag = di->opts & BQ27XXX_O_ZERO;

	flags = bq27xxx_read(di, BQ27XXX_REG_FLAGS, has_singe_flag);
	if (flags < 0) {
		dev_err(di->dev, "error reading flag register:%d\n", flags);
		return flags;
	}

	/* Unlikely but important to return first */
	if (unlikely(bq27xxx_battery_overtemp(di, flags)))
		return POWER_SUPPLY_HEALTH_OVERHEAT;
	if (unlikely(bq27xxx_battery_undertemp(di, flags)))
		return POWER_SUPPLY_HEALTH_COLD;
	if (unlikely(bq27xxx_battery_dead(di, flags)))
		return POWER_SUPPLY_HEALTH_DEAD;

	return POWER_SUPPLY_HEALTH_GOOD;
}