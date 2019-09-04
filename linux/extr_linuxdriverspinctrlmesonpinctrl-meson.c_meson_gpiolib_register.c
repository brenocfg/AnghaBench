#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int base; int can_sleep; int of_gpio_n_cells; int /*<<< orphan*/  of_node; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  parent; int /*<<< orphan*/  label; } ;
struct meson_pinctrl {TYPE_1__* data; int /*<<< orphan*/  dev; TYPE_2__ chip; int /*<<< orphan*/  of_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  num_pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int gpiochip_add_data (TYPE_2__*,struct meson_pinctrl*) ; 
 int /*<<< orphan*/  gpiochip_generic_free ; 
 int /*<<< orphan*/  gpiochip_generic_request ; 
 int /*<<< orphan*/  meson_gpio_direction_input ; 
 int /*<<< orphan*/  meson_gpio_direction_output ; 
 int /*<<< orphan*/  meson_gpio_get ; 
 int /*<<< orphan*/  meson_gpio_set ; 

__attribute__((used)) static int meson_gpiolib_register(struct meson_pinctrl *pc)
{
	int ret;

	pc->chip.label = pc->data->name;
	pc->chip.parent = pc->dev;
	pc->chip.request = gpiochip_generic_request;
	pc->chip.free = gpiochip_generic_free;
	pc->chip.direction_input = meson_gpio_direction_input;
	pc->chip.direction_output = meson_gpio_direction_output;
	pc->chip.get = meson_gpio_get;
	pc->chip.set = meson_gpio_set;
	pc->chip.base = -1;
	pc->chip.ngpio = pc->data->num_pins;
	pc->chip.can_sleep = false;
	pc->chip.of_node = pc->of_node;
	pc->chip.of_gpio_n_cells = 2;

	ret = gpiochip_add_data(&pc->chip, pc);
	if (ret) {
		dev_err(pc->dev, "can't add gpio chip %s\n",
			pc->data->name);
		return ret;
	}

	return 0;
}