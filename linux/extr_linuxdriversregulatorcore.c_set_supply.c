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
struct regulator_dev {int /*<<< orphan*/  open_count; int /*<<< orphan*/ * supply; int /*<<< orphan*/  dev; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * create_regulator (struct regulator_dev*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rdev_get_name (struct regulator_dev*) ; 
 int /*<<< orphan*/  rdev_info (struct regulator_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_supply(struct regulator_dev *rdev,
		      struct regulator_dev *supply_rdev)
{
	int err;

	rdev_info(rdev, "supplied by %s\n", rdev_get_name(supply_rdev));

	if (!try_module_get(supply_rdev->owner))
		return -ENODEV;

	rdev->supply = create_regulator(supply_rdev, &rdev->dev, "SUPPLY");
	if (rdev->supply == NULL) {
		err = -ENOMEM;
		return err;
	}
	supply_rdev->open_count++;

	return 0;
}