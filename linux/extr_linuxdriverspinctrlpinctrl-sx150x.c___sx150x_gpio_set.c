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
struct sx150x_pinctrl {TYPE_1__* data; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __sx150x_gpio_set(struct sx150x_pinctrl *pctl, unsigned int offset,
			     int value)
{
	return regmap_write_bits(pctl->regmap, pctl->data->reg_data,
				 BIT(offset), value ? BIT(offset) : 0);
}