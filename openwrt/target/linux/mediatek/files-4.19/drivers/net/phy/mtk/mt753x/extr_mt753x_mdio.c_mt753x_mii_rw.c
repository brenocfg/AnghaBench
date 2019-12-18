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
struct gsw_mt753x {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int MDIO_CMD_ADDR ; 
 int MDIO_CMD_M ; 
 int MDIO_CMD_READ ; 
 int MDIO_CMD_READ_C45 ; 
 int MDIO_CMD_S ; 
 int MDIO_CMD_WRITE ; 
 int MDIO_PHY_ADDR_M ; 
 int MDIO_PHY_ADDR_S ; 
 int MDIO_REG_ADDR_M ; 
 int MDIO_REG_ADDR_S ; 
 int MDIO_RW_DATA_M ; 
 int MDIO_ST_S ; 
 int PHY_ACS_ST ; 
 int /*<<< orphan*/  PHY_IAC ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ktime_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int mt753x_reg_read (struct gsw_mt753x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt753x_reg_write (struct gsw_mt753x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt753x_mii_rw(struct gsw_mt753x *gsw, int phy, int reg, u16 data,
			 u32 cmd, u32 st)
{
	ktime_t timeout;
	u32 val, timeout_us;
	int ret = 0;

	timeout_us = 100000;
	timeout = ktime_add_us(ktime_get(), timeout_us);
	while (1) {
		val = mt753x_reg_read(gsw, PHY_IAC);

		if ((val & PHY_ACS_ST) == 0)
			break;

		if (ktime_compare(ktime_get(), timeout) > 0)
			return -ETIMEDOUT;
	}

	val = (st << MDIO_ST_S) |
	      ((cmd << MDIO_CMD_S) & MDIO_CMD_M) |
	      ((phy << MDIO_PHY_ADDR_S) & MDIO_PHY_ADDR_M) |
	      ((reg << MDIO_REG_ADDR_S) & MDIO_REG_ADDR_M);

	if (cmd == MDIO_CMD_WRITE || cmd == MDIO_CMD_ADDR)
		val |= data & MDIO_RW_DATA_M;

	mt753x_reg_write(gsw, PHY_IAC, val | PHY_ACS_ST);

	timeout_us = 100000;
	timeout = ktime_add_us(ktime_get(), timeout_us);
	while (1) {
		val = mt753x_reg_read(gsw, PHY_IAC);

		if ((val & PHY_ACS_ST) == 0)
			break;

		if (ktime_compare(ktime_get(), timeout) > 0)
			return -ETIMEDOUT;
	}

	if (cmd == MDIO_CMD_READ || cmd == MDIO_CMD_READ_C45) {
		val = mt753x_reg_read(gsw, PHY_IAC);
		ret = val & MDIO_RW_DATA_M;
	}

	return ret;
}