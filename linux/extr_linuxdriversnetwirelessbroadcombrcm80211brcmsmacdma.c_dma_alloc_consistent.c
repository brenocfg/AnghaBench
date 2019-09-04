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
typedef  int /*<<< orphan*/  uint ;
typedef  int u16 ;
struct dma_info {int /*<<< orphan*/  dmadev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *dma_alloc_consistent(struct dma_info *di, uint size,
				  u16 align_bits, uint *alloced,
				  dma_addr_t *pap)
{
	if (align_bits) {
		u16 align = (1 << align_bits);
		if (!IS_ALIGNED(PAGE_SIZE, align))
			size += align;
		*alloced = size;
	}
	return dma_alloc_coherent(di->dmadev, size, pap, GFP_ATOMIC);
}