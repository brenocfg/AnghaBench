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
struct s6e63m0 {int power; } ;

/* Variables and functions */
 scalar_t__ s6e63m0_power_is_on (int) ; 
 int s6e63m0_power_off (struct s6e63m0*) ; 
 int s6e63m0_power_on (struct s6e63m0*) ; 

__attribute__((used)) static int s6e63m0_power(struct s6e63m0 *lcd, int power)
{
	int ret = 0;

	if (s6e63m0_power_is_on(power) && !s6e63m0_power_is_on(lcd->power))
		ret = s6e63m0_power_on(lcd);
	else if (!s6e63m0_power_is_on(power) && s6e63m0_power_is_on(lcd->power))
		ret = s6e63m0_power_off(lcd);

	if (!ret)
		lcd->power = power;

	return ret;
}