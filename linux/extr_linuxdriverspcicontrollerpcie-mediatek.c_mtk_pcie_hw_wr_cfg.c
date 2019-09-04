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
struct mtk_pcie_port {scalar_t__ base; } ;

/* Variables and functions */
 int APP_CFG_REQ ; 
 int CFG_HEADER_DW0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CFG_HEADER_DW1 (int,int) ; 
 int CFG_HEADER_DW2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CFG_WRRD_TYPE_0 ; 
 int /*<<< orphan*/  CFG_WR_FMT ; 
 scalar_t__ PCIE_APP_TLP_REQ ; 
 scalar_t__ PCIE_CFG_HEADER0 ; 
 scalar_t__ PCIE_CFG_HEADER1 ; 
 scalar_t__ PCIE_CFG_HEADER2 ; 
 scalar_t__ PCIE_CFG_WDATA ; 
 int /*<<< orphan*/  PCI_FUNC (int) ; 
 int /*<<< orphan*/  PCI_SLOT (int) ; 
 int mtk_pcie_check_cfg_cpld (struct mtk_pcie_port*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtk_pcie_hw_wr_cfg(struct mtk_pcie_port *port, u32 bus, u32 devfn,
			      int where, int size, u32 val)
{
	/* Write PCIe configuration transaction header for Cfgwr */
	writel(CFG_HEADER_DW0(CFG_WRRD_TYPE_0, CFG_WR_FMT),
	       port->base + PCIE_CFG_HEADER0);
	writel(CFG_HEADER_DW1(where, size), port->base + PCIE_CFG_HEADER1);
	writel(CFG_HEADER_DW2(where, PCI_FUNC(devfn), PCI_SLOT(devfn), bus),
	       port->base + PCIE_CFG_HEADER2);

	/* Write Cfgwr data */
	val = val << 8 * (where & 3);
	writel(val, port->base + PCIE_CFG_WDATA);

	/* Trigger h/w to transmit Cfgwr TLP */
	val = readl(port->base + PCIE_APP_TLP_REQ);
	val |= APP_CFG_REQ;
	writel(val, port->base + PCIE_APP_TLP_REQ);

	/* Check completion status */
	return mtk_pcie_check_cfg_cpld(port);
}