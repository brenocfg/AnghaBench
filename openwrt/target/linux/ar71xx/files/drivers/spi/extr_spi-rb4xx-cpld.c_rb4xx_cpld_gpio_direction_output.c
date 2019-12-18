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
struct rb4xx_cpld {int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int __rb4xx_cpld_change_cfg (struct rb4xx_cpld*,int,int) ; 
 struct rb4xx_cpld* gpio_to_cpld (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rb4xx_cpld_gpio_direction_output(struct gpio_chip *chip,
					    unsigned offset,
					    int value)
{
	struct rb4xx_cpld *cpld = gpio_to_cpld(chip);
	int ret;

	mutex_lock(&cpld->lock);
	ret = __rb4xx_cpld_change_cfg(cpld, (1 << offset), !!value << offset);
	mutex_unlock(&cpld->lock);

	return ret;
}