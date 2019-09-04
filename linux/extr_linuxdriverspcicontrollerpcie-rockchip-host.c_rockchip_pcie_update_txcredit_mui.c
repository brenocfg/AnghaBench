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
struct rockchip_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_CORE_TXCREDIT_CFG1 ; 
 int /*<<< orphan*/  PCIE_CORE_TXCREDIT_CFG1_MUI_ENCODE (int) ; 
 int /*<<< orphan*/  PCIE_CORE_TXCREDIT_CFG1_MUI_MASK ; 
 int /*<<< orphan*/  rockchip_pcie_read (struct rockchip_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rockchip_pcie_write (struct rockchip_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rockchip_pcie_update_txcredit_mui(struct rockchip_pcie *rockchip)
{
	u32 val;

	/* Update Tx credit maximum update interval */
	val = rockchip_pcie_read(rockchip, PCIE_CORE_TXCREDIT_CFG1);
	val &= ~PCIE_CORE_TXCREDIT_CFG1_MUI_MASK;
	val |= PCIE_CORE_TXCREDIT_CFG1_MUI_ENCODE(24000);	/* ns */
	rockchip_pcie_write(rockchip, val, PCIE_CORE_TXCREDIT_CFG1);
}