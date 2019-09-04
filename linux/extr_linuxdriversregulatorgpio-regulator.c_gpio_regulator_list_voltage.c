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
struct gpio_regulator_data {unsigned int nr_states; TYPE_1__* states; } ;
struct TYPE_2__ {int value; } ;

/* Variables and functions */
 int EINVAL ; 
 struct gpio_regulator_data* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int gpio_regulator_list_voltage(struct regulator_dev *dev,
				      unsigned selector)
{
	struct gpio_regulator_data *data = rdev_get_drvdata(dev);

	if (selector >= data->nr_states)
		return -EINVAL;

	return data->states[selector].value;
}