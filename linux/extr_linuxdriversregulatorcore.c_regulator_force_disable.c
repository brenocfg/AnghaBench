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
struct regulator_dev {scalar_t__ supply; int /*<<< orphan*/  open_count; int /*<<< orphan*/  mutex; } ;
struct regulator {struct regulator_dev* rdev; scalar_t__ uA_load; } ;

/* Variables and functions */
 int _regulator_force_disable (struct regulator_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 

int regulator_force_disable(struct regulator *regulator)
{
	struct regulator_dev *rdev = regulator->rdev;
	int ret;

	mutex_lock(&rdev->mutex);
	regulator->uA_load = 0;
	ret = _regulator_force_disable(regulator->rdev);
	mutex_unlock(&rdev->mutex);

	if (rdev->supply)
		while (rdev->open_count--)
			regulator_disable(rdev->supply);

	return ret;
}