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
struct rt5677_priv {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  irq_en; int /*<<< orphan*/  regmap; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int RT5677_EN_IRQ_GPIO_JD1 ; 
 int RT5677_EN_IRQ_GPIO_JD2 ; 
 int RT5677_EN_IRQ_GPIO_JD3 ; 
 int /*<<< orphan*/  RT5677_IRQ_CTRL1 ; 
 struct rt5677_priv* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt5677_irq_bus_sync_unlock(struct irq_data *data)
{
	struct rt5677_priv *rt5677 = irq_data_get_irq_chip_data(data);

	// Set the enable/disable bits for the jack detect IRQs.
	regmap_update_bits(rt5677->regmap, RT5677_IRQ_CTRL1,
			RT5677_EN_IRQ_GPIO_JD1 | RT5677_EN_IRQ_GPIO_JD2 |
			RT5677_EN_IRQ_GPIO_JD3, rt5677->irq_en);
	mutex_unlock(&rt5677->irq_lock);
}