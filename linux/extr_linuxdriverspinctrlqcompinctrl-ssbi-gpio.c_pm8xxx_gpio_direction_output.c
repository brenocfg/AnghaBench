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
typedef  int u8 ;
struct pm8xxx_pin_data {int mode; int output_value; int open_drain; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct pm8xxx_gpio {TYPE_2__ desc; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_3__ {struct pm8xxx_pin_data* drv_data; } ;

/* Variables and functions */
 int PM8XXX_GPIO_MODE_OUTPUT ; 
 struct pm8xxx_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pm8xxx_write_bank (struct pm8xxx_gpio*,struct pm8xxx_pin_data*,int,int) ; 

__attribute__((used)) static int pm8xxx_gpio_direction_output(struct gpio_chip *chip,
					unsigned offset,
					int value)
{
	struct pm8xxx_gpio *pctrl = gpiochip_get_data(chip);
	struct pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;
	u8 val;

	pin->mode = PM8XXX_GPIO_MODE_OUTPUT;
	pin->output_value = !!value;

	val = pin->mode << 2;
	val |= pin->open_drain << 1;
	val |= pin->output_value;

	pm8xxx_write_bank(pctrl, pin, 1, val);

	return 0;
}