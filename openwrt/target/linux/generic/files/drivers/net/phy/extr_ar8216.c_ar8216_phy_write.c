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
struct ar8xxx_priv {int dummy; } ;

/* Variables and functions */
 int AR8216_MDIO_CTRL_BUSY ; 
 int AR8216_MDIO_CTRL_CMD_WRITE ; 
 int AR8216_MDIO_CTRL_MASTER_EN ; 
 int AR8216_MDIO_CTRL_PHY_ADDR_S ; 
 int AR8216_MDIO_CTRL_REG_ADDR_S ; 
 int AR8216_NUM_PORTS ; 
 int /*<<< orphan*/  AR8216_REG_MDIO_CTRL ; 
 int EINVAL ; 
 int ar8xxx_reg_wait (struct ar8xxx_priv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar8xxx_write (struct ar8xxx_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ar8216_phy_write(struct ar8xxx_priv *priv, int addr, int regnum, u16 val)
{
	u32 t;
	int ret;

	if (addr >= AR8216_NUM_PORTS)
		return -EINVAL;

	t = (addr << AR8216_MDIO_CTRL_PHY_ADDR_S) |
	    (regnum << AR8216_MDIO_CTRL_REG_ADDR_S) |
	    AR8216_MDIO_CTRL_MASTER_EN |
	    AR8216_MDIO_CTRL_BUSY |
	    AR8216_MDIO_CTRL_CMD_WRITE |
	    val;

	ar8xxx_write(priv, AR8216_REG_MDIO_CTRL, t);
	ret = ar8xxx_reg_wait(priv, AR8216_REG_MDIO_CTRL,
			      AR8216_MDIO_CTRL_BUSY, 0, 5);

	return ret;
}