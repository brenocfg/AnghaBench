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
struct regulator_ops {int (* set_current_limit ) (struct regulator_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  get_current_limit; } ;
struct regulator_dev {TYPE_1__* desc; } ;
struct regulation_constraints {int /*<<< orphan*/  max_uA; int /*<<< orphan*/  min_uA; } ;
struct TYPE_2__ {struct regulator_ops* ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  rdev_err (struct regulator_dev*,char*,...) ; 
 int /*<<< orphan*/  rdev_warn (struct regulator_dev*,char*) ; 
 int stub1 (struct regulator_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int machine_constraints_current(struct regulator_dev *rdev,
	struct regulation_constraints *constraints)
{
	const struct regulator_ops *ops = rdev->desc->ops;
	int ret;

	if (!constraints->min_uA && !constraints->max_uA)
		return 0;

	if (constraints->min_uA > constraints->max_uA) {
		rdev_err(rdev, "Invalid current constraints\n");
		return -EINVAL;
	}

	if (!ops->set_current_limit || !ops->get_current_limit) {
		rdev_warn(rdev, "Operation of current configuration missing\n");
		return 0;
	}

	/* Set regulator current in constraints range */
	ret = ops->set_current_limit(rdev, constraints->min_uA,
			constraints->max_uA);
	if (ret < 0) {
		rdev_err(rdev, "Failed to set current constraint, %d\n", ret);
		return ret;
	}

	return 0;
}