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
typedef  int /*<<< orphan*/  u8 ;
struct gpio_chip {int dummy; } ;
struct gb_gpio_controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_gpio_deactivate_operation (struct gb_gpio_controller*,int /*<<< orphan*/ ) ; 
 struct gb_gpio_controller* gpio_chip_to_gb_gpio_controller (struct gpio_chip*) ; 

__attribute__((used)) static void gb_gpio_free(struct gpio_chip *chip, unsigned int offset)
{
	struct gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);

	gb_gpio_deactivate_operation(ggc, (u8)offset);
}