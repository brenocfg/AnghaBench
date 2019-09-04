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
struct power_supply_battery_info {int charge_full_design_uah; int energy_full_design_uwh; int voltage_min_design_uv; } ;
struct bq27xxx_dm_buf {scalar_t__ class; scalar_t__ block; scalar_t__ dirty; } ;
struct bq27xxx_device_info {int opts; } ;

/* Variables and functions */
 struct bq27xxx_dm_buf BQ27XXX_DM_BUF (struct bq27xxx_device_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BQ27XXX_DM_DESIGN_CAPACITY ; 
 int /*<<< orphan*/  BQ27XXX_DM_DESIGN_ENERGY ; 
 int /*<<< orphan*/  BQ27XXX_DM_TERMINATE_VOLTAGE ; 
 int /*<<< orphan*/  BQ27XXX_MSLEEP (int) ; 
 int BQ27XXX_O_CFGUP ; 
 int /*<<< orphan*/  BQ27XXX_REG_CTRL ; 
 int /*<<< orphan*/  BQ27XXX_RESET ; 
 int EINVAL ; 
 int /*<<< orphan*/  bq27xxx_battery_read_dm_block (struct bq27xxx_device_info*,struct bq27xxx_dm_buf*) ; 
 int /*<<< orphan*/  bq27xxx_battery_seal (struct bq27xxx_device_info*) ; 
 scalar_t__ bq27xxx_battery_unseal (struct bq27xxx_device_info*) ; 
 int /*<<< orphan*/  bq27xxx_battery_update_dm_block (struct bq27xxx_device_info*,struct bq27xxx_dm_buf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bq27xxx_battery_write_dm_block (struct bq27xxx_device_info*,struct bq27xxx_dm_buf*) ; 
 int /*<<< orphan*/  bq27xxx_write (struct bq27xxx_device_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bq27xxx_battery_set_config(struct bq27xxx_device_info *di,
				       struct power_supply_battery_info *info)
{
	struct bq27xxx_dm_buf bd = BQ27XXX_DM_BUF(di, BQ27XXX_DM_DESIGN_CAPACITY);
	struct bq27xxx_dm_buf bt = BQ27XXX_DM_BUF(di, BQ27XXX_DM_TERMINATE_VOLTAGE);
	bool updated;

	if (bq27xxx_battery_unseal(di) < 0)
		return;

	if (info->charge_full_design_uah != -EINVAL &&
	    info->energy_full_design_uwh != -EINVAL) {
		bq27xxx_battery_read_dm_block(di, &bd);
		/* assume design energy & capacity are in same block */
		bq27xxx_battery_update_dm_block(di, &bd,
					BQ27XXX_DM_DESIGN_CAPACITY,
					info->charge_full_design_uah / 1000);
		bq27xxx_battery_update_dm_block(di, &bd,
					BQ27XXX_DM_DESIGN_ENERGY,
					info->energy_full_design_uwh / 1000);
	}

	if (info->voltage_min_design_uv != -EINVAL) {
		bool same = bd.class == bt.class && bd.block == bt.block;
		if (!same)
			bq27xxx_battery_read_dm_block(di, &bt);
		bq27xxx_battery_update_dm_block(di, same ? &bd : &bt,
					BQ27XXX_DM_TERMINATE_VOLTAGE,
					info->voltage_min_design_uv / 1000);
	}

	updated = bd.dirty || bt.dirty;

	bq27xxx_battery_write_dm_block(di, &bd);
	bq27xxx_battery_write_dm_block(di, &bt);

	bq27xxx_battery_seal(di);

	if (updated && !(di->opts & BQ27XXX_O_CFGUP)) {
		bq27xxx_write(di, BQ27XXX_REG_CTRL, BQ27XXX_RESET, false);
		BQ27XXX_MSLEEP(300); /* reset time is not documented */
	}
	/* assume bq27xxx_battery_update() is called hereafter */
}