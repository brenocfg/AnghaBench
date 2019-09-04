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
struct mtk_eth {int /*<<< orphan*/  page_lock; TYPE_1__* soc; } ;
struct TYPE_2__ {int dma_type; int pdma_glo_cfg; scalar_t__ rx_2b_offset; } ;

/* Variables and functions */
 int MTK_PDMA ; 
 int MTK_QDMA ; 
 int /*<<< orphan*/  MTK_QDMA_GLO_CFG ; 
 int /*<<< orphan*/  MTK_REG_PDMA_GLO_CFG ; 
 int MTK_RX_2B_OFFSET ; 
 int MTK_RX_DMA_EN ; 
 int MTK_TX_DMA_EN ; 
 int MTK_TX_WB_DDONE ; 
 int /*<<< orphan*/  mtk_dma_free (struct mtk_eth*) ; 
 int mtk_pdma_init (struct mtk_eth*) ; 
 int mtk_pdma_qdma_init (struct mtk_eth*) ; 
 int mtk_qdma_init (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_reg_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mtk_start_dma(struct mtk_eth *eth)
{
	unsigned long flags;
	u32 val;
	int err;

	if (eth->soc->dma_type == MTK_PDMA)
		err = mtk_pdma_init(eth);
	else if (eth->soc->dma_type == MTK_QDMA)
		err = mtk_qdma_init(eth, 0);
	else
		err = mtk_pdma_qdma_init(eth);
	if (err) {
		mtk_dma_free(eth);
		return err;
	}

	spin_lock_irqsave(&eth->page_lock, flags);

	val = MTK_TX_WB_DDONE | MTK_RX_DMA_EN | MTK_TX_DMA_EN;
	if (eth->soc->rx_2b_offset)
		val |= MTK_RX_2B_OFFSET;
	val |= eth->soc->pdma_glo_cfg;

	if (eth->soc->dma_type & MTK_PDMA)
		mtk_reg_w32(eth, val, MTK_REG_PDMA_GLO_CFG);

	if (eth->soc->dma_type & MTK_QDMA)
		mtk_w32(eth, val, MTK_QDMA_GLO_CFG);

	spin_unlock_irqrestore(&eth->page_lock, flags);

	return 0;
}