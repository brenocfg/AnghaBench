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
typedef  int u16 ;
struct unimac_mdio_priv {int (* wait_func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  wait_func_data; } ;
struct mii_bus {struct unimac_mdio_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_CMD ; 
 int MDIO_PMD_SHIFT ; 
 int MDIO_REG_SHIFT ; 
 int MDIO_WR ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unimac_mdio_start (struct unimac_mdio_priv*) ; 
 int /*<<< orphan*/  unimac_mdio_writel (struct unimac_mdio_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unimac_mdio_write(struct mii_bus *bus, int phy_id,
			     int reg, u16 val)
{
	struct unimac_mdio_priv *priv = bus->priv;
	u32 cmd;

	/* Prepare the write operation */
	cmd = MDIO_WR | (phy_id << MDIO_PMD_SHIFT) |
		(reg << MDIO_REG_SHIFT) | (0xffff & val);
	unimac_mdio_writel(priv, cmd, MDIO_CMD);

	unimac_mdio_start(priv);

	return priv->wait_func(priv->wait_func_data);
}