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
struct regulator_dev {TYPE_1__* desc; } ;
struct regulator {struct regulator_dev* rdev; } ;
struct TYPE_2__ {unsigned int uV_step; } ;

/* Variables and functions */

unsigned int regulator_get_linear_step(struct regulator *regulator)
{
	struct regulator_dev *rdev = regulator->rdev;

	return rdev->desc->uV_step;
}