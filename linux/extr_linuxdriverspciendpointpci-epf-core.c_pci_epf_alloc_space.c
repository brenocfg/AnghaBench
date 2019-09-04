#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_epf {TYPE_1__* bar; TYPE_3__* epc; } ;
struct device {int dummy; } ;
typedef  enum pci_barno { ____Placeholder_pci_barno } pci_barno ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {struct device* parent; } ;
struct TYPE_6__ {TYPE_2__ dev; } ;
struct TYPE_4__ {size_t size; int barno; int /*<<< orphan*/  flags; int /*<<< orphan*/  phys_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_SPACE_MEMORY ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* dma_alloc_coherent (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t roundup_pow_of_two (size_t) ; 

void *pci_epf_alloc_space(struct pci_epf *epf, size_t size, enum pci_barno bar)
{
	void *space;
	struct device *dev = epf->epc->dev.parent;
	dma_addr_t phys_addr;

	if (size < 128)
		size = 128;
	size = roundup_pow_of_two(size);

	space = dma_alloc_coherent(dev, size, &phys_addr, GFP_KERNEL);
	if (!space) {
		dev_err(dev, "failed to allocate mem space\n");
		return NULL;
	}

	epf->bar[bar].phys_addr = phys_addr;
	epf->bar[bar].size = size;
	epf->bar[bar].barno = bar;
	epf->bar[bar].flags = PCI_BASE_ADDRESS_SPACE_MEMORY;

	return space;
}