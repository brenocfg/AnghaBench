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
struct irq_domain_data {int /*<<< orphan*/  irq_lock; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct irq_domain_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lan78xx_irq_bus_lock(struct irq_data *irqd)
{
	struct irq_domain_data *data = irq_data_get_irq_chip_data(irqd);

	mutex_lock(&data->irq_lock);
}