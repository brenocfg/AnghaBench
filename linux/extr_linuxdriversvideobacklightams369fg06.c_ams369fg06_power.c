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
struct ams369fg06 {int power; } ;

/* Variables and functions */
 scalar_t__ ams369fg06_power_is_on (int) ; 
 int ams369fg06_power_off (struct ams369fg06*) ; 
 int ams369fg06_power_on (struct ams369fg06*) ; 

__attribute__((used)) static int ams369fg06_power(struct ams369fg06 *lcd, int power)
{
	int ret = 0;

	if (ams369fg06_power_is_on(power) &&
		!ams369fg06_power_is_on(lcd->power))
		ret = ams369fg06_power_on(lcd);
	else if (!ams369fg06_power_is_on(power) &&
		ams369fg06_power_is_on(lcd->power))
		ret = ams369fg06_power_off(lcd);

	if (!ret)
		lcd->power = power;

	return ret;
}