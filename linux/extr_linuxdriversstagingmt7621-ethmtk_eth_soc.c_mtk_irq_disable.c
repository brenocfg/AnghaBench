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
struct mtk_eth {TYPE_1__* soc; } ;
struct TYPE_2__ {int dma_type; } ;

/* Variables and functions */
 int MTK_PDMA ; 
 int MTK_QDMA ; 
 int /*<<< orphan*/  MTK_QMTK_INT_ENABLE ; 
 int /*<<< orphan*/  MTK_REG_MTK_INT_ENABLE ; 
 int mtk_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int mtk_reg_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_reg_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mtk_irq_disable(struct mtk_eth *eth, u32 mask)
{
	u32 val;

	if (eth->soc->dma_type & MTK_PDMA) {
		val = mtk_reg_r32(eth, MTK_REG_MTK_INT_ENABLE);
		mtk_reg_w32(eth, val & ~mask, MTK_REG_MTK_INT_ENABLE);
		/* flush write */
		mtk_reg_r32(eth, MTK_REG_MTK_INT_ENABLE);
	}
	if (eth->soc->dma_type & MTK_QDMA) {
		val = mtk_r32(eth, MTK_QMTK_INT_ENABLE);
		mtk_w32(eth, val & ~mask, MTK_QMTK_INT_ENABLE);
		/* flush write */
		mtk_r32(eth, MTK_QMTK_INT_ENABLE);
	}
}