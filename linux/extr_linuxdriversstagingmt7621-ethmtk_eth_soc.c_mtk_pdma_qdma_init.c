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
struct TYPE_2__ {int /*<<< orphan*/  rx_calc_idx; int /*<<< orphan*/  rx_ring_size; int /*<<< orphan*/  rx_phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_PST_DRX_IDX0 ; 
 int /*<<< orphan*/  MTK_REG_PDMA_RST_CFG ; 
 int /*<<< orphan*/  MTK_REG_RX_BASE_PTR0 ; 
 int /*<<< orphan*/  MTK_REG_RX_CALC_IDX0 ; 
 int /*<<< orphan*/  MTK_REG_RX_MAX_CNT0 ; 
 int mtk_dma_rx_alloc (struct mtk_eth*,TYPE_1__*) ; 
 int mtk_qdma_init (struct mtk_eth*,int) ; 
 int /*<<< orphan*/  mtk_reg_w32 (struct mtk_eth*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_pdma_qdma_init(struct mtk_eth *eth)
{
	int err = mtk_qdma_init(eth, 1);

	if (err)
		return err;

	err = mtk_dma_rx_alloc(eth, &eth->rx_ring[0]);
	if (err)
		return err;

	mtk_reg_w32(eth, eth->rx_ring[0].rx_phys, MTK_REG_RX_BASE_PTR0);
	mtk_reg_w32(eth, eth->rx_ring[0].rx_ring_size, MTK_REG_RX_MAX_CNT0);
	mtk_reg_w32(eth, eth->rx_ring[0].rx_calc_idx, MTK_REG_RX_CALC_IDX0);
	mtk_reg_w32(eth, MTK_PST_DRX_IDX0, MTK_REG_PDMA_RST_CFG);

	return 0;
}