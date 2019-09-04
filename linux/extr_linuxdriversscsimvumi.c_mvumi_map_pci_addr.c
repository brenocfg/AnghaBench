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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IORESOURCE_MEM ; 
 int MAX_BASE_ADDRESS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mvumi_unmap_pci_addr (struct pci_dev*,void**) ; 
 void* pci_iomap (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,int) ; 

__attribute__((used)) static int mvumi_map_pci_addr(struct pci_dev *dev, void **addr_array)
{
	int i;

	for (i = 0; i < MAX_BASE_ADDRESS; i++) {
		if (pci_resource_flags(dev, i) & IORESOURCE_MEM) {
			addr_array[i] = pci_iomap(dev, i, 0);
			if (!addr_array[i]) {
				dev_err(&dev->dev, "failed to map Bar[%d]\n",
									i);
				mvumi_unmap_pci_addr(dev, addr_array);
				return -ENOMEM;
			}
		} else
			addr_array[i] = NULL;

		dev_dbg(&dev->dev, "Bar %d : %p.\n", i, addr_array[i]);
	}

	return 0;
}