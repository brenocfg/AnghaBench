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
struct pm8607_regulator_info {int* vol_table; scalar_t__ slope_double; } ;
struct TYPE_2__ {unsigned int n_voltages; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pm8607_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int pm8607_list_voltage(struct regulator_dev *rdev, unsigned index)
{
	struct pm8607_regulator_info *info = rdev_get_drvdata(rdev);
	int ret = -EINVAL;

	if (info->vol_table && (index < rdev->desc->n_voltages)) {
		ret = info->vol_table[index];
		if (info->slope_double)
			ret <<= 1;
	}
	return ret;
}