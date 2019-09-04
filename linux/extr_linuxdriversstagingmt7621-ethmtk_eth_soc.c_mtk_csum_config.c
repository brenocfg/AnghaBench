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
struct mtk_eth {TYPE_1__* soc; } ;
struct TYPE_2__ {int hw_features; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_CDMA_CSG_CFG ; 
 int MTK_GDM1_ICS_EN ; 
 int MTK_GDM1_TCS_EN ; 
 int MTK_GDM1_UCS_EN ; 
 int /*<<< orphan*/  MTK_GDMA1_FWD_CFG ; 
 int MTK_ICS_GEN_EN ; 
 int MTK_TCS_GEN_EN ; 
 int MTK_UCS_GEN_EN ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int mtk_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 

void mtk_csum_config(struct mtk_eth *eth)
{
	if (eth->soc->hw_features & NETIF_F_RXCSUM)
		mtk_w32(eth, mtk_r32(eth, MTK_GDMA1_FWD_CFG) |
			(MTK_GDM1_ICS_EN | MTK_GDM1_TCS_EN | MTK_GDM1_UCS_EN),
			MTK_GDMA1_FWD_CFG);
	else
		mtk_w32(eth, mtk_r32(eth, MTK_GDMA1_FWD_CFG) &
			~(MTK_GDM1_ICS_EN | MTK_GDM1_TCS_EN | MTK_GDM1_UCS_EN),
			MTK_GDMA1_FWD_CFG);
	if (eth->soc->hw_features & NETIF_F_IP_CSUM)
		mtk_w32(eth, mtk_r32(eth, MTK_CDMA_CSG_CFG) |
			(MTK_ICS_GEN_EN | MTK_TCS_GEN_EN | MTK_UCS_GEN_EN),
			MTK_CDMA_CSG_CFG);
	else
		mtk_w32(eth, mtk_r32(eth, MTK_CDMA_CSG_CFG) &
			~(MTK_ICS_GEN_EN | MTK_TCS_GEN_EN | MTK_UCS_GEN_EN),
			MTK_CDMA_CSG_CFG);
}