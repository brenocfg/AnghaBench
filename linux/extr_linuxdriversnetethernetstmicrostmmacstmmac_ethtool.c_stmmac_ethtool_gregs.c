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
typedef  int /*<<< orphan*/  u32 ;
struct stmmac_priv {int /*<<< orphan*/  ioaddr; int /*<<< orphan*/  hw; } ;
struct net_device {int dummy; } ;
struct ethtool_regs {int dummy; } ;

/* Variables and functions */
 int DMA_BUS_MODE ; 
 size_t ETHTOOL_DMA_OFFSET ; 
 int NUM_DWMAC1000_DMA_REGS ; 
 int /*<<< orphan*/  REG_SPACE_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stmmac_dump_dma_regs (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_dump_mac_regs (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stmmac_ethtool_gregs(struct net_device *dev,
			  struct ethtool_regs *regs, void *space)
{
	u32 *reg_space = (u32 *) space;

	struct stmmac_priv *priv = netdev_priv(dev);

	memset(reg_space, 0x0, REG_SPACE_SIZE);

	stmmac_dump_mac_regs(priv, priv->hw, reg_space);
	stmmac_dump_dma_regs(priv, priv->ioaddr, reg_space);
	/* Copy DMA registers to where ethtool expects them */
	memcpy(&reg_space[ETHTOOL_DMA_OFFSET], &reg_space[DMA_BUS_MODE / 4],
	       NUM_DWMAC1000_DMA_REGS * 4);
}