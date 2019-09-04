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
struct regulator_dev {int dummy; } ;
struct max8952_data {unsigned int vid0; unsigned int vid1; TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio_vid1; int /*<<< orphan*/  gpio_vid0; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,unsigned int) ; 
 struct max8952_data* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int max8952_set_voltage_sel(struct regulator_dev *rdev,
				   unsigned selector)
{
	struct max8952_data *max8952 = rdev_get_drvdata(rdev);

	if (!gpio_is_valid(max8952->pdata->gpio_vid0) ||
			!gpio_is_valid(max8952->pdata->gpio_vid1)) {
		/* DVS not supported */
		return -EPERM;
	}

	max8952->vid0 = selector & 0x1;
	max8952->vid1 = (selector >> 1) & 0x1;
	gpio_set_value(max8952->pdata->gpio_vid0, max8952->vid0);
	gpio_set_value(max8952->pdata->gpio_vid1, max8952->vid1);

	return 0;
}