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
 int BQ27XXX_CURRENT_CONSTANT ; 
 int BQ27XXX_O_ZERO ; 
 int /*<<< orphan*/  BQ27XXX_REG_DCAP ; 
 int BQ27XXX_RS ; 
 int bq27xxx_read (struct bq27xxx_device_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int bq27xxx_battery_read_dcap(struct bq27xxx_device_info *di)
{
	int dcap;

	if (di->opts & BQ27XXX_O_ZERO)
		dcap = bq27xxx_read(di, BQ27XXX_REG_DCAP, true);
	else
		dcap = bq27xxx_read(di, BQ27XXX_REG_DCAP, false);

	if (dcap < 0) {
		dev_dbg(di->dev, "error reading initial last measured discharge\n");
		return dcap;
	}

	if (di->opts & BQ27XXX_O_ZERO)
		dcap = (dcap << 8) * BQ27XXX_CURRENT_CONSTANT / BQ27XXX_RS;
	else
		dcap *= 1000;

	return dcap;
}