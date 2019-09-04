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
struct stm32_gpio_bank {int /*<<< orphan*/  gpio_chip; } ;
struct irq_data {int /*<<< orphan*/  hwirq; TYPE_1__* domain; } ;
struct TYPE_2__ {struct stm32_gpio_bank* host_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_unlock_as_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_gpio_irq_release_resources(struct irq_data *irq_data)
{
	struct stm32_gpio_bank *bank = irq_data->domain->host_data;

	gpiochip_unlock_as_irq(&bank->gpio_chip, irq_data->hwirq);
}