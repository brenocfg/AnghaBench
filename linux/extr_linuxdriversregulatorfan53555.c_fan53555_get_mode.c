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
struct regulator_dev {int dummy; } ;
struct fan53555_device_info {int /*<<< orphan*/  vol_reg; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int REGULATOR_MODE_FAST ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 unsigned int VSEL_MODE ; 
 struct fan53555_device_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned int fan53555_get_mode(struct regulator_dev *rdev)
{
	struct fan53555_device_info *di = rdev_get_drvdata(rdev);
	unsigned int val;
	int ret = 0;

	ret = regmap_read(di->regmap, di->vol_reg, &val);
	if (ret < 0)
		return ret;
	if (val & VSEL_MODE)
		return REGULATOR_MODE_FAST;
	else
		return REGULATOR_MODE_NORMAL;
}