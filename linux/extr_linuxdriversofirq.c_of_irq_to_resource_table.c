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
struct resource {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ of_irq_to_resource (struct device_node*,int,struct resource*) ; 

int of_irq_to_resource_table(struct device_node *dev, struct resource *res,
		int nr_irqs)
{
	int i;

	for (i = 0; i < nr_irqs; i++, res++)
		if (of_irq_to_resource(dev, i, res) <= 0)
			break;

	return i;
}