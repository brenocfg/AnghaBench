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
struct mtk_tx_ring {int tx_ring_size; int /*<<< orphan*/ * tx_dma; int /*<<< orphan*/  tx_phys; int /*<<< orphan*/ * tx_buf; } ;
struct mtk_eth {int /*<<< orphan*/  dev; struct mtk_tx_ring tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_txd_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_qdma_tx_clean(struct mtk_eth *eth)
{
	struct mtk_tx_ring *ring = &eth->tx_ring;
	int i;

	if (ring->tx_buf) {
		for (i = 0; i < ring->tx_ring_size; i++)
			mtk_txd_unmap(eth->dev, &ring->tx_buf[i]);
		kfree(ring->tx_buf);
		ring->tx_buf = NULL;
	}

	if (ring->tx_dma) {
		dma_free_coherent(eth->dev,
				  ring->tx_ring_size * sizeof(*ring->tx_dma),
				  ring->tx_dma,
				  ring->tx_phys);
		ring->tx_dma = NULL;
	}
}