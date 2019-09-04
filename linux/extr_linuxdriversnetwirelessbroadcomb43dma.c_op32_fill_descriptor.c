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
typedef  int u32 ;
typedef  int u16 ;
struct b43_dmaring {int nr_slots; TYPE_1__* dev; struct b43_dmadesc32* descbase; } ;
struct b43_dmadesc32 {void* address; void* control; } ;
struct b43_dmadesc_generic {struct b43_dmadesc32 dma32; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int B43_DMA32_DCTL_ADDREXT_MASK ; 
 int B43_DMA32_DCTL_ADDREXT_SHIFT ; 
 int B43_DMA32_DCTL_BYTECNT ; 
 int B43_DMA32_DCTL_DTABLEEND ; 
 int B43_DMA32_DCTL_FRAMEEND ; 
 int B43_DMA32_DCTL_FRAMESTART ; 
 int B43_DMA32_DCTL_IRQ ; 
 int /*<<< orphan*/  B43_DMA_ADDR_EXT ; 
 int /*<<< orphan*/  B43_DMA_ADDR_LOW ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int b43_dma_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 

__attribute__((used)) static void op32_fill_descriptor(struct b43_dmaring *ring,
				 struct b43_dmadesc_generic *desc,
				 dma_addr_t dmaaddr, u16 bufsize,
				 int start, int end, int irq)
{
	struct b43_dmadesc32 *descbase = ring->descbase;
	int slot;
	u32 ctl;
	u32 addr;
	u32 addrext;

	slot = (int)(&(desc->dma32) - descbase);
	B43_WARN_ON(!(slot >= 0 && slot < ring->nr_slots));

	addr = b43_dma_address(&ring->dev->dma, dmaaddr, B43_DMA_ADDR_LOW);
	addrext = b43_dma_address(&ring->dev->dma, dmaaddr, B43_DMA_ADDR_EXT);

	ctl = bufsize & B43_DMA32_DCTL_BYTECNT;
	if (slot == ring->nr_slots - 1)
		ctl |= B43_DMA32_DCTL_DTABLEEND;
	if (start)
		ctl |= B43_DMA32_DCTL_FRAMESTART;
	if (end)
		ctl |= B43_DMA32_DCTL_FRAMEEND;
	if (irq)
		ctl |= B43_DMA32_DCTL_IRQ;
	ctl |= (addrext << B43_DMA32_DCTL_ADDREXT_SHIFT)
	    & B43_DMA32_DCTL_ADDREXT_MASK;

	desc->dma32.control = cpu_to_le32(ctl);
	desc->dma32.address = cpu_to_le32(addr);
}