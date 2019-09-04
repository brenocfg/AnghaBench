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
struct resource {int /*<<< orphan*/  flags; } ;
struct parisc_device {int dummy; } ;
struct gsc_asic {int /*<<< orphan*/  name; int /*<<< orphan*/  hpa; int /*<<< orphan*/ * global_irq; struct parisc_device* gsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  NO_IRQ ; 
 struct resource* request_mem_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int gsc_common_setup(struct parisc_device *parent, struct gsc_asic *gsc_asic)
{
	struct resource *res;
	int i;

	gsc_asic->gsc = parent;

	/* Initialise local irq -> global irq mapping */
	for (i = 0; i < 32; i++) {
		gsc_asic->global_irq[i] = NO_IRQ;
	}

	/* allocate resource region */
	res = request_mem_region(gsc_asic->hpa, 0x100000, gsc_asic->name);
	if (res) {
		res->flags = IORESOURCE_MEM; 	/* do not mark it busy ! */
	}

#if 0
	printk(KERN_WARNING "%s IRQ %d EIM 0x%x", gsc_asic->name,
			parent->irq, gsc_asic->eim);
	if (gsc_readl(gsc_asic->hpa + OFFSET_IMR))
		printk("  IMR is non-zero! (0x%x)",
				gsc_readl(gsc_asic->hpa + OFFSET_IMR));
	printk("\n");
#endif

	return 0;
}