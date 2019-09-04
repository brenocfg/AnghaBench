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
typedef  int /*<<< orphan*/  u32 ;
struct qcom_pcie_resources_1_0_0 {int /*<<< orphan*/  core; int /*<<< orphan*/  aux; int /*<<< orphan*/  iface; int /*<<< orphan*/  master_bus; int /*<<< orphan*/  slave_bus; int /*<<< orphan*/  vdda; } ;
struct TYPE_2__ {struct qcom_pcie_resources_1_0_0 v1_0_0; } ;
struct qcom_pcie {scalar_t__ parf; struct dw_pcie* pci; TYPE_1__ res; } ;
struct dw_pcie {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ PCIE20_PARF_AXI_MSTR_WR_ADDR_HALT ; 
 scalar_t__ PCIE20_PARF_DBI_BASE_ADDR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int qcom_pcie_init_1_0_0(struct qcom_pcie *pcie)
{
	struct qcom_pcie_resources_1_0_0 *res = &pcie->res.v1_0_0;
	struct dw_pcie *pci = pcie->pci;
	struct device *dev = pci->dev;
	int ret;

	ret = reset_control_deassert(res->core);
	if (ret) {
		dev_err(dev, "cannot deassert core reset\n");
		return ret;
	}

	ret = clk_prepare_enable(res->aux);
	if (ret) {
		dev_err(dev, "cannot prepare/enable aux clock\n");
		goto err_res;
	}

	ret = clk_prepare_enable(res->iface);
	if (ret) {
		dev_err(dev, "cannot prepare/enable iface clock\n");
		goto err_aux;
	}

	ret = clk_prepare_enable(res->master_bus);
	if (ret) {
		dev_err(dev, "cannot prepare/enable master_bus clock\n");
		goto err_iface;
	}

	ret = clk_prepare_enable(res->slave_bus);
	if (ret) {
		dev_err(dev, "cannot prepare/enable slave_bus clock\n");
		goto err_master;
	}

	ret = regulator_enable(res->vdda);
	if (ret) {
		dev_err(dev, "cannot enable vdda regulator\n");
		goto err_slave;
	}

	/* change DBI base address */
	writel(0, pcie->parf + PCIE20_PARF_DBI_BASE_ADDR);

	if (IS_ENABLED(CONFIG_PCI_MSI)) {
		u32 val = readl(pcie->parf + PCIE20_PARF_AXI_MSTR_WR_ADDR_HALT);

		val |= BIT(31);
		writel(val, pcie->parf + PCIE20_PARF_AXI_MSTR_WR_ADDR_HALT);
	}

	return 0;
err_slave:
	clk_disable_unprepare(res->slave_bus);
err_master:
	clk_disable_unprepare(res->master_bus);
err_iface:
	clk_disable_unprepare(res->iface);
err_aux:
	clk_disable_unprepare(res->aux);
err_res:
	reset_control_assert(res->core);

	return ret;
}