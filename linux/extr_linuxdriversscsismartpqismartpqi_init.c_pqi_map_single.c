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
typedef  int /*<<< orphan*/  u64 ;
struct pqi_sg_descriptor {int /*<<< orphan*/  flags; int /*<<< orphan*/  length; int /*<<< orphan*/  address; } ;
struct pci_dev {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 size_t CISS_SG_LAST ; 
 int ENOMEM ; 
 int PCI_DMA_NONE ; 
 scalar_t__ pci_dma_mapping_error (struct pci_dev*,scalar_t__) ; 
 scalar_t__ pci_map_single (struct pci_dev*,void*,size_t,int) ; 
 int /*<<< orphan*/  put_unaligned_le32 (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pqi_map_single(struct pci_dev *pci_dev,
	struct pqi_sg_descriptor *sg_descriptor, void *buffer,
	size_t buffer_length, int data_direction)
{
	dma_addr_t bus_address;

	if (!buffer || buffer_length == 0 || data_direction == PCI_DMA_NONE)
		return 0;

	bus_address = pci_map_single(pci_dev, buffer, buffer_length,
		data_direction);
	if (pci_dma_mapping_error(pci_dev, bus_address))
		return -ENOMEM;

	put_unaligned_le64((u64)bus_address, &sg_descriptor->address);
	put_unaligned_le32(buffer_length, &sg_descriptor->length);
	put_unaligned_le32(CISS_SG_LAST, &sg_descriptor->flags);

	return 0;
}