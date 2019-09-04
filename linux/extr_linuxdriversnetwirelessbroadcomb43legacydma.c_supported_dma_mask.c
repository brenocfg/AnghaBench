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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct b43legacy_wldev {int dummy; } ;

/* Variables and functions */
 int B43legacy_DMA32_TXADDREXT_MASK ; 
 scalar_t__ B43legacy_DMA32_TXCTL ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 scalar_t__ b43legacy_dmacontroller_base (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int b43legacy_read32 (struct b43legacy_wldev*,scalar_t__) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,scalar_t__,int) ; 

__attribute__((used)) static u64 supported_dma_mask(struct b43legacy_wldev *dev)
{
	u32 tmp;
	u16 mmio_base;

	mmio_base = b43legacy_dmacontroller_base(0, 0);
	b43legacy_write32(dev,
			mmio_base + B43legacy_DMA32_TXCTL,
			B43legacy_DMA32_TXADDREXT_MASK);
	tmp = b43legacy_read32(dev, mmio_base +
			       B43legacy_DMA32_TXCTL);
	if (tmp & B43legacy_DMA32_TXADDREXT_MASK)
		return DMA_BIT_MASK(32);

	return DMA_BIT_MASK(30);
}