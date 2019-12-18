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
struct irq_devres {unsigned int member_0; void* member_1; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_irq_match ; 
 int /*<<< orphan*/  devm_irq_release ; 
 int /*<<< orphan*/  devres_destroy (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct irq_devres*) ; 
 int /*<<< orphan*/  free_irq (unsigned int,void*) ; 

void devm_free_irq(struct device *dev, unsigned int irq, void *dev_id)
{
	struct irq_devres match_data = { irq, dev_id };

	WARN_ON(devres_destroy(dev, devm_irq_release, devm_irq_match,
			       &match_data));
	free_irq(irq, dev_id);
}