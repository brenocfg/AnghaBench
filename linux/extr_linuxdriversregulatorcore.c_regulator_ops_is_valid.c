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
struct TYPE_2__ {int valid_ops_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  rdev_err (struct regulator_dev*,char*) ; 

__attribute__((used)) static bool regulator_ops_is_valid(struct regulator_dev *rdev, int ops)
{
	if (!rdev->constraints) {
		rdev_err(rdev, "no constraints\n");
		return false;
	}

	if (rdev->constraints->valid_ops_mask & ops)
		return true;

	return false;
}