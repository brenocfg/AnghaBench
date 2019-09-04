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
struct mcp23s08 {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;
struct irq_data {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct mcp23s08* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcp23s08_irq_bus_unlock(struct irq_data *data)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(data);
	struct mcp23s08 *mcp = gpiochip_get_data(gc);

	regcache_cache_only(mcp->regmap, false);
	regcache_sync(mcp->regmap);

	mutex_unlock(&mcp->lock);
}