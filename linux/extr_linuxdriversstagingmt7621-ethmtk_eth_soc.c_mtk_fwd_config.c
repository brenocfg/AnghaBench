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
struct TYPE_2__ {scalar_t__ jumbo_frame; } ;

/* Variables and functions */
 int MTK_GDM1_JMB_EN ; 
 int /*<<< orphan*/  MTK_GDMA1_FWD_CFG ; 
 int mtk_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 

void mtk_fwd_config(struct mtk_eth *eth)
{
	u32 fwd_cfg;

	fwd_cfg = mtk_r32(eth, MTK_GDMA1_FWD_CFG);

	/* disable jumbo frame */
	if (eth->soc->jumbo_frame)
		fwd_cfg &= ~MTK_GDM1_JMB_EN;

	/* set unicast/multicast/broadcast frame to cpu */
	fwd_cfg &= ~0xffff;

	mtk_w32(eth, fwd_cfg, MTK_GDMA1_FWD_CFG);
}