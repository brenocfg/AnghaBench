#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {scalar_t__ bypass_count; scalar_t__ open_count; TYPE_2__* desc; } ;
struct regulator {int bypass; struct regulator_dev* rdev; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* set_bypass ) (struct regulator_dev*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  REGULATOR_CHANGE_BYPASS ; 
 int /*<<< orphan*/  regulator_lock (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_ops_is_valid (struct regulator_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_unlock (struct regulator_dev*) ; 
 int stub1 (struct regulator_dev*,int) ; 
 int stub2 (struct regulator_dev*,int) ; 

int regulator_allow_bypass(struct regulator *regulator, bool enable)
{
	struct regulator_dev *rdev = regulator->rdev;
	int ret = 0;

	if (!rdev->desc->ops->set_bypass)
		return 0;

	if (!regulator_ops_is_valid(rdev, REGULATOR_CHANGE_BYPASS))
		return 0;

	regulator_lock(rdev);

	if (enable && !regulator->bypass) {
		rdev->bypass_count++;

		if (rdev->bypass_count == rdev->open_count) {
			ret = rdev->desc->ops->set_bypass(rdev, enable);
			if (ret != 0)
				rdev->bypass_count--;
		}

	} else if (!enable && regulator->bypass) {
		rdev->bypass_count--;

		if (rdev->bypass_count != rdev->open_count) {
			ret = rdev->desc->ops->set_bypass(rdev, enable);
			if (ret != 0)
				rdev->bypass_count++;
		}
	}

	if (ret == 0)
		regulator->bypass = enable;

	regulator_unlock(rdev);

	return ret;
}