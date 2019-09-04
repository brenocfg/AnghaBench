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
struct ld9040 {int power; } ;

/* Variables and functions */
 scalar_t__ ld9040_power_is_on (int) ; 
 int ld9040_power_off (struct ld9040*) ; 
 int ld9040_power_on (struct ld9040*) ; 

__attribute__((used)) static int ld9040_power(struct ld9040 *lcd, int power)
{
	int ret = 0;

	if (ld9040_power_is_on(power) && !ld9040_power_is_on(lcd->power))
		ret = ld9040_power_on(lcd);
	else if (!ld9040_power_is_on(power) && ld9040_power_is_on(lcd->power))
		ret = ld9040_power_off(lcd);

	if (!ret)
		lcd->power = power;

	return ret;
}