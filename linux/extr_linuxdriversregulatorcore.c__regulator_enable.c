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
struct regulator_dev {scalar_t__ use_count; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  REGULATOR_CHANGE_DRMS ; 
 int /*<<< orphan*/  REGULATOR_CHANGE_STATUS ; 
 int /*<<< orphan*/  REGULATOR_EVENT_ENABLE ; 
 int /*<<< orphan*/  _notifier_call_chain (struct regulator_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _regulator_do_enable (struct regulator_dev*) ; 
 int _regulator_is_enabled (struct regulator_dev*) ; 
 int /*<<< orphan*/  drms_uA_update (struct regulator_dev*) ; 
 int /*<<< orphan*/  lockdep_assert_held_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdev_err (struct regulator_dev*,char*,int) ; 
 scalar_t__ regulator_ops_is_valid (struct regulator_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _regulator_enable(struct regulator_dev *rdev)
{
	int ret;

	lockdep_assert_held_once(&rdev->mutex);

	/* check voltage and requested load before enabling */
	if (regulator_ops_is_valid(rdev, REGULATOR_CHANGE_DRMS))
		drms_uA_update(rdev);

	if (rdev->use_count == 0) {
		/* The regulator may on if it's not switchable or left on */
		ret = _regulator_is_enabled(rdev);
		if (ret == -EINVAL || ret == 0) {
			if (!regulator_ops_is_valid(rdev,
					REGULATOR_CHANGE_STATUS))
				return -EPERM;

			ret = _regulator_do_enable(rdev);
			if (ret < 0)
				return ret;

			_notifier_call_chain(rdev, REGULATOR_EVENT_ENABLE,
					     NULL);
		} else if (ret < 0) {
			rdev_err(rdev, "is_enabled() failed: %d\n", ret);
			return ret;
		}
		/* Fallthrough on positive return values - already enabled */
	}

	rdev->use_count++;

	return 0;
}