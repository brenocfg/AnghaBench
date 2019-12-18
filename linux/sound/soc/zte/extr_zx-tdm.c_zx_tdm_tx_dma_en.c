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
struct zx_tdm_info {int dummy; } ;

/* Variables and functions */
 unsigned long DEAGULT_FIFO_THRES ; 
 unsigned long FIFO_CTRL_TX_DMA_EN ; 
 unsigned long FIFO_CTRL_TX_RST ; 
 int /*<<< orphan*/  REG_TX_FIFO_CTRL ; 
 unsigned long zx_tdm_readl (struct zx_tdm_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx_tdm_writel (struct zx_tdm_info*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void zx_tdm_tx_dma_en(struct zx_tdm_info *tdm, bool on)
{
	unsigned long val;

	val = zx_tdm_readl(tdm, REG_TX_FIFO_CTRL);
	val |= FIFO_CTRL_TX_RST | DEAGULT_FIFO_THRES;
	if (on)
		val |= FIFO_CTRL_TX_DMA_EN;
	else
		val &= ~FIFO_CTRL_TX_DMA_EN;
	zx_tdm_writel(tdm, REG_TX_FIFO_CTRL, val);
}