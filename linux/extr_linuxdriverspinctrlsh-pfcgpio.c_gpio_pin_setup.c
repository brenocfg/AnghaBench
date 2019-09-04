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
struct gpio_chip {int /*<<< orphan*/  ngpio; scalar_t__ base; int /*<<< orphan*/  owner; int /*<<< orphan*/  parent; int /*<<< orphan*/  label; int /*<<< orphan*/  to_irq; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  free; int /*<<< orphan*/  request; } ;
struct sh_pfc_chip {int /*<<< orphan*/ * pins; struct gpio_chip gpio_chip; struct sh_pfc* pfc; } ;
struct sh_pfc {int /*<<< orphan*/  nr_gpio_pins; int /*<<< orphan*/  dev; TYPE_1__* info; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  nr_pins; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/ * devm_kcalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_pin_direction_input ; 
 int /*<<< orphan*/  gpio_pin_direction_output ; 
 int /*<<< orphan*/  gpio_pin_free ; 
 int /*<<< orphan*/  gpio_pin_get ; 
 int /*<<< orphan*/  gpio_pin_request ; 
 int /*<<< orphan*/  gpio_pin_set ; 
 int /*<<< orphan*/  gpio_pin_to_irq ; 
 int gpio_setup_data_regs (struct sh_pfc_chip*) ; 

__attribute__((used)) static int gpio_pin_setup(struct sh_pfc_chip *chip)
{
	struct sh_pfc *pfc = chip->pfc;
	struct gpio_chip *gc = &chip->gpio_chip;
	int ret;

	chip->pins = devm_kcalloc(pfc->dev,
				  pfc->info->nr_pins, sizeof(*chip->pins),
				  GFP_KERNEL);
	if (chip->pins == NULL)
		return -ENOMEM;

	ret = gpio_setup_data_regs(chip);
	if (ret < 0)
		return ret;

	gc->request = gpio_pin_request;
	gc->free = gpio_pin_free;
	gc->direction_input = gpio_pin_direction_input;
	gc->get = gpio_pin_get;
	gc->direction_output = gpio_pin_direction_output;
	gc->set = gpio_pin_set;
	gc->to_irq = gpio_pin_to_irq;

	gc->label = pfc->info->name;
	gc->parent = pfc->dev;
	gc->owner = THIS_MODULE;
	gc->base = 0;
	gc->ngpio = pfc->nr_gpio_pins;

	return 0;
}