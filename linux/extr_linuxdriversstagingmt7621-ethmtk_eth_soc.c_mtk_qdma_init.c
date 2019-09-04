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
struct mtk_eth {TYPE_1__* rx_ring; } ;
struct TYPE_2__ {int rx_phys; int rx_ring_size; int rx_calc_idx; } ;

/* Variables and functions */
 int MTK_PST_DRX_IDX0 ; 
 int /*<<< orphan*/  MTK_QDMA_FC_THRES ; 
 int /*<<< orphan*/  MTK_QDMA_HRED2 ; 
 int /*<<< orphan*/  MTK_QDMA_RST_IDX ; 
 int /*<<< orphan*/  MTK_QRX_BASE_PTR0 ; 
 int /*<<< orphan*/  MTK_QRX_CRX_IDX0 ; 
 int /*<<< orphan*/  MTK_QRX_MAX_CNT0 ; 
 int /*<<< orphan*/  MTK_QTX_CFG (int /*<<< orphan*/ ) ; 
 int QDMA_RES_THRES ; 
 int mtk_dma_rx_alloc (struct mtk_eth*,TYPE_1__*) ; 
 int mtk_init_fq_dma (struct mtk_eth*) ; 
 int mtk_qdma_tx_alloc_tx (struct mtk_eth*) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_qdma_init(struct mtk_eth *eth, int ring)
{
	int err;

	err = mtk_init_fq_dma(eth);
	if (err)
		return err;

	err = mtk_qdma_tx_alloc_tx(eth);
	if (err)
		return err;

	err = mtk_dma_rx_alloc(eth, &eth->rx_ring[ring]);
	if (err)
		return err;

	mtk_w32(eth, eth->rx_ring[ring].rx_phys, MTK_QRX_BASE_PTR0);
	mtk_w32(eth, eth->rx_ring[ring].rx_ring_size, MTK_QRX_MAX_CNT0);
	mtk_w32(eth, eth->rx_ring[ring].rx_calc_idx, MTK_QRX_CRX_IDX0);
	mtk_w32(eth, MTK_PST_DRX_IDX0, MTK_QDMA_RST_IDX);
	mtk_w32(eth, (QDMA_RES_THRES << 8) | QDMA_RES_THRES, MTK_QTX_CFG(0));

	/* Enable random early drop and set drop threshold automatically */
	mtk_w32(eth, 0x174444, MTK_QDMA_FC_THRES);
	mtk_w32(eth, 0x0, MTK_QDMA_HRED2);

	return 0;
}