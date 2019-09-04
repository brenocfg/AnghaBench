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
typedef  int u8 ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 size_t DS2404_CLK ; 
 size_t DS2404_DQ ; 
 TYPE_1__* ds2404_gpio ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u8 ds2404_read_byte(struct device *dev)
{
	int i;
	u8 ret = 0;

	gpio_direction_input(ds2404_gpio[DS2404_DQ].gpio);

	for (i = 0; i < 8; i++) {
		gpio_set_value(ds2404_gpio[DS2404_CLK].gpio, 0);
		udelay(10);
		if (gpio_get_value(ds2404_gpio[DS2404_DQ].gpio))
			ret |= 1 << i;
		gpio_set_value(ds2404_gpio[DS2404_CLK].gpio, 1);
		udelay(10);
	}
	return ret;
}