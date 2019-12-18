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
struct irq_data {struct irq_chip* chip; } ;
struct irq_desc {struct irq_data irq_data; } ;
struct irq_chip {int /*<<< orphan*/  (* irq_release_resources ) (struct irq_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct irq_data*) ; 

__attribute__((used)) static void irq_release_resources(struct irq_desc *desc)
{
	struct irq_data *d = &desc->irq_data;
	struct irq_chip *c = d->chip;

	if (c->irq_release_resources)
		c->irq_release_resources(d);
}