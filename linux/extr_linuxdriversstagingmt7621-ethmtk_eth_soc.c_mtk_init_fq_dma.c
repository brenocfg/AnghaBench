#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mtk_tx_dma {int dummy; } ;
struct mtk_eth {TYPE_2__* scratch_ring; int /*<<< orphan*/  dev; int /*<<< orphan*/  scratch_head; TYPE_1__* soc; } ;
typedef  int dma_addr_t ;
struct TYPE_5__ {int txd1; int txd2; int /*<<< orphan*/  txd3; } ;
struct TYPE_4__ {int dma_ring_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTK_QDMA_FQ_BLEN ; 
 int /*<<< orphan*/  MTK_QDMA_FQ_CNT ; 
 int /*<<< orphan*/  MTK_QDMA_FQ_HEAD ; 
 int /*<<< orphan*/  MTK_QDMA_FQ_TAIL ; 
 int QDMA_PAGE_SIZE ; 
 int /*<<< orphan*/  TX_QDMA_SDL (int) ; 
 int __GFP_ZERO ; 
 TYPE_2__* dma_alloc_coherent (int /*<<< orphan*/ ,int,int*,int) ; 
 int dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mtk_init_fq_dma(struct mtk_eth *eth)
{
	dma_addr_t dma_addr, phy_ring_head, phy_ring_tail;
	int cnt = eth->soc->dma_ring_size;
	int i;

	eth->scratch_ring = dma_alloc_coherent(eth->dev,
					       cnt * sizeof(struct mtk_tx_dma),
					       &phy_ring_head,
					       GFP_ATOMIC | __GFP_ZERO);
	if (unlikely(!eth->scratch_ring))
		return -ENOMEM;

	eth->scratch_head = kcalloc(cnt, QDMA_PAGE_SIZE,
				    GFP_KERNEL);
	dma_addr = dma_map_single(eth->dev,
				  eth->scratch_head, cnt * QDMA_PAGE_SIZE,
				  DMA_FROM_DEVICE);
	if (unlikely(dma_mapping_error(eth->dev, dma_addr)))
		return -ENOMEM;

	memset(eth->scratch_ring, 0x0, sizeof(struct mtk_tx_dma) * cnt);
	phy_ring_tail = phy_ring_head + (sizeof(struct mtk_tx_dma) * (cnt - 1));

	for (i = 0; i < cnt; i++) {
		eth->scratch_ring[i].txd1 = (dma_addr + (i * QDMA_PAGE_SIZE));
		if (i < cnt - 1)
			eth->scratch_ring[i].txd2 = (phy_ring_head +
				((i + 1) * sizeof(struct mtk_tx_dma)));
		eth->scratch_ring[i].txd3 = TX_QDMA_SDL(QDMA_PAGE_SIZE);
	}

	mtk_w32(eth, phy_ring_head, MTK_QDMA_FQ_HEAD);
	mtk_w32(eth, phy_ring_tail, MTK_QDMA_FQ_TAIL);
	mtk_w32(eth, (cnt << 16) | cnt, MTK_QDMA_FQ_CNT);
	mtk_w32(eth, QDMA_PAGE_SIZE << 16, MTK_QDMA_FQ_BLEN);

	return 0;
}