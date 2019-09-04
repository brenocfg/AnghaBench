#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tegra_pcie_soc {scalar_t__ force_pca_enable; scalar_t__ has_pex_clkreq_en; } ;
struct tegra_pcie_port {scalar_t__ base; TYPE_1__* pcie; } ;
struct TYPE_3__ {struct tegra_pcie_soc* soc; } ;

/* Variables and functions */
 unsigned long AFI_PEX_CTRL_CLKREQ_EN ; 
 unsigned long AFI_PEX_CTRL_OVERRIDE_EN ; 
 unsigned long AFI_PEX_CTRL_REFCLK_EN ; 
 scalar_t__ RP_VEND_CTL2 ; 
 unsigned long RP_VEND_CTL2_PCA_ENABLE ; 
 unsigned long afi_readl (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  afi_writel (TYPE_1__*,unsigned long,unsigned long) ; 
 unsigned long readl (scalar_t__) ; 
 unsigned long tegra_pcie_port_get_pex_ctrl (struct tegra_pcie_port*) ; 
 int /*<<< orphan*/  tegra_pcie_port_reset (struct tegra_pcie_port*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void tegra_pcie_port_enable(struct tegra_pcie_port *port)
{
	unsigned long ctrl = tegra_pcie_port_get_pex_ctrl(port);
	const struct tegra_pcie_soc *soc = port->pcie->soc;
	unsigned long value;

	/* enable reference clock */
	value = afi_readl(port->pcie, ctrl);
	value |= AFI_PEX_CTRL_REFCLK_EN;

	if (soc->has_pex_clkreq_en)
		value |= AFI_PEX_CTRL_CLKREQ_EN;

	value |= AFI_PEX_CTRL_OVERRIDE_EN;

	afi_writel(port->pcie, value, ctrl);

	tegra_pcie_port_reset(port);

	if (soc->force_pca_enable) {
		value = readl(port->base + RP_VEND_CTL2);
		value |= RP_VEND_CTL2_PCA_ENABLE;
		writel(value, port->base + RP_VEND_CTL2);
	}
}