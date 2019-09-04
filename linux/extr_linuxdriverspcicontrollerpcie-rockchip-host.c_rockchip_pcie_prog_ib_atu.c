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
typedef  int u8 ;
typedef  int u32 ;
struct rockchip_pcie {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_ROOT_PORT_REG_SIZE_SHIFT ; 
 int MAX_AXI_IB_ROOTPORT_REGION_NUM ; 
 int MIN_AXI_ADDR_BITS_PASSED ; 
 int PCIE_CORE_IB_REGION_ADDR0_LO_ADDR ; 
 int PCIE_CORE_IB_REGION_ADDR0_NUM_BITS ; 
 scalar_t__ PCIE_RP_IB_ADDR0 ; 
 scalar_t__ PCIE_RP_IB_ADDR1 ; 
 int /*<<< orphan*/  rockchip_pcie_write (struct rockchip_pcie*,int,scalar_t__) ; 

__attribute__((used)) static int rockchip_pcie_prog_ib_atu(struct rockchip_pcie *rockchip,
				     int region_no, u8 num_pass_bits,
				     u32 lower_addr, u32 upper_addr)
{
	u32 ib_addr_0;
	u32 ib_addr_1;
	u32 aw_offset;

	if (region_no > MAX_AXI_IB_ROOTPORT_REGION_NUM)
		return -EINVAL;
	if (num_pass_bits + 1 < MIN_AXI_ADDR_BITS_PASSED)
		return -EINVAL;
	if (num_pass_bits > 63)
		return -EINVAL;

	aw_offset = (region_no << IB_ROOT_PORT_REG_SIZE_SHIFT);

	ib_addr_0 = num_pass_bits & PCIE_CORE_IB_REGION_ADDR0_NUM_BITS;
	ib_addr_0 |= (lower_addr << 8) & PCIE_CORE_IB_REGION_ADDR0_LO_ADDR;
	ib_addr_1 = upper_addr;

	rockchip_pcie_write(rockchip, ib_addr_0, PCIE_RP_IB_ADDR0 + aw_offset);
	rockchip_pcie_write(rockchip, ib_addr_1, PCIE_RP_IB_ADDR1 + aw_offset);

	return 0;
}