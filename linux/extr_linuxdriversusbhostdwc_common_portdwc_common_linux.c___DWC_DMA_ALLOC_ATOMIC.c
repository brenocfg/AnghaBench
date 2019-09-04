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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  dwc_dma_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 void* dma_zalloc_coherent (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *__DWC_DMA_ALLOC_ATOMIC(void *dma_ctx, uint32_t size, dwc_dma_t *dma_addr)
{
	return dma_zalloc_coherent(dma_ctx, size, dma_addr, GFP_ATOMIC);
}