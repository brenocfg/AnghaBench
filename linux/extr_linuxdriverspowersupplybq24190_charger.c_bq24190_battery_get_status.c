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
struct bq24190_dev_info {int f_reg; int /*<<< orphan*/  f_reg_lock; } ;

/* Variables and functions */
 int BQ24190_REG_F_CHRG_FAULT_MASK ; 
 int BQ24190_REG_F_CHRG_FAULT_SHIFT ; 
 int /*<<< orphan*/  BQ24190_REG_SS ; 
 int BQ24190_REG_SS_CHRG_STAT_MASK ; 
 int BQ24190_REG_SS_CHRG_STAT_SHIFT ; 
 int BQ24190_REG_SS_PG_STAT_MASK ; 
 int EIO ; 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int bq24190_read (struct bq24190_dev_info*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bq24190_battery_get_status(struct bq24190_dev_info *bdi,
		union power_supply_propval *val)
{
	u8 ss_reg, chrg_fault;
	int status, ret;

	mutex_lock(&bdi->f_reg_lock);
	chrg_fault = bdi->f_reg;
	mutex_unlock(&bdi->f_reg_lock);

	chrg_fault &= BQ24190_REG_F_CHRG_FAULT_MASK;
	chrg_fault >>= BQ24190_REG_F_CHRG_FAULT_SHIFT;

	ret = bq24190_read(bdi, BQ24190_REG_SS, &ss_reg);
	if (ret < 0)
		return ret;

	/*
	 * The battery must be discharging when any of these are true:
	 * - there is no good power source;
	 * - there is a charge fault.
	 * Could also be discharging when in "supplement mode" but
	 * there is no way to tell when its in that mode.
	 */
	if (!(ss_reg & BQ24190_REG_SS_PG_STAT_MASK) || chrg_fault) {
		status = POWER_SUPPLY_STATUS_DISCHARGING;
	} else {
		ss_reg &= BQ24190_REG_SS_CHRG_STAT_MASK;
		ss_reg >>= BQ24190_REG_SS_CHRG_STAT_SHIFT;

		switch (ss_reg) {
		case 0x0: /* Not Charging */
			status = POWER_SUPPLY_STATUS_NOT_CHARGING;
			break;
		case 0x1: /* Pre-charge */
		case 0x2: /* Fast Charging */
			status = POWER_SUPPLY_STATUS_CHARGING;
			break;
		case 0x3: /* Charge Termination Done */
			status = POWER_SUPPLY_STATUS_FULL;
			break;
		default:
			ret = -EIO;
		}
	}

	if (!ret)
		val->intval = status;

	return ret;
}