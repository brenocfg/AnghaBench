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
 int BQ27XXX_POWER_CONSTANT ; 
 int /*<<< orphan*/  BQ27XXX_REG_AP ; 
 int BQ27XXX_RS ; 
 int bq27xxx_read (struct bq27xxx_device_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bq27xxx_battery_read_pwr_avg(struct bq27xxx_device_info *di)
{
	int tval;

	tval = bq27xxx_read(di, BQ27XXX_REG_AP, false);
	if (tval < 0) {
		dev_err(di->dev, "error reading average power register  %02x: %d\n",
			BQ27XXX_REG_AP, tval);
		return tval;
	}

	if (di->opts & BQ27XXX_O_ZERO)
		return (tval * BQ27XXX_POWER_CONSTANT) / BQ27XXX_RS;
	else
		return tval;
}