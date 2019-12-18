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
typedef  int u32 ;
struct TYPE_2__ {int i; } ;
struct switch_val {TYPE_1__ value; int /*<<< orphan*/  port_vlan; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RTL8366S_NUM_PORTS ; 
 int /*<<< orphan*/  RTL8366S_PHY_POWER_SAVING_CTRL_REG ; 
 int RTL8366S_PHY_POWER_SAVING_MASK ; 
 int rtl8366s_read_phy_reg (struct rtl8366_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct rtl8366_smi* sw_to_rtl8366_smi (struct switch_dev*) ; 

__attribute__((used)) static int rtl8366s_sw_get_green_port(struct switch_dev *dev,
				      const struct switch_attr *attr,
				      struct switch_val *val)
{
	struct rtl8366_smi *smi = sw_to_rtl8366_smi(dev);
	int err;
	u32 phyData;

	if (val->port_vlan >= RTL8366S_NUM_PORTS)
		return -EINVAL;

	err = rtl8366s_read_phy_reg(smi, val->port_vlan, 0, RTL8366S_PHY_POWER_SAVING_CTRL_REG, &phyData);
	if (err)
		return err;

	val->value.i = ((phyData & RTL8366S_PHY_POWER_SAVING_MASK) != 0) ? 1 : 0;

	return 0;
}