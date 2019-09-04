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
struct da9062_regulator_info {unsigned int n_current_limits; int* current_limits; } ;
struct da9062_regulator {int /*<<< orphan*/  ilimit; struct da9062_regulator_info* info; } ;

/* Variables and functions */
 struct da9062_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_field_read (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int da9062_get_current_limit(struct regulator_dev *rdev)
{
	struct da9062_regulator *regl = rdev_get_drvdata(rdev);
	const struct da9062_regulator_info *rinfo = regl->info;
	unsigned int sel;
	int ret;

	ret = regmap_field_read(regl->ilimit, &sel);
	if (ret < 0)
		return ret;

	if (sel >= rinfo->n_current_limits)
		sel = rinfo->n_current_limits - 1;

	return rinfo->current_limits[sel];
}