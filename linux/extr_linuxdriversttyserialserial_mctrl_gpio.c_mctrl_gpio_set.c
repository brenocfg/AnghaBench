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
struct mctrl_gpios {struct gpio_desc** gpio; } ;
struct gpio_desc {int dummy; } ;
typedef  enum mctrl_gpio_idx { ____Placeholder_mctrl_gpio_idx } mctrl_gpio_idx ;
struct TYPE_2__ {unsigned int mctrl; scalar_t__ dir_out; } ;

/* Variables and functions */
 int UART_GPIO_MAX ; 
 int /*<<< orphan*/  gpiod_set_array_value (unsigned int,struct gpio_desc**,int*) ; 
 TYPE_1__* mctrl_gpios_desc ; 

void mctrl_gpio_set(struct mctrl_gpios *gpios, unsigned int mctrl)
{
	enum mctrl_gpio_idx i;
	struct gpio_desc *desc_array[UART_GPIO_MAX];
	int value_array[UART_GPIO_MAX];
	unsigned int count = 0;

	if (gpios == NULL)
		return;

	for (i = 0; i < UART_GPIO_MAX; i++)
		if (gpios->gpio[i] && mctrl_gpios_desc[i].dir_out) {
			desc_array[count] = gpios->gpio[i];
			value_array[count] = !!(mctrl & mctrl_gpios_desc[i].mctrl);
			count++;
		}
	gpiod_set_array_value(count, desc_array, value_array);
}