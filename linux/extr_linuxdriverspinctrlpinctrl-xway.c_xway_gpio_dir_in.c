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
struct ltq_pinmux_info {int /*<<< orphan*/ * membase; } ;
struct gpio_chip {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_DIR (unsigned int) ; 
 int /*<<< orphan*/  PORT_PIN (unsigned int) ; 
 struct ltq_pinmux_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_clearbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xway_gpio_dir_in(struct gpio_chip *chip, unsigned int pin)
{
	struct ltq_pinmux_info *info = dev_get_drvdata(chip->parent);

	gpio_clearbit(info->membase[0], GPIO_DIR(pin), PORT_PIN(pin));

	return 0;
}