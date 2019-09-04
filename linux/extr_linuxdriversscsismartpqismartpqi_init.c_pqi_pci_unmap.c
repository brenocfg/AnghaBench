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
struct pqi_sg_descriptor {int /*<<< orphan*/  length; int /*<<< orphan*/  address; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int PCI_DMA_NONE ; 
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_unaligned_le64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pqi_pci_unmap(struct pci_dev *pci_dev,
	struct pqi_sg_descriptor *descriptors, int num_descriptors,
	int data_direction)
{
	int i;

	if (data_direction == PCI_DMA_NONE)
		return;

	for (i = 0; i < num_descriptors; i++)
		pci_unmap_single(pci_dev,
			(dma_addr_t)get_unaligned_le64(&descriptors[i].address),
			get_unaligned_le32(&descriptors[i].length),
			data_direction);
}