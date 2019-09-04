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
struct ltq_pinmux_info {int num_exin; unsigned int* exin; } ;
struct gpio_chip {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct ltq_pinmux_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int ltq_eiu_get_irq (int) ; 

__attribute__((used)) static int xway_gpio_to_irq(struct gpio_chip *chip, unsigned offset)
{
	struct ltq_pinmux_info *info = dev_get_drvdata(chip->parent);
	int i;

	for (i = 0; i < info->num_exin; i++)
		if (info->exin[i] == offset)
			return ltq_eiu_get_irq(i);

	return -1;
}