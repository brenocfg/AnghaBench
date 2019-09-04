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
struct regulator_dev {TYPE_2__* desc; TYPE_1__* constraints; } ;
struct TYPE_4__ {char const* name; } ;
struct TYPE_3__ {char const* name; } ;

/* Variables and functions */

__attribute__((used)) static const char *rdev_get_name(struct regulator_dev *rdev)
{
	if (rdev->constraints && rdev->constraints->name)
		return rdev->constraints->name;
	else if (rdev->desc->name)
		return rdev->desc->name;
	else
		return "";
}