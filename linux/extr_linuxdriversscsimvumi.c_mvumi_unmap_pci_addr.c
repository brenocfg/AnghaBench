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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int IORESOURCE_MEM ; 
 int MAX_BASE_ADDRESS ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,void*) ; 
 int pci_resource_flags (struct pci_dev*,int) ; 

__attribute__((used)) static void mvumi_unmap_pci_addr(struct pci_dev *dev, void **addr_array)
{
	int i;

	for (i = 0; i < MAX_BASE_ADDRESS; i++)
		if ((pci_resource_flags(dev, i) & IORESOURCE_MEM) &&
								addr_array[i])
			pci_iounmap(dev, addr_array[i]);
}