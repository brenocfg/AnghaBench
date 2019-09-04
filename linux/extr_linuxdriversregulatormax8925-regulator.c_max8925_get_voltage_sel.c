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
struct regulator_dev {TYPE_1__* desc; } ;
struct max8925_regulator_info {int /*<<< orphan*/  vol_reg; int /*<<< orphan*/  i2c; } ;
struct TYPE_2__ {int n_voltages; } ;

/* Variables and functions */
 int max8925_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct max8925_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int max8925_get_voltage_sel(struct regulator_dev *rdev)
{
	struct max8925_regulator_info *info = rdev_get_drvdata(rdev);
	unsigned char data, mask;
	int ret;

	ret = max8925_reg_read(info->i2c, info->vol_reg);
	if (ret < 0)
		return ret;
	mask = rdev->desc->n_voltages - 1;
	data = ret & mask;

	return data;
}