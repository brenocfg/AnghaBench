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
 int /*<<< orphan*/  mtk_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_reg_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 mtk_irq_pending(struct mtk_eth *eth)
{
	u32 status = 0;

	if (eth->soc->dma_type & MTK_PDMA)
		status |= mtk_reg_r32(eth, MTK_REG_MTK_INT_STATUS);
	if (eth->soc->dma_type & MTK_QDMA)
		status |= mtk_r32(eth, MTK_QMTK_INT_STATUS);

	return status;
}