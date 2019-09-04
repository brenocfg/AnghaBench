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
struct da9062_regulator_info {int n_current_limits; int* current_limits; } ;
struct da9062_regulator {int /*<<< orphan*/  ilimit; struct da9062_regulator_info* info; } ;

/* Variables and functions */
 int EINVAL ; 
 struct da9062_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int da9062_set_current_limit(struct regulator_dev *rdev,
				    int min_ua, int max_ua)
{
	struct da9062_regulator *regl = rdev_get_drvdata(rdev);
	const struct da9062_regulator_info *rinfo = regl->info;
	int n, tval;

	for (n = 0; n < rinfo->n_current_limits; n++) {
		tval = rinfo->current_limits[n];
		if (tval >= min_ua && tval <= max_ua)
			return regmap_field_write(regl->ilimit, n);
	}

	return -EINVAL;
}