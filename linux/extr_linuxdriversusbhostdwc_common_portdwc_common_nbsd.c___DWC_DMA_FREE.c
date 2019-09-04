#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ nsegs; int /*<<< orphan*/ * dma_vaddr; int /*<<< orphan*/ * dma_map; scalar_t__ dma_paddr; int /*<<< orphan*/  segs; int /*<<< orphan*/  dma_tag; } ;
typedef  TYPE_1__ dwc_dmactx_t ;
typedef  int /*<<< orphan*/  dwc_dma_t ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamem_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void __DWC_DMA_FREE(void *dma_ctx, uint32_t size, void *virt_addr, dwc_dma_t dma_addr)
{
	dwc_dmactx_t *dma = (dwc_dmactx_t *)dma_ctx;

	if (dma->dma_map != NULL) {
		bus_dmamap_sync(dma->dma_tag, dma->dma_map, 0, size,
				BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(dma->dma_tag, dma->dma_map);
		bus_dmamap_destroy(dma->dma_tag, dma->dma_map);
		bus_dmamem_unmap(dma->dma_tag, dma->dma_vaddr, size);
		bus_dmamem_free(dma->dma_tag, dma->segs, dma->nsegs);
		dma->dma_paddr = 0;
		dma->dma_map = NULL;
		dma->dma_vaddr = NULL;
		dma->nsegs = 0;
	}
}