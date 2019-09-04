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
struct qcom_pcie_resources_2_4_0 {void* phy_ahb_reset; void* ahb_reset; void* pwr_reset; void* pipe_sticky_reset; void* axi_m_sticky_reset; void* phy_reset; void* parf_reset; void* axi_s_xpu_reset; void* axi_m_vmid_reset; void* pipe_reset; void* axi_s_reset; void* axi_m_reset; void* slave_clk; void* master_clk; void* aux_clk; } ;
struct TYPE_2__ {struct qcom_pcie_resources_2_4_0 v2_4_0; } ;
struct qcom_pcie {struct dw_pcie* pci; TYPE_1__ res; } ;
struct dw_pcie {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_reset_control_get_exclusive (struct device*,char*) ; 

__attribute__((used)) static int qcom_pcie_get_resources_2_4_0(struct qcom_pcie *pcie)
{
	struct qcom_pcie_resources_2_4_0 *res = &pcie->res.v2_4_0;
	struct dw_pcie *pci = pcie->pci;
	struct device *dev = pci->dev;

	res->aux_clk = devm_clk_get(dev, "aux");
	if (IS_ERR(res->aux_clk))
		return PTR_ERR(res->aux_clk);

	res->master_clk = devm_clk_get(dev, "master_bus");
	if (IS_ERR(res->master_clk))
		return PTR_ERR(res->master_clk);

	res->slave_clk = devm_clk_get(dev, "slave_bus");
	if (IS_ERR(res->slave_clk))
		return PTR_ERR(res->slave_clk);

	res->axi_m_reset = devm_reset_control_get_exclusive(dev, "axi_m");
	if (IS_ERR(res->axi_m_reset))
		return PTR_ERR(res->axi_m_reset);

	res->axi_s_reset = devm_reset_control_get_exclusive(dev, "axi_s");
	if (IS_ERR(res->axi_s_reset))
		return PTR_ERR(res->axi_s_reset);

	res->pipe_reset = devm_reset_control_get_exclusive(dev, "pipe");
	if (IS_ERR(res->pipe_reset))
		return PTR_ERR(res->pipe_reset);

	res->axi_m_vmid_reset = devm_reset_control_get_exclusive(dev,
								 "axi_m_vmid");
	if (IS_ERR(res->axi_m_vmid_reset))
		return PTR_ERR(res->axi_m_vmid_reset);

	res->axi_s_xpu_reset = devm_reset_control_get_exclusive(dev,
								"axi_s_xpu");
	if (IS_ERR(res->axi_s_xpu_reset))
		return PTR_ERR(res->axi_s_xpu_reset);

	res->parf_reset = devm_reset_control_get_exclusive(dev, "parf");
	if (IS_ERR(res->parf_reset))
		return PTR_ERR(res->parf_reset);

	res->phy_reset = devm_reset_control_get_exclusive(dev, "phy");
	if (IS_ERR(res->phy_reset))
		return PTR_ERR(res->phy_reset);

	res->axi_m_sticky_reset = devm_reset_control_get_exclusive(dev,
								   "axi_m_sticky");
	if (IS_ERR(res->axi_m_sticky_reset))
		return PTR_ERR(res->axi_m_sticky_reset);

	res->pipe_sticky_reset = devm_reset_control_get_exclusive(dev,
								  "pipe_sticky");
	if (IS_ERR(res->pipe_sticky_reset))
		return PTR_ERR(res->pipe_sticky_reset);

	res->pwr_reset = devm_reset_control_get_exclusive(dev, "pwr");
	if (IS_ERR(res->pwr_reset))
		return PTR_ERR(res->pwr_reset);

	res->ahb_reset = devm_reset_control_get_exclusive(dev, "ahb");
	if (IS_ERR(res->ahb_reset))
		return PTR_ERR(res->ahb_reset);

	res->phy_ahb_reset = devm_reset_control_get_exclusive(dev, "phy_ahb");
	if (IS_ERR(res->phy_ahb_reset))
		return PTR_ERR(res->phy_ahb_reset);

	return 0;
}