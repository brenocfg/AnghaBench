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
struct gem {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ MAC_RXCFG ; 
 int MAC_RXCFG_ENAB ; 
 scalar_t__ MAC_TXCFG ; 
 int MAC_TXCFG_ENAB ; 
 scalar_t__ RXDMA_CFG ; 
 int RXDMA_CFG_ENABLE ; 
 scalar_t__ RXDMA_KICK ; 
 int RX_RING_SIZE ; 
 scalar_t__ TXDMA_CFG ; 
 int TXDMA_CFG_ENABLE ; 
 int /*<<< orphan*/  gem_enable_ints (struct gem*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void gem_start_dma(struct gem *gp)
{
	u32 val;

	/* We are ready to rock, turn everything on. */
	val = readl(gp->regs + TXDMA_CFG);
	writel(val | TXDMA_CFG_ENABLE, gp->regs + TXDMA_CFG);
	val = readl(gp->regs + RXDMA_CFG);
	writel(val | RXDMA_CFG_ENABLE, gp->regs + RXDMA_CFG);
	val = readl(gp->regs + MAC_TXCFG);
	writel(val | MAC_TXCFG_ENAB, gp->regs + MAC_TXCFG);
	val = readl(gp->regs + MAC_RXCFG);
	writel(val | MAC_RXCFG_ENAB, gp->regs + MAC_RXCFG);

	(void) readl(gp->regs + MAC_RXCFG);
	udelay(100);

	gem_enable_ints(gp);

	writel(RX_RING_SIZE - 4, gp->regs + RXDMA_KICK);
}