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
struct regulator_dev {TYPE_1__* supply; } ;
struct TYPE_2__ {struct regulator_dev* rdev; } ;

/* Variables and functions */

__attribute__((used)) static inline struct regulator_dev *rdev_get_supply(struct regulator_dev *rdev)
{
	if (rdev && rdev->supply)
		return rdev->supply->rdev;

	return NULL;
}