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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,size_t,void*,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static void tsi148_free_consistent(struct device *parent, size_t size,
	void *vaddr, dma_addr_t dma)
{
	struct pci_dev *pdev;

	/* Find pci_dev container of dev */
	pdev = to_pci_dev(parent);

	pci_free_consistent(pdev, size, vaddr, dma);
}