#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct stmmac_priv {int clk_csr; scalar_t__ ioaddr; TYPE_2__* hw; } ;
struct net_device {int dummy; } ;
struct mii_bus {struct net_device* priv; } ;
struct TYPE_3__ {unsigned int addr; unsigned int data; int clk_csr_shift; int clk_csr_mask; } ;
struct TYPE_4__ {TYPE_1__ mii; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int MII_ADDR_C45 ; 
 int MII_XGMAC_BUSY ; 
 int MII_XGMAC_SADDR ; 
 int MII_XGMAC_WRITE ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 
 int stmmac_xgmac2_c22_format (struct stmmac_priv*,int,int,int*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int stmmac_xgmac2_mdio_write(struct mii_bus *bus, int phyaddr,
				    int phyreg, u16 phydata)
{
	struct net_device *ndev = bus->priv;
	struct stmmac_priv *priv = netdev_priv(ndev);
	unsigned int mii_address = priv->hw->mii.addr;
	unsigned int mii_data = priv->hw->mii.data;
	u32 addr, tmp, value = MII_XGMAC_BUSY;
	int ret;

	if (phyreg & MII_ADDR_C45) {
		return -EOPNOTSUPP;
	} else {
		ret = stmmac_xgmac2_c22_format(priv, phyaddr, phyreg, &addr);
		if (ret)
			return ret;
	}

	value |= (priv->clk_csr << priv->hw->mii.clk_csr_shift)
		& priv->hw->mii.clk_csr_mask;
	value |= phydata | MII_XGMAC_SADDR;
	value |= MII_XGMAC_WRITE;

	/* Wait until any existing MII operation is complete */
	if (readl_poll_timeout(priv->ioaddr + mii_data, tmp,
			       !(tmp & MII_XGMAC_BUSY), 100, 10000))
		return -EBUSY;

	/* Set the MII address register to write */
	writel(addr, priv->ioaddr + mii_address);
	writel(value, priv->ioaddr + mii_data);

	/* Wait until any existing MII operation is complete */
	return readl_poll_timeout(priv->ioaddr + mii_data, tmp,
				  !(tmp & MII_XGMAC_BUSY), 100, 10000);
}