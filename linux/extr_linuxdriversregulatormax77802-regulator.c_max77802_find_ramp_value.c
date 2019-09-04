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
struct regulator_dev {TYPE_1__* desc; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int max77802_find_ramp_value(struct regulator_dev *rdev,
				    const unsigned int limits[], int size,
				    unsigned int ramp_delay)
{
	int i;

	for (i = 0; i < size; i++) {
		if (ramp_delay <= limits[i])
			return i;
	}

	/* Use maximum value for no ramp control */
	dev_warn(&rdev->dev, "%s: ramp_delay: %d not supported, setting 100000\n",
		 rdev->desc->name, ramp_delay);
	return size - 1;
}