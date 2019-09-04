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
struct TYPE_2__ {unsigned int n_voltages; int min_uV; unsigned int uV_step; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int arizona_ldo1_hc_list_voltage(struct regulator_dev *rdev,
					unsigned int selector)
{
	if (selector >= rdev->desc->n_voltages)
		return -EINVAL;

	if (selector == rdev->desc->n_voltages - 1)
		return 1800000;
	else
		return rdev->desc->min_uV + (rdev->desc->uV_step * selector);
}