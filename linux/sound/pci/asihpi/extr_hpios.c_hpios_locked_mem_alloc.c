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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct consistent_dma_area {scalar_t__ size; int /*<<< orphan*/ * pdev; scalar_t__ vaddr; scalar_t__ dma_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  WARNING ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 

u16 hpios_locked_mem_alloc(struct consistent_dma_area *p_mem_area, u32 size,
	struct pci_dev *pdev)
{
	/*?? any benefit in using managed dmam_alloc_coherent? */
	p_mem_area->vaddr =
		dma_alloc_coherent(&pdev->dev, size, &p_mem_area->dma_handle,
		GFP_KERNEL);

	if (p_mem_area->vaddr) {
		HPI_DEBUG_LOG(DEBUG, "allocated %d bytes, dma 0x%x vma %p\n",
			size, (unsigned int)p_mem_area->dma_handle,
			p_mem_area->vaddr);
		p_mem_area->pdev = &pdev->dev;
		p_mem_area->size = size;
		return 0;
	} else {
		HPI_DEBUG_LOG(WARNING,
			"failed to allocate %d bytes locked memory\n", size);
		p_mem_area->size = 0;
		return 1;
	}
}