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
 int gb_gpio_activate_operation (struct gb_gpio_controller*,int /*<<< orphan*/ ) ; 
 struct gb_gpio_controller* gpio_chip_to_gb_gpio_controller (struct gpio_chip*) ; 

__attribute__((used)) static int gb_gpio_request(struct gpio_chip *chip, unsigned int offset)
{
	struct gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);

	return gb_gpio_activate_operation(ggc, (u8)offset);
}