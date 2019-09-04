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
struct ssb_bus {int /*<<< orphan*/  chipco; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct ssb_bus* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  ssb_chipco_gpio_in (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ssb_gpio_chipco_get_value(struct gpio_chip *chip, unsigned int gpio)
{
	struct ssb_bus *bus = gpiochip_get_data(chip);

	return !!ssb_chipco_gpio_in(&bus->chipco, 1 << gpio);
}