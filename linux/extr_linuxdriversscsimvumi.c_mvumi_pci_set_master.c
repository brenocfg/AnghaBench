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
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 scalar_t__ IS_DMA64 ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 

__attribute__((used)) static unsigned int mvumi_pci_set_master(struct pci_dev *pdev)
{
	unsigned int ret = 0;
	pci_set_master(pdev);

	if (IS_DMA64) {
		if (pci_set_dma_mask(pdev, DMA_BIT_MASK(64)))
			ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	} else
		ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));

	return ret;
}