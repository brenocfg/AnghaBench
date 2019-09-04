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
struct resource {int flags; int /*<<< orphan*/  start; } ;
struct pnp_dev {int dummy; } ;

/* Variables and functions */
 int IORESOURCE_DISABLED ; 
 int /*<<< orphan*/  pcibios_penalize_isa_irq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pnp_add_resource (struct pnp_dev*,struct resource*) ; 

__attribute__((used)) static void pnpacpi_add_irqresource(struct pnp_dev *dev, struct resource *r)
{
	if (!(r->flags & IORESOURCE_DISABLED))
		pcibios_penalize_isa_irq(r->start, 1);

	pnp_add_resource(dev, r);
}