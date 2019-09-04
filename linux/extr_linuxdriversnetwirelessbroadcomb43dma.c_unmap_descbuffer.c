#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct b43_dmaring {TYPE_2__* dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
    void unmap_descbuffer(struct b43_dmaring *ring,
			  dma_addr_t addr, size_t len, int tx)
{
	if (tx) {
		dma_unmap_single(ring->dev->dev->dma_dev,
				 addr, len, DMA_TO_DEVICE);
	} else {
		dma_unmap_single(ring->dev->dev->dma_dev,
				 addr, len, DMA_FROM_DEVICE);
	}
}