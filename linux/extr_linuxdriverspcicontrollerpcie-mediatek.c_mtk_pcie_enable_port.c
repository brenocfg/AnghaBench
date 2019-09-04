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
struct mtk_pcie_port {int /*<<< orphan*/  sys_ck; int /*<<< orphan*/  ahb_ck; int /*<<< orphan*/  aux_ck; int /*<<< orphan*/  axi_ck; int /*<<< orphan*/  obff_ck; int /*<<< orphan*/  pipe_ck; int /*<<< orphan*/  phy; int /*<<< orphan*/  slot; int /*<<< orphan*/  reset; struct mtk_pcie* pcie; } ;
struct mtk_pcie {TYPE_1__* soc; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* startup ) (struct mtk_pcie_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_pcie_port_free (struct mtk_pcie_port*) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int phy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mtk_pcie_port*) ; 

__attribute__((used)) static void mtk_pcie_enable_port(struct mtk_pcie_port *port)
{
	struct mtk_pcie *pcie = port->pcie;
	struct device *dev = pcie->dev;
	int err;

	err = clk_prepare_enable(port->sys_ck);
	if (err) {
		dev_err(dev, "failed to enable sys_ck%d clock\n", port->slot);
		goto err_sys_clk;
	}

	err = clk_prepare_enable(port->ahb_ck);
	if (err) {
		dev_err(dev, "failed to enable ahb_ck%d\n", port->slot);
		goto err_ahb_clk;
	}

	err = clk_prepare_enable(port->aux_ck);
	if (err) {
		dev_err(dev, "failed to enable aux_ck%d\n", port->slot);
		goto err_aux_clk;
	}

	err = clk_prepare_enable(port->axi_ck);
	if (err) {
		dev_err(dev, "failed to enable axi_ck%d\n", port->slot);
		goto err_axi_clk;
	}

	err = clk_prepare_enable(port->obff_ck);
	if (err) {
		dev_err(dev, "failed to enable obff_ck%d\n", port->slot);
		goto err_obff_clk;
	}

	err = clk_prepare_enable(port->pipe_ck);
	if (err) {
		dev_err(dev, "failed to enable pipe_ck%d\n", port->slot);
		goto err_pipe_clk;
	}

	reset_control_assert(port->reset);
	reset_control_deassert(port->reset);

	err = phy_init(port->phy);
	if (err) {
		dev_err(dev, "failed to initialize port%d phy\n", port->slot);
		goto err_phy_init;
	}

	err = phy_power_on(port->phy);
	if (err) {
		dev_err(dev, "failed to power on port%d phy\n", port->slot);
		goto err_phy_on;
	}

	if (!pcie->soc->startup(port))
		return;

	dev_info(dev, "Port%d link down\n", port->slot);

	phy_power_off(port->phy);
err_phy_on:
	phy_exit(port->phy);
err_phy_init:
	clk_disable_unprepare(port->pipe_ck);
err_pipe_clk:
	clk_disable_unprepare(port->obff_ck);
err_obff_clk:
	clk_disable_unprepare(port->axi_ck);
err_axi_clk:
	clk_disable_unprepare(port->aux_ck);
err_aux_clk:
	clk_disable_unprepare(port->ahb_ck);
err_ahb_clk:
	clk_disable_unprepare(port->sys_ck);
err_sys_clk:
	mtk_pcie_port_free(port);
}