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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct kirin_pcie {void* pcie_aclk; void* apb_sys_clk; void* apb_phy_clk; void* pcie_aux_clk; void* phy_ref_clk; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 long PTR_ERR (void*) ; 
 void* devm_clk_get (struct device*,char*) ; 

__attribute__((used)) static long kirin_pcie_get_clk(struct kirin_pcie *kirin_pcie,
			       struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;

	kirin_pcie->phy_ref_clk = devm_clk_get(dev, "pcie_phy_ref");
	if (IS_ERR(kirin_pcie->phy_ref_clk))
		return PTR_ERR(kirin_pcie->phy_ref_clk);

	kirin_pcie->pcie_aux_clk = devm_clk_get(dev, "pcie_aux");
	if (IS_ERR(kirin_pcie->pcie_aux_clk))
		return PTR_ERR(kirin_pcie->pcie_aux_clk);

	kirin_pcie->apb_phy_clk = devm_clk_get(dev, "pcie_apb_phy");
	if (IS_ERR(kirin_pcie->apb_phy_clk))
		return PTR_ERR(kirin_pcie->apb_phy_clk);

	kirin_pcie->apb_sys_clk = devm_clk_get(dev, "pcie_apb_sys");
	if (IS_ERR(kirin_pcie->apb_sys_clk))
		return PTR_ERR(kirin_pcie->apb_sys_clk);

	kirin_pcie->pcie_aclk = devm_clk_get(dev, "pcie_aclk");
	if (IS_ERR(kirin_pcie->pcie_aclk))
		return PTR_ERR(kirin_pcie->pcie_aclk);

	return 0;
}