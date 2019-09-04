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
struct resource {int flags; int start; int end; } ;
struct pnp_resource {struct resource res; } ;
struct pnp_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IORESOURCE_IRQ ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,struct resource*) ; 
 struct pnp_resource* pnp_new_resource (struct pnp_dev*) ; 

struct pnp_resource *pnp_add_irq_resource(struct pnp_dev *dev, int irq,
					  int flags)
{
	struct pnp_resource *pnp_res;
	struct resource *res;

	pnp_res = pnp_new_resource(dev);
	if (!pnp_res) {
		dev_err(&dev->dev, "can't add resource for IRQ %d\n", irq);
		return NULL;
	}

	res = &pnp_res->res;
	res->flags = IORESOURCE_IRQ | flags;
	res->start = irq;
	res->end = irq;

	dev_printk(KERN_DEBUG, &dev->dev, "%pR\n", res);
	return pnp_res;
}