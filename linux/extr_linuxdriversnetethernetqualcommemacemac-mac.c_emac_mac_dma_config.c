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
typedef  int u32 ;
struct emac_adapter {int dma_order; scalar_t__ base; scalar_t__ dmaw_dly_cnt; scalar_t__ dmar_dly_cnt; scalar_t__ dmaw_block; scalar_t__ dmar_block; } ;

/* Variables and functions */
 int DMAR_DLY_CNT_BMSK ; 
 int DMAR_DLY_CNT_SHFT ; 
 int DMAR_REQ_PRI ; 
 int DMAW_DLY_CNT_BMSK ; 
 int DMAW_DLY_CNT_SHFT ; 
 scalar_t__ EMAC_DMA_CTRL ; 
 int ENH_ORDER_MODE ; 
 int IN_ORDER_MODE ; 
 int OUT_ORDER_MODE ; 
 int REGRDBLEN_BMSK ; 
 int REGRDBLEN_SHFT ; 
 int REGWRBLEN_BMSK ; 
 int REGWRBLEN_SHFT ; 
#define  emac_dma_ord_enh 130 
#define  emac_dma_ord_in 129 
#define  emac_dma_ord_out 128 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void emac_mac_dma_config(struct emac_adapter *adpt)
{
	u32 dma_ctrl = DMAR_REQ_PRI;

	switch (adpt->dma_order) {
	case emac_dma_ord_in:
		dma_ctrl |= IN_ORDER_MODE;
		break;
	case emac_dma_ord_enh:
		dma_ctrl |= ENH_ORDER_MODE;
		break;
	case emac_dma_ord_out:
		dma_ctrl |= OUT_ORDER_MODE;
		break;
	default:
		break;
	}

	dma_ctrl |= (((u32)adpt->dmar_block) << REGRDBLEN_SHFT) &
						REGRDBLEN_BMSK;
	dma_ctrl |= (((u32)adpt->dmaw_block) << REGWRBLEN_SHFT) &
						REGWRBLEN_BMSK;
	dma_ctrl |= (((u32)adpt->dmar_dly_cnt) << DMAR_DLY_CNT_SHFT) &
						DMAR_DLY_CNT_BMSK;
	dma_ctrl |= (((u32)adpt->dmaw_dly_cnt) << DMAW_DLY_CNT_SHFT) &
						DMAW_DLY_CNT_BMSK;

	/* config DMA and ensure that configuration is flushed to HW */
	writel(dma_ctrl, adpt->base + EMAC_DMA_CTRL);
}