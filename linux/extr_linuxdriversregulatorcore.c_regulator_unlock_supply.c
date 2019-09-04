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
struct regulator_dev {struct regulator* supply; } ;
struct regulator {struct regulator_dev* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  regulator_unlock (struct regulator_dev*) ; 

__attribute__((used)) static void regulator_unlock_supply(struct regulator_dev *rdev)
{
	struct regulator *supply;

	while (1) {
		regulator_unlock(rdev);
		supply = rdev->supply;

		if (!rdev->supply)
			return;

		rdev = supply->rdev;
	}
}