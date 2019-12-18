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
struct ar8xxx_priv {int initialized; int port4_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8216_CTRL_RESET ; 
 int /*<<< orphan*/  AR8216_REG_CTRL ; 
 int /*<<< orphan*/  AR8216_REG_PORT_STATUS (int) ; 
 int /*<<< orphan*/  ar8xxx_phy_init (struct ar8xxx_priv*) ; 
 int /*<<< orphan*/  ar8xxx_reg_wait (struct ar8xxx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar8xxx_write (struct ar8xxx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar7240sw_hw_init(struct ar8xxx_priv *priv)
{
	if (priv->initialized)
		return 0;

	ar8xxx_write(priv, AR8216_REG_CTRL, AR8216_CTRL_RESET);
	ar8xxx_reg_wait(priv, AR8216_REG_CTRL, AR8216_CTRL_RESET, 0, 1000);

	priv->port4_phy = 1;
	/* disable port5 to prevent mii conflict */
	ar8xxx_write(priv, AR8216_REG_PORT_STATUS(5), 0);

	ar8xxx_phy_init(priv);

	priv->initialized = true;
	return 0;
}