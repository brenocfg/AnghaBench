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
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int RTL8366S_PHY_ACCESS_CTRL_REG ; 
 int /*<<< orphan*/  RTL8366S_PHY_ACCESS_DATA_REG ; 
 int RTL8366S_PHY_ADDR_MAX ; 
 int /*<<< orphan*/  RTL8366S_PHY_CTRL_READ ; 
 int RTL8366S_PHY_NO_MAX ; 
 int RTL8366S_PHY_NO_OFFSET ; 
 int RTL8366S_PHY_PAGE_MASK ; 
 int RTL8366S_PHY_PAGE_MAX ; 
 int RTL8366S_PHY_PAGE_OFFSET ; 
 int RTL8366S_PHY_REG_MASK ; 
 int rtl8366_smi_read_reg (struct rtl8366_smi*,int /*<<< orphan*/ ,int*) ; 
 int rtl8366_smi_write_reg (struct rtl8366_smi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8366s_read_phy_reg(struct rtl8366_smi *smi,
				 u32 phy_no, u32 page, u32 addr, u32 *data)
{
	u32 reg;
	int ret;

	if (phy_no > RTL8366S_PHY_NO_MAX)
		return -EINVAL;

	if (page > RTL8366S_PHY_PAGE_MAX)
		return -EINVAL;

	if (addr > RTL8366S_PHY_ADDR_MAX)
		return -EINVAL;

	ret = rtl8366_smi_write_reg(smi, RTL8366S_PHY_ACCESS_CTRL_REG,
				    RTL8366S_PHY_CTRL_READ);
	if (ret)
		return ret;

	reg = 0x8000 | (1 << (phy_no + RTL8366S_PHY_NO_OFFSET)) |
	      ((page << RTL8366S_PHY_PAGE_OFFSET) & RTL8366S_PHY_PAGE_MASK) |
	      (addr & RTL8366S_PHY_REG_MASK);

	ret = rtl8366_smi_write_reg(smi, reg, 0);
	if (ret)
		return ret;

	ret = rtl8366_smi_read_reg(smi, RTL8366S_PHY_ACCESS_DATA_REG, data);
	if (ret)
		return ret;

	return 0;
}