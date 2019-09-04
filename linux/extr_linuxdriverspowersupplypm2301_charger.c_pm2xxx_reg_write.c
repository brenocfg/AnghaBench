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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  pm2xxx_i2c; } ;
struct pm2xxx_charger {int /*<<< orphan*/  dev; TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int i2c_smbus_write_i2c_block_data (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm2xxx_reg_write(struct pm2xxx_charger *pm2, int reg, u8 val)
{
	int ret;

	/* wake up the device */
	pm_runtime_get_sync(pm2->dev);

	ret = i2c_smbus_write_i2c_block_data(pm2->config.pm2xxx_i2c, reg,
				1, &val);
	if (ret < 0)
		dev_err(pm2->dev, "Error writing register at 0x%x\n", reg);
	else
		ret = 0;

	pm_runtime_put_sync(pm2->dev);

	return ret;
}