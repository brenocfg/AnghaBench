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
 int EINVAL ; 
#define  REGULATOR_MODE_FAST 129 
#define  REGULATOR_MODE_NORMAL 128 
 int /*<<< orphan*/  VSEL_MODE ; 
 struct fan53555_device_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fan53555_set_mode(struct regulator_dev *rdev, unsigned int mode)
{
	struct fan53555_device_info *di = rdev_get_drvdata(rdev);

	switch (mode) {
	case REGULATOR_MODE_FAST:
		regmap_update_bits(di->regmap, di->vol_reg,
				VSEL_MODE, VSEL_MODE);
		break;
	case REGULATOR_MODE_NORMAL:
		regmap_update_bits(di->regmap, di->vol_reg, VSEL_MODE, 0);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}