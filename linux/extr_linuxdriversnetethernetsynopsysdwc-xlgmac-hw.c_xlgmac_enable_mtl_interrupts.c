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
struct TYPE_2__ {int /*<<< orphan*/  rx_q_cnt; int /*<<< orphan*/  tx_q_cnt; } ;
struct xlgmac_pdata {TYPE_1__ hw_feat; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTL_Q_IER ; 
 int /*<<< orphan*/  MTL_Q_ISR ; 
 int /*<<< orphan*/  XLGMAC_MTL_REG (struct xlgmac_pdata*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xlgmac_enable_mtl_interrupts(struct xlgmac_pdata *pdata)
{
	unsigned int q_count, i;
	unsigned int mtl_q_isr;

	q_count = max(pdata->hw_feat.tx_q_cnt, pdata->hw_feat.rx_q_cnt);
	for (i = 0; i < q_count; i++) {
		/* Clear all the interrupts which are set */
		mtl_q_isr = readl(XLGMAC_MTL_REG(pdata, i, MTL_Q_ISR));
		writel(mtl_q_isr, XLGMAC_MTL_REG(pdata, i, MTL_Q_ISR));

		/* No MTL interrupts to be enabled */
		writel(0, XLGMAC_MTL_REG(pdata, i, MTL_Q_IER));
	}
}