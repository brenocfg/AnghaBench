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
struct pm8xxx_pin_data {int irq; } ;
struct TYPE_4__ {TYPE_1__* pins; } ;
struct pm8xxx_mpp {TYPE_2__ desc; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_3__ {struct pm8xxx_pin_data* drv_data; } ;

/* Variables and functions */
 struct pm8xxx_mpp* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int pm8xxx_mpp_to_irq(struct gpio_chip *chip, unsigned offset)
{
	struct pm8xxx_mpp *pctrl = gpiochip_get_data(chip);
	struct pm8xxx_pin_data *pin = pctrl->desc.pins[offset].drv_data;

	return pin->irq;
}