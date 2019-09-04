#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ili922x {int power; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 scalar_t__ POWER_IS_ON (int) ; 
 int ili922x_poweroff (int /*<<< orphan*/ ) ; 
 int ili922x_poweron (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ili922x_lcd_power(struct ili922x *lcd, int power)
{
	int ret = 0;

	if (POWER_IS_ON(power) && !POWER_IS_ON(lcd->power))
		ret = ili922x_poweron(lcd->spi);
	else if (!POWER_IS_ON(power) && POWER_IS_ON(lcd->power))
		ret = ili922x_poweroff(lcd->spi);

	if (!ret)
		lcd->power = power;

	return ret;
}