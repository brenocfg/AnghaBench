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
typedef  scalar_t__ u32 ;
struct rtl8366_smi {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  REG_RD (struct rtl8366_smi*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  REG_WR (struct rtl8366_smi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL8367B_IA_ADDRESS_REG ; 
 int RTL8367B_IA_CTRL_CMD_MASK ; 
 int /*<<< orphan*/  RTL8367B_IA_CTRL_REG ; 
 int RTL8367B_IA_CTRL_RW_READ ; 
 int /*<<< orphan*/  RTL8367B_IA_READ_DATA_REG ; 
 scalar_t__ RTL8367B_IA_STATUS_PHY_BUSY ; 
 int /*<<< orphan*/  RTL8367B_IA_STATUS_REG ; 
 int RTL8367B_INTERNAL_PHY_REG (scalar_t__,scalar_t__) ; 
 scalar_t__ RTL8367B_PHY_ADDR_MAX ; 
 scalar_t__ RTL8367B_PHY_REG_MAX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rtl8367b_read_phy_reg(struct rtl8366_smi *smi,
				u32 phy_addr, u32 phy_reg, u32 *val)
{
	int timeout;
	u32 data;
	int err;

	if (phy_addr > RTL8367B_PHY_ADDR_MAX)
		return -EINVAL;

	if (phy_reg > RTL8367B_PHY_REG_MAX)
		return -EINVAL;

	REG_RD(smi, RTL8367B_IA_STATUS_REG, &data);
	if (data & RTL8367B_IA_STATUS_PHY_BUSY)
		return -ETIMEDOUT;

	/* prepare address */
	REG_WR(smi, RTL8367B_IA_ADDRESS_REG,
	       RTL8367B_INTERNAL_PHY_REG(phy_addr, phy_reg));

	/* send read command */
	REG_WR(smi, RTL8367B_IA_CTRL_REG,
	       RTL8367B_IA_CTRL_CMD_MASK | RTL8367B_IA_CTRL_RW_READ);

	timeout = 5;
	do {
		REG_RD(smi, RTL8367B_IA_STATUS_REG, &data);
		if ((data & RTL8367B_IA_STATUS_PHY_BUSY) == 0)
			break;

		if (timeout--) {
			dev_err(smi->parent, "phy read timed out\n");
			return -ETIMEDOUT;
		}

		udelay(1);
	} while (1);

	/* read data */
	REG_RD(smi, RTL8367B_IA_READ_DATA_REG, val);

	dev_dbg(smi->parent, "phy_read: addr:%02x, reg:%02x, val:%04x\n",
		phy_addr, phy_reg, *val);
	return 0;
}