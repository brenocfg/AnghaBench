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
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 size_t DS2404_CLK ; 
 size_t DS2404_DQ ; 
 size_t DS2404_RST ; 
 TYPE_1__* ds2404_gpio ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ds2404_reset(struct device *dev)
{
	gpio_set_value(ds2404_gpio[DS2404_RST].gpio, 0);
	udelay(1000);
	gpio_set_value(ds2404_gpio[DS2404_RST].gpio, 1);
	gpio_set_value(ds2404_gpio[DS2404_CLK].gpio, 0);
	gpio_direction_output(ds2404_gpio[DS2404_DQ].gpio, 0);
	udelay(10);
}