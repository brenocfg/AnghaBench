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
struct TYPE_2__ {struct ak4641_platform_data* platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct ak4641_platform_data {int /*<<< orphan*/  gpio_npdn; int /*<<< orphan*/  gpio_power; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ak4641_i2c_remove(struct i2c_client *i2c)
{
	struct ak4641_platform_data *pdata = i2c->dev.platform_data;

	if (pdata) {
		if (gpio_is_valid(pdata->gpio_power)) {
			gpio_set_value(pdata->gpio_power, 0);
			gpio_free(pdata->gpio_power);
		}
		if (gpio_is_valid(pdata->gpio_npdn))
			gpio_free(pdata->gpio_npdn);
	}

	return 0;
}