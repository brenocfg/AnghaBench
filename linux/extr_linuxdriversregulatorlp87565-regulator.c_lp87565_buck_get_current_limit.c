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
struct regulator_dev {int dummy; } ;
struct lp87565 {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl2_reg; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 unsigned int LP87565_BUCK_CTRL_2_ILIM ; 
 unsigned int __ffs (unsigned int) ; 
 int* lp87565_buck_uA ; 
 struct lp87565* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 TYPE_1__* regulators ; 

__attribute__((used)) static int lp87565_buck_get_current_limit(struct regulator_dev *rdev)
{
	int id = rdev_get_id(rdev);
	struct lp87565 *lp87565 = rdev_get_drvdata(rdev);
	int ret;
	unsigned int val;

	ret = regmap_read(lp87565->regmap, regulators[id].ctrl2_reg, &val);
	if (ret)
		return ret;

	val = (val & LP87565_BUCK_CTRL_2_ILIM) >>
	       __ffs(LP87565_BUCK_CTRL_2_ILIM);

	return (val < ARRAY_SIZE(lp87565_buck_uA)) ?
			lp87565_buck_uA[val] : -EINVAL;
}