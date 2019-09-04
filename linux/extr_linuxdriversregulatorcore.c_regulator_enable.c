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
struct regulator_dev {struct regulator* supply; int /*<<< orphan*/  mutex; } ;
struct regulator {scalar_t__ always_on; struct regulator_dev* rdev; } ;

/* Variables and functions */
 int _regulator_enable (struct regulator_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (struct regulator*) ; 

int regulator_enable(struct regulator *regulator)
{
	struct regulator_dev *rdev = regulator->rdev;
	int ret = 0;

	if (regulator->always_on)
		return 0;

	if (rdev->supply) {
		ret = regulator_enable(rdev->supply);
		if (ret != 0)
			return ret;
	}

	mutex_lock(&rdev->mutex);
	ret = _regulator_enable(rdev);
	mutex_unlock(&rdev->mutex);

	if (ret != 0 && rdev->supply)
		regulator_disable(rdev->supply);

	return ret;
}