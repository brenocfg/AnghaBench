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
typedef  int u16 ;
struct consistent_dma_area {scalar_t__ size; int /*<<< orphan*/  vaddr; scalar_t__ dma_handle; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*,unsigned long,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

u16 hpios_locked_mem_free(struct consistent_dma_area *p_mem_area)
{
	if (p_mem_area->size) {
		dma_free_coherent(p_mem_area->pdev, p_mem_area->size,
			p_mem_area->vaddr, p_mem_area->dma_handle);
		HPI_DEBUG_LOG(DEBUG, "freed %lu bytes, dma 0x%x vma %p\n",
			(unsigned long)p_mem_area->size,
			(unsigned int)p_mem_area->dma_handle,
			p_mem_area->vaddr);
		p_mem_area->size = 0;
		return 0;
	} else {
		return 1;
	}
}