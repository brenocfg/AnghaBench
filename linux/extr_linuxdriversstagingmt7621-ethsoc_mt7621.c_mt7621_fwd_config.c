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
struct mtk_eth {int dummy; } ;

/* Variables and functions */
 int GDMA_ICS_EN ; 
 int GDMA_TCS_EN ; 
 int GDMA_UCS_EN ; 
 int /*<<< orphan*/  MT7620_GDMA1_FWD_CFG ; 
 int /*<<< orphan*/  MT7621_CDMP_EG_CTRL ; 
 int mtk_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7621_fwd_config(struct mtk_eth *eth)
{
	/* Setup GMAC1 only, there is no support for GMAC2 yet */
	mtk_w32(eth, mtk_r32(eth, MT7620_GDMA1_FWD_CFG) & ~0xffff,
		MT7620_GDMA1_FWD_CFG);

	/* Enable RX checksum */
	mtk_w32(eth, mtk_r32(eth, MT7620_GDMA1_FWD_CFG) | (GDMA_ICS_EN |
		       GDMA_TCS_EN | GDMA_UCS_EN),
		       MT7620_GDMA1_FWD_CFG);

	/* Enable RX VLan Offloading */
	mtk_w32(eth, 0, MT7621_CDMP_EG_CTRL);

	return 0;
}