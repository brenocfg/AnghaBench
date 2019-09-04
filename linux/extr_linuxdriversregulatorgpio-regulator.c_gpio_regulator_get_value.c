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
struct gpio_regulator_data {int nr_states; scalar_t__ state; TYPE_1__* states; } ;
struct TYPE_2__ {scalar_t__ gpios; int value; } ;

/* Variables and functions */
 int EINVAL ; 
 struct gpio_regulator_data* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int gpio_regulator_get_value(struct regulator_dev *dev)
{
	struct gpio_regulator_data *data = rdev_get_drvdata(dev);
	int ptr;

	for (ptr = 0; ptr < data->nr_states; ptr++)
		if (data->states[ptr].gpios == data->state)
			return data->states[ptr].value;

	return -EINVAL;
}