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
struct st_pio_control {int dummy; } ;
struct st_gpio_bank {struct st_pio_control pc; } ;
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 struct st_gpio_bank* gpio_range_to_bank (struct pinctrl_gpio_range*) ; 
 struct pinctrl_gpio_range* pinctrl_find_gpio_range_from_pin (struct pinctrl_dev*,int) ; 

__attribute__((used)) static struct st_pio_control *st_get_pio_control(
			struct pinctrl_dev *pctldev, int pin)
{
	struct pinctrl_gpio_range *range =
			 pinctrl_find_gpio_range_from_pin(pctldev, pin);
	struct st_gpio_bank *bank = gpio_range_to_bank(range);

	return &bank->pc;
}