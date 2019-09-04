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
struct regulator_dev {TYPE_1__* constraints; } ;
struct TYPE_2__ {int max_uA; int min_uA; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  REGULATOR_CHANGE_CURRENT ; 
 int /*<<< orphan*/  rdev_err (struct regulator_dev*,char*,...) ; 
 int /*<<< orphan*/  regulator_ops_is_valid (struct regulator_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regulator_check_current_limit(struct regulator_dev *rdev,
					int *min_uA, int *max_uA)
{
	BUG_ON(*min_uA > *max_uA);

	if (!regulator_ops_is_valid(rdev, REGULATOR_CHANGE_CURRENT)) {
		rdev_err(rdev, "current operation not allowed\n");
		return -EPERM;
	}

	if (*max_uA > rdev->constraints->max_uA)
		*max_uA = rdev->constraints->max_uA;
	if (*min_uA < rdev->constraints->min_uA)
		*min_uA = rdev->constraints->min_uA;

	if (*min_uA > *max_uA) {
		rdev_err(rdev, "unsupportable current range: %d-%duA\n",
			 *min_uA, *max_uA);
		return -EINVAL;
	}

	return 0;
}