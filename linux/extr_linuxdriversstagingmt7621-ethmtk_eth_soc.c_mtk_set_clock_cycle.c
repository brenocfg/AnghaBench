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
struct mtk_eth {unsigned long sysclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_GLO_CFG ; 
 unsigned long MTK_US_CYC_CNT_DIVISOR ; 
 unsigned long MTK_US_CYC_CNT_MASK ; 
 unsigned long MTK_US_CYC_CNT_SHIFT ; 
 unsigned long mtk_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,unsigned long,int /*<<< orphan*/ ) ; 

int mtk_set_clock_cycle(struct mtk_eth *eth)
{
	unsigned long sysclk = eth->sysclk;

	sysclk /= MTK_US_CYC_CNT_DIVISOR;
	sysclk <<= MTK_US_CYC_CNT_SHIFT;

	mtk_w32(eth, (mtk_r32(eth, MTK_GLO_CFG) &
			~(MTK_US_CYC_CNT_MASK << MTK_US_CYC_CNT_SHIFT)) |
			sysclk,
			MTK_GLO_CFG);
	return 0;
}