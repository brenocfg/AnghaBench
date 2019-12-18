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
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int RTL8366S_NUM_PORTS ; 
 int /*<<< orphan*/  RTL8366S_PHY_POWER_SAVING_CTRL_REG ; 
 int /*<<< orphan*/  RTL8366S_PHY_POWER_SAVING_MASK ; 
 int rtl8366s_read_phy_reg (struct rtl8366_smi*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rtl8366s_write_phy_reg (struct rtl8366_smi*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8366s_set_green_port(struct rtl8366_smi *smi, int port, int enable)
{
	int err;
	u32 phyData;

	if (port >= RTL8366S_NUM_PORTS)
		return -EINVAL;

	err = rtl8366s_read_phy_reg(smi, port, 0, RTL8366S_PHY_POWER_SAVING_CTRL_REG, &phyData);
	if (err)
		return err;

	if (enable)
		phyData |= RTL8366S_PHY_POWER_SAVING_MASK;
	else
		phyData &= ~RTL8366S_PHY_POWER_SAVING_MASK;

	err = rtl8366s_write_phy_reg(smi, port, 0, RTL8366S_PHY_POWER_SAVING_CTRL_REG, phyData);
	if (err)
		return err;

	return 0;
}