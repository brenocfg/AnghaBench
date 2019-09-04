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
struct TYPE_4__ {int /*<<< orphan*/  sense; int /*<<< orphan*/  masked; } ;
struct sx150x_pinctrl {int /*<<< orphan*/  lock; TYPE_2__ irq; TYPE_1__* data; int /*<<< orphan*/  regmap; } ;
struct irq_data {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg_sense; int /*<<< orphan*/  reg_irq_mask; } ;

/* Variables and functions */
 struct sx150x_pinctrl* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sx150x_irq_bus_sync_unlock(struct irq_data *d)
{
	struct sx150x_pinctrl *pctl =
			gpiochip_get_data(irq_data_get_irq_chip_data(d));

	regmap_write(pctl->regmap, pctl->data->reg_irq_mask, pctl->irq.masked);
	regmap_write(pctl->regmap, pctl->data->reg_sense, pctl->irq.sense);
	mutex_unlock(&pctl->lock);
}