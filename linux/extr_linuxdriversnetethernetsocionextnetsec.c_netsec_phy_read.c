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
struct netsec_priv {int /*<<< orphan*/  freq; } ;
struct mii_bus {struct netsec_priv* priv; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GMAC_REG_GAR ; 
 int /*<<< orphan*/  GMAC_REG_GDR ; 
 int GMAC_REG_SHIFT_CR_GAR ; 
 int NETSEC_GMAC_GAR_REG_GB ; 
 int NETSEC_GMAC_GAR_REG_SHIFT_GR ; 
 int NETSEC_GMAC_GAR_REG_SHIFT_PA ; 
 int netsec_clk_type (int /*<<< orphan*/ ) ; 
 int netsec_mac_read (struct netsec_priv*,int /*<<< orphan*/ ,int*) ; 
 int netsec_mac_wait_while_busy (struct netsec_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netsec_mac_write (struct netsec_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int netsec_phy_read(struct mii_bus *bus, int phy_addr, int reg_addr)
{
	struct netsec_priv *priv = bus->priv;
	u32 data;
	int ret;

	if (netsec_mac_write(priv, GMAC_REG_GAR, NETSEC_GMAC_GAR_REG_GB |
			     phy_addr << NETSEC_GMAC_GAR_REG_SHIFT_PA |
			     reg_addr << NETSEC_GMAC_GAR_REG_SHIFT_GR |
			     (netsec_clk_type(priv->freq) <<
			      GMAC_REG_SHIFT_CR_GAR)))
		return -ETIMEDOUT;

	ret = netsec_mac_wait_while_busy(priv, GMAC_REG_GAR,
					 NETSEC_GMAC_GAR_REG_GB);
	if (ret)
		return ret;

	ret = netsec_mac_read(priv, GMAC_REG_GDR, &data);
	if (ret)
		return ret;

	return data;
}