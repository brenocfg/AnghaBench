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
struct tps65218 {int /*<<< orphan*/  regmap; } ;
struct regulator_dev {TYPE_1__* desc; } ;
struct TYPE_2__ {unsigned int csel_mask; int /*<<< orphan*/  csel_reg; } ;

/* Variables and functions */
 int* ls3_currents ; 
 struct tps65218* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int tps65218_pmic_get_current_limit(struct regulator_dev *dev)
{
	int retval;
	unsigned int index;
	struct tps65218 *tps = rdev_get_drvdata(dev);

	retval = regmap_read(tps->regmap, dev->desc->csel_reg, &index);
	if (retval < 0)
		return retval;

	index = (index & dev->desc->csel_mask) >> 2;

	return ls3_currents[index];
}