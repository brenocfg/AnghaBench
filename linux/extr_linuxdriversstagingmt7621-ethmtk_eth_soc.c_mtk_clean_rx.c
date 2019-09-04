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
struct mtk_rx_ring {int rx_ring_size; TYPE_1__* rx_dma; int /*<<< orphan*/  rx_phys; int /*<<< orphan*/ * rx_data; int /*<<< orphan*/  rx_buf_size; } ;
struct mtk_eth {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  rxd1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_free_frag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_clean_rx(struct mtk_eth *eth, struct mtk_rx_ring *ring)
{
	int i;

	if (ring->rx_data && ring->rx_dma) {
		for (i = 0; i < ring->rx_ring_size; i++) {
			if (!ring->rx_data[i])
				continue;
			if (!ring->rx_dma[i].rxd1)
				continue;
			dma_unmap_single(eth->dev,
					 ring->rx_dma[i].rxd1,
					 ring->rx_buf_size,
					 DMA_FROM_DEVICE);
			skb_free_frag(ring->rx_data[i]);
		}
		kfree(ring->rx_data);
		ring->rx_data = NULL;
	}

	if (ring->rx_dma) {
		dma_free_coherent(eth->dev,
				  ring->rx_ring_size * sizeof(*ring->rx_dma),
				  ring->rx_dma,
				  ring->rx_phys);
		ring->rx_dma = NULL;
	}
}