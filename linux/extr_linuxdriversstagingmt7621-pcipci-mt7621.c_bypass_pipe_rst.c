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
struct mt7621_pcie {int dummy; } ;

/* Variables and functions */
 scalar_t__ RALINK_PCIEPHY_P0P1_CTL_OFFSET ; 
 scalar_t__ RALINK_PCIEPHY_P2_CTL_OFFSET ; 
 int /*<<< orphan*/  set_pcie_phy (struct mt7621_pcie*,scalar_t__,int,int,int) ; 

void
bypass_pipe_rst(struct mt7621_pcie *pcie)
{
	/* PCIe Port 0 */
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x02c), 12, 1, 0x01);	// rg_pe1_pipe_rst_b
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x02c),  4, 1, 0x01);	// rg_pe1_pipe_cmd_frc[4]
	/* PCIe Port 1 */
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x12c), 12, 1, 0x01);	// rg_pe1_pipe_rst_b
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P0P1_CTL_OFFSET + 0x12c),  4, 1, 0x01);	// rg_pe1_pipe_cmd_frc[4]
	/* PCIe Port 2 */
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x02c), 12, 1, 0x01);	// rg_pe1_pipe_rst_b
	set_pcie_phy(pcie, (RALINK_PCIEPHY_P2_CTL_OFFSET + 0x02c),  4, 1, 0x01);	// rg_pe1_pipe_cmd_frc[4]
}