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
struct cas {int cas_flags; scalar_t__ regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CAS_FLAG_REG_PLUS ; 
 int MAC_RX_CFG_EN ; 
 int MAC_TX_CFG_EN ; 
 int N_RX_COMP_RINGS ; 
 int N_RX_DESC_RINGS ; 
 scalar_t__ REG_MAC_RX_CFG ; 
 scalar_t__ REG_MAC_STATE_MACHINE ; 
 scalar_t__ REG_MAC_TX_CFG ; 
 scalar_t__ REG_MIF_STATE_MACHINE ; 
 scalar_t__ REG_PLUS_RX_COMPN_TAIL (int) ; 
 scalar_t__ REG_PLUS_RX_KICK1 ; 
 scalar_t__ REG_RX_CFG ; 
 scalar_t__ REG_RX_COMP_TAIL ; 
 scalar_t__ REG_RX_KICK ; 
 scalar_t__ REG_TX_CFG ; 
 int RX_CFG_DMA_EN ; 
 int RX_DESC_RINGN_SIZE (int) ; 
 int STOP_TRIES ; 
 int TX_CFG_DMA_EN ; 
 int /*<<< orphan*/  cas_unmask_intr (struct cas*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void cas_start_dma(struct cas *cp)
{
	int i;
	u32 val;
	int txfailed = 0;

	/* enable dma */
	val = readl(cp->regs + REG_TX_CFG) | TX_CFG_DMA_EN;
	writel(val, cp->regs + REG_TX_CFG);
	val = readl(cp->regs + REG_RX_CFG) | RX_CFG_DMA_EN;
	writel(val, cp->regs + REG_RX_CFG);

	/* enable the mac */
	val = readl(cp->regs + REG_MAC_TX_CFG) | MAC_TX_CFG_EN;
	writel(val, cp->regs + REG_MAC_TX_CFG);
	val = readl(cp->regs + REG_MAC_RX_CFG) | MAC_RX_CFG_EN;
	writel(val, cp->regs + REG_MAC_RX_CFG);

	i = STOP_TRIES;
	while (i-- > 0) {
		val = readl(cp->regs + REG_MAC_TX_CFG);
		if ((val & MAC_TX_CFG_EN))
			break;
		udelay(10);
	}
	if (i < 0) txfailed = 1;
	i = STOP_TRIES;
	while (i-- > 0) {
		val = readl(cp->regs + REG_MAC_RX_CFG);
		if ((val & MAC_RX_CFG_EN)) {
			if (txfailed) {
				netdev_err(cp->dev,
					   "enabling mac failed [tx:%08x:%08x]\n",
					   readl(cp->regs + REG_MIF_STATE_MACHINE),
					   readl(cp->regs + REG_MAC_STATE_MACHINE));
			}
			goto enable_rx_done;
		}
		udelay(10);
	}
	netdev_err(cp->dev, "enabling mac failed [%s:%08x:%08x]\n",
		   (txfailed ? "tx,rx" : "rx"),
		   readl(cp->regs + REG_MIF_STATE_MACHINE),
		   readl(cp->regs + REG_MAC_STATE_MACHINE));

enable_rx_done:
	cas_unmask_intr(cp); /* enable interrupts */
	writel(RX_DESC_RINGN_SIZE(0) - 4, cp->regs + REG_RX_KICK);
	writel(0, cp->regs + REG_RX_COMP_TAIL);

	if (cp->cas_flags & CAS_FLAG_REG_PLUS) {
		if (N_RX_DESC_RINGS > 1)
			writel(RX_DESC_RINGN_SIZE(1) - 4,
			       cp->regs + REG_PLUS_RX_KICK1);

		for (i = 1; i < N_RX_COMP_RINGS; i++)
			writel(0, cp->regs + REG_PLUS_RX_COMPN_TAIL(i));
	}
}