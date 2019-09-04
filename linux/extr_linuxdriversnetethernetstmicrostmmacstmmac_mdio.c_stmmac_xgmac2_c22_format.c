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
struct stmmac_priv {scalar_t__ ioaddr; TYPE_2__* hw; } ;
struct TYPE_3__ {unsigned int data; } ;
struct TYPE_4__ {TYPE_1__ mii; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EBUSY ; 
 int ENODEV ; 
 int MII_XGMAC_BUSY ; 
 int MII_XGMAC_C22P_MASK ; 
 int MII_XGMAC_MAX_C22ADDR ; 
 scalar_t__ XGMAC_MDIO_C22P ; 
 int readl (scalar_t__) ; 
 scalar_t__ readl_poll_timeout (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int stmmac_xgmac2_c22_format(struct stmmac_priv *priv, int phyaddr,
				    int phyreg, u32 *hw_addr)
{
	unsigned int mii_data = priv->hw->mii.data;
	u32 tmp;

	/* HW does not support C22 addr >= 4 */
	if (phyaddr > MII_XGMAC_MAX_C22ADDR)
		return -ENODEV;
	/* Wait until any existing MII operation is complete */
	if (readl_poll_timeout(priv->ioaddr + mii_data, tmp,
			       !(tmp & MII_XGMAC_BUSY), 100, 10000))
		return -EBUSY;

	/* Set port as Clause 22 */
	tmp = readl(priv->ioaddr + XGMAC_MDIO_C22P);
	tmp &= ~MII_XGMAC_C22P_MASK;
	tmp |= BIT(phyaddr);
	writel(tmp, priv->ioaddr + XGMAC_MDIO_C22P);

	*hw_addr = (phyaddr << 16) | (phyreg & 0x1f);
	return 0;
}