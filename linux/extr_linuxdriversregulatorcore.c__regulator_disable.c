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
struct regulator_dev {int use_count; TYPE_1__* constraints; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  always_on; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int NOTIFY_STOP_MASK ; 
 int /*<<< orphan*/  REGULATOR_CHANGE_DRMS ; 
 int /*<<< orphan*/  REGULATOR_CHANGE_STATUS ; 
 int /*<<< orphan*/  REGULATOR_EVENT_ABORT_DISABLE ; 
 int /*<<< orphan*/  REGULATOR_EVENT_DISABLE ; 
 int /*<<< orphan*/  REGULATOR_EVENT_PRE_DISABLE ; 
 scalar_t__ WARN (int,char*,int /*<<< orphan*/ ) ; 
 int _notifier_call_chain (struct regulator_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _regulator_do_disable (struct regulator_dev*) ; 
 int /*<<< orphan*/  drms_uA_update (struct regulator_dev*) ; 
 int /*<<< orphan*/  lockdep_assert_held_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdev_err (struct regulator_dev*,char*) ; 
 int /*<<< orphan*/  rdev_get_name (struct regulator_dev*) ; 
 scalar_t__ regulator_ops_is_valid (struct regulator_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _regulator_disable(struct regulator_dev *rdev)
{
	int ret = 0;

	lockdep_assert_held_once(&rdev->mutex);

	if (WARN(rdev->use_count <= 0,
		 "unbalanced disables for %s\n", rdev_get_name(rdev)))
		return -EIO;

	/* are we the last user and permitted to disable ? */
	if (rdev->use_count == 1 &&
	    (rdev->constraints && !rdev->constraints->always_on)) {

		/* we are last user */
		if (regulator_ops_is_valid(rdev, REGULATOR_CHANGE_STATUS)) {
			ret = _notifier_call_chain(rdev,
						   REGULATOR_EVENT_PRE_DISABLE,
						   NULL);
			if (ret & NOTIFY_STOP_MASK)
				return -EINVAL;

			ret = _regulator_do_disable(rdev);
			if (ret < 0) {
				rdev_err(rdev, "failed to disable\n");
				_notifier_call_chain(rdev,
						REGULATOR_EVENT_ABORT_DISABLE,
						NULL);
				return ret;
			}
			_notifier_call_chain(rdev, REGULATOR_EVENT_DISABLE,
					NULL);
		}

		rdev->use_count = 0;
	} else if (rdev->use_count > 1) {
		if (regulator_ops_is_valid(rdev, REGULATOR_CHANGE_DRMS))
			drms_uA_update(rdev);

		rdev->use_count--;
	}

	return ret;
}