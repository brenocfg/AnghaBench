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
struct rt5677_priv {int /*<<< orphan*/  irq_en; } ;
struct irq_data {size_t hwirq; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_mask; } ;

/* Variables and functions */
 struct rt5677_priv* irq_data_get_irq_chip_data (struct irq_data*) ; 
 TYPE_1__* rt5677_irq_descs ; 

__attribute__((used)) static void rt5677_irq_disable(struct irq_data *data)
{
	struct rt5677_priv *rt5677 = irq_data_get_irq_chip_data(data);

	rt5677->irq_en &= ~rt5677_irq_descs[data->hwirq].enable_mask;
}