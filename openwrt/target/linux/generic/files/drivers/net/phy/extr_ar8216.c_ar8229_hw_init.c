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
struct ar8xxx_priv {int initialized; scalar_t__ port4_phy; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8216_CTRL_RESET ; 
 int /*<<< orphan*/  AR8216_REG_CTRL ; 
 int /*<<< orphan*/  AR8216_REG_PORT_STATUS (int) ; 
 int /*<<< orphan*/  AR8229_OPER_MODE0_MAC_GMII_EN ; 
 int /*<<< orphan*/  AR8229_OPER_MODE0_PHY_MII_EN ; 
 int /*<<< orphan*/  AR8229_REG_OPER_MODE0 ; 
 int /*<<< orphan*/  AR8229_REG_OPER_MODE1 ; 
 int /*<<< orphan*/  AR8229_REG_OPER_MODE1_PHY4_MII_EN ; 
 int EINVAL ; 
 int PHY_INTERFACE_MODE_GMII ; 
 int PHY_INTERFACE_MODE_MII ; 
 int /*<<< orphan*/  ar8xxx_phy_init (struct ar8xxx_priv*) ; 
 int /*<<< orphan*/  ar8xxx_reg_wait (struct ar8xxx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar8xxx_write (struct ar8xxx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int of_get_phy_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int
ar8229_hw_init(struct ar8xxx_priv *priv)
{
	int phy_if_mode;

	if (priv->initialized)
		return 0;

	ar8xxx_write(priv, AR8216_REG_CTRL, AR8216_CTRL_RESET);
	ar8xxx_reg_wait(priv, AR8216_REG_CTRL, AR8216_CTRL_RESET, 0, 1000);

	phy_if_mode = of_get_phy_mode(priv->pdev->of_node);

	if (phy_if_mode == PHY_INTERFACE_MODE_GMII) {
		ar8xxx_write(priv, AR8229_REG_OPER_MODE0,
				 AR8229_OPER_MODE0_MAC_GMII_EN);
	} else if (phy_if_mode == PHY_INTERFACE_MODE_MII) {
		ar8xxx_write(priv, AR8229_REG_OPER_MODE0,
				 AR8229_OPER_MODE0_PHY_MII_EN);
	} else {
		pr_err("ar8229: unsupported mii mode\n");
		return -EINVAL;
	}

	if (priv->port4_phy) {
		ar8xxx_write(priv, AR8229_REG_OPER_MODE1,
			     AR8229_REG_OPER_MODE1_PHY4_MII_EN);
		/* disable port5 to prevent mii conflict */
		ar8xxx_write(priv, AR8216_REG_PORT_STATUS(5), 0);
	}

	ar8xxx_phy_init(priv);

	priv->initialized = true;
	return 0;
}