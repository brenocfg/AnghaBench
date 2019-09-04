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
struct mtk_rx_ring {int rx_ring_size; int rx_calc_idx; TYPE_2__* rx_dma; int /*<<< orphan*/  rx_buf_size; scalar_t__* rx_data; int /*<<< orphan*/  rx_phys; int /*<<< orphan*/  frag_size; } ;
struct mtk_eth {TYPE_1__* soc; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {unsigned int rxd1; int /*<<< orphan*/  rxd2; } ;
struct TYPE_3__ {int dma_ring_size; scalar_t__ rx_sg_dma; int /*<<< orphan*/  rx_2b_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_DATA_LEN ; 
 int GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NET_IP_ALIGN ; 
 scalar_t__ NET_SKB_PAD ; 
 int /*<<< orphan*/  RX_DMA_LSO ; 
 int /*<<< orphan*/  RX_DMA_PLEN0 (int /*<<< orphan*/ ) ; 
 int __GFP_ZERO ; 
 TYPE_2__* dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_max_buf_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_max_frag_size (int /*<<< orphan*/ ) ; 
 scalar_t__ netdev_alloc_frag (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int mtk_dma_rx_alloc(struct mtk_eth *eth, struct mtk_rx_ring *ring)
{
	int i, pad = 0;

	ring->frag_size = mtk_max_frag_size(ETH_DATA_LEN);
	ring->rx_buf_size = mtk_max_buf_size(ring->frag_size);
	ring->rx_ring_size = eth->soc->dma_ring_size;
	ring->rx_data = kcalloc(ring->rx_ring_size, sizeof(*ring->rx_data),
				GFP_KERNEL);
	if (!ring->rx_data)
		goto no_rx_mem;

	for (i = 0; i < ring->rx_ring_size; i++) {
		ring->rx_data[i] = netdev_alloc_frag(ring->frag_size);
		if (!ring->rx_data[i])
			goto no_rx_mem;
	}

	ring->rx_dma =
		dma_alloc_coherent(eth->dev,
				   ring->rx_ring_size * sizeof(*ring->rx_dma),
				   &ring->rx_phys, GFP_ATOMIC | __GFP_ZERO);
	if (!ring->rx_dma)
		goto no_rx_mem;

	if (!eth->soc->rx_2b_offset)
		pad = NET_IP_ALIGN;

	for (i = 0; i < ring->rx_ring_size; i++) {
		dma_addr_t dma_addr = dma_map_single(eth->dev,
				ring->rx_data[i] + NET_SKB_PAD + pad,
				ring->rx_buf_size,
				DMA_FROM_DEVICE);
		if (unlikely(dma_mapping_error(eth->dev, dma_addr)))
			goto no_rx_mem;
		ring->rx_dma[i].rxd1 = (unsigned int)dma_addr;

		if (eth->soc->rx_sg_dma)
			ring->rx_dma[i].rxd2 = RX_DMA_PLEN0(ring->rx_buf_size);
		else
			ring->rx_dma[i].rxd2 = RX_DMA_LSO;
	}
	ring->rx_calc_idx = ring->rx_ring_size - 1;
	/* make sure that all changes to the dma ring are flushed before we
	 * continue
	 */
	wmb();

	return 0;

no_rx_mem:
	return -ENOMEM;
}