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
struct mvebu_pcie_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_CMD_OFF ; 
 int /*<<< orphan*/  PCIE_MASK_ENABLE_INTS ; 
 int /*<<< orphan*/  PCIE_MASK_OFF ; 
 int /*<<< orphan*/  PCI_COMMAND_IO ; 
 int /*<<< orphan*/  PCI_COMMAND_MASTER ; 
 int /*<<< orphan*/  PCI_COMMAND_MEMORY ; 
 int /*<<< orphan*/  mvebu_pcie_setup_wins (struct mvebu_pcie_port*) ; 
 int /*<<< orphan*/  mvebu_readl (struct mvebu_pcie_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvebu_writel (struct mvebu_pcie_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvebu_pcie_setup_hw(struct mvebu_pcie_port *port)
{
	u32 cmd, mask;

	/* Point PCIe unit MBUS decode windows to DRAM space. */
	mvebu_pcie_setup_wins(port);

	/* Master + slave enable. */
	cmd = mvebu_readl(port, PCIE_CMD_OFF);
	cmd |= PCI_COMMAND_IO;
	cmd |= PCI_COMMAND_MEMORY;
	cmd |= PCI_COMMAND_MASTER;
	mvebu_writel(port, cmd, PCIE_CMD_OFF);

	/* Enable interrupt lines A-D. */
	mask = mvebu_readl(port, PCIE_MASK_OFF);
	mask |= PCIE_MASK_ENABLE_INTS;
	mvebu_writel(port, mask, PCIE_MASK_OFF);
}