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
struct regmap {int dummy; } ;

/* Variables and functions */
 int __uniphier_watchdog_start (struct regmap*,unsigned int) ; 
 int __uniphier_watchdog_stop (struct regmap*) ; 

__attribute__((used)) static int __uniphier_watchdog_restart(struct regmap *regmap, unsigned int sec)
{
	int ret;

	ret = __uniphier_watchdog_stop(regmap);
	if (ret)
		return ret;

	return __uniphier_watchdog_start(regmap, sec);
}