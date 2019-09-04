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
struct b43legacy_dmaring {int /*<<< orphan*/  type; int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  dev; scalar_t__ tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_DMA32_RXRING ; 
 int /*<<< orphan*/  B43legacy_DMA32_TXRING ; 
 int /*<<< orphan*/  b43legacy_dma_write (struct b43legacy_dmaring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_dmacontroller_rx_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_dmacontroller_tx_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmacontroller_cleanup(struct b43legacy_dmaring *ring)
{
	if (ring->tx) {
		b43legacy_dmacontroller_tx_reset(ring->dev, ring->mmio_base,
						 ring->type);
		b43legacy_dma_write(ring, B43legacy_DMA32_TXRING, 0);
	} else {
		b43legacy_dmacontroller_rx_reset(ring->dev, ring->mmio_base,
						 ring->type);
		b43legacy_dma_write(ring, B43legacy_DMA32_RXRING, 0);
	}
}