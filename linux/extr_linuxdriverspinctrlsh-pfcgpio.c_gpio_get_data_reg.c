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
struct sh_pfc_gpio_pin {size_t dreg; unsigned int dbit; } ;
struct sh_pfc_gpio_data_reg {int dummy; } ;
struct sh_pfc_chip {struct sh_pfc_gpio_data_reg* regs; struct sh_pfc_gpio_pin* pins; int /*<<< orphan*/  pfc; } ;

/* Variables and functions */
 int sh_pfc_get_pin_index (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void gpio_get_data_reg(struct sh_pfc_chip *chip, unsigned int offset,
			      struct sh_pfc_gpio_data_reg **reg,
			      unsigned int *bit)
{
	int idx = sh_pfc_get_pin_index(chip->pfc, offset);
	struct sh_pfc_gpio_pin *gpio_pin = &chip->pins[idx];

	*reg = &chip->regs[gpio_pin->dreg];
	*bit = gpio_pin->dbit;
}