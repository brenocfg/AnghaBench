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
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct tegra_pcie_port {int /*<<< orphan*/  list; TYPE_1__ regs; int /*<<< orphan*/  base; struct tegra_pcie* pcie; } ;
struct tegra_pcie {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_iounmap (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct tegra_pcie_port*) ; 
 int /*<<< orphan*/  devm_release_mem_region (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 

__attribute__((used)) static void tegra_pcie_port_free(struct tegra_pcie_port *port)
{
	struct tegra_pcie *pcie = port->pcie;
	struct device *dev = pcie->dev;

	devm_iounmap(dev, port->base);
	devm_release_mem_region(dev, port->regs.start,
				resource_size(&port->regs));
	list_del(&port->list);
	devm_kfree(dev, port);
}