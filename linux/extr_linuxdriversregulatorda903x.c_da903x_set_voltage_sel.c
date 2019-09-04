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
typedef  int uint8_t ;
struct regulator_dev {TYPE_1__* desc; } ;
struct device {int dummy; } ;
struct da903x_regulator_info {unsigned int vol_shift; int vol_nbits; int /*<<< orphan*/  vol_reg; } ;
struct TYPE_2__ {int n_voltages; } ;

/* Variables and functions */
 int EINVAL ; 
 int da903x_update (struct device*,int /*<<< orphan*/ ,int,int) ; 
 struct da903x_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 
 struct device* to_da903x_dev (struct regulator_dev*) ; 

__attribute__((used)) static int da903x_set_voltage_sel(struct regulator_dev *rdev, unsigned selector)
{
	struct da903x_regulator_info *info = rdev_get_drvdata(rdev);
	struct device *da9034_dev = to_da903x_dev(rdev);
	uint8_t val, mask;

	if (rdev->desc->n_voltages == 1)
		return -EINVAL;

	val = selector << info->vol_shift;
	mask = ((1 << info->vol_nbits) - 1)  << info->vol_shift;

	return da903x_update(da9034_dev, info->vol_reg, val, mask);
}