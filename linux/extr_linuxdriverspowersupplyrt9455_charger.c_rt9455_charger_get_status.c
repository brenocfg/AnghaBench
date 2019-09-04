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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct rt9455_info {TYPE_1__* client; int /*<<< orphan*/ * regmap_fields; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t F_PWR_RDY ; 
 size_t F_STAT ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_CHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_DISCHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_FULL ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int regmap_field_read (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int rt9455_charger_get_status(struct rt9455_info *info,
				     union power_supply_propval *val)
{
	unsigned int v, pwr_rdy;
	int ret;

	ret = regmap_field_read(info->regmap_fields[F_PWR_RDY],
				&pwr_rdy);
	if (ret) {
		dev_err(&info->client->dev, "Failed to read PWR_RDY bit\n");
		return ret;
	}

	/*
	 * If PWR_RDY bit is unset, the battery is discharging. Otherwise,
	 * STAT bits value must be checked.
	 */
	if (!pwr_rdy) {
		val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		return 0;
	}

	ret = regmap_field_read(info->regmap_fields[F_STAT], &v);
	if (ret) {
		dev_err(&info->client->dev, "Failed to read STAT bits\n");
		return ret;
	}

	switch (v) {
	case 0:
		/*
		 * If PWR_RDY bit is set, but STAT bits value is 0, the charger
		 * may be in one of the following cases:
		 * 1. CHG_EN bit is 0.
		 * 2. CHG_EN bit is 1 but the battery is not connected.
		 * In any of these cases, POWER_SUPPLY_STATUS_NOT_CHARGING is
		 * returned.
		 */
		val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		return 0;
	case 1:
		val->intval = POWER_SUPPLY_STATUS_CHARGING;
		return 0;
	case 2:
		val->intval = POWER_SUPPLY_STATUS_FULL;
		return 0;
	default:
		val->intval = POWER_SUPPLY_STATUS_UNKNOWN;
		return 0;
	}
}