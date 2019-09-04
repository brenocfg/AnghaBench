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
typedef  int /*<<< orphan*/  u32 ;
struct mtk_eth {TYPE_1__* soc; } ;
struct TYPE_2__ {int dma_type; } ;

/* Variables and functions */
 int MTK_PDMA ; 
 int MTK_QDMA ; 
 int /*<<< orphan*/  MTK_QMTK_INT_STATUS ; 
 int /*<<< orphan*/  MTK_REG_MTK_INT_STATUS ; 
 int /*<<< orphan*/  mtk_reg_w32 (struct mtk_eth*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mtk_irq_ack(struct mtk_eth *eth, u32 mask)
{
	if (eth->soc->dma_type & MTK_PDMA)
		mtk_reg_w32(eth, mask, MTK_REG_MTK_INT_STATUS);
	if (eth->soc->dma_type & MTK_QDMA)
		mtk_w32(eth, mask, MTK_QMTK_INT_STATUS);
}