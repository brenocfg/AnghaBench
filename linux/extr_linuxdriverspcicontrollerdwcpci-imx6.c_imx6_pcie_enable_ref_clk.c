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
struct imx6_pcie {int variant; int /*<<< orphan*/  iomuxc_gpr; int /*<<< orphan*/  pcie_inbound_axi; struct dw_pcie* pci; } ;
struct dw_pcie {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  IMX6Q 131 
#define  IMX6QP 130 
 int /*<<< orphan*/  IMX6Q_GPR1_PCIE_REF_CLK_EN ; 
 int /*<<< orphan*/  IMX6Q_GPR1_PCIE_TEST_PD ; 
#define  IMX6SX 129 
 int /*<<< orphan*/  IMX6SX_GPR12_PCIE_TEST_POWERDOWN ; 
#define  IMX7D 128 
 int /*<<< orphan*/  IOMUXC_GPR1 ; 
 int /*<<< orphan*/  IOMUXC_GPR12 ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int imx6_pcie_enable_ref_clk(struct imx6_pcie *imx6_pcie)
{
	struct dw_pcie *pci = imx6_pcie->pci;
	struct device *dev = pci->dev;
	int ret = 0;

	switch (imx6_pcie->variant) {
	case IMX6SX:
		ret = clk_prepare_enable(imx6_pcie->pcie_inbound_axi);
		if (ret) {
			dev_err(dev, "unable to enable pcie_axi clock\n");
			break;
		}

		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX6SX_GPR12_PCIE_TEST_POWERDOWN, 0);
		break;
	case IMX6QP:		/* FALLTHROUGH */
	case IMX6Q:
		/* power up core phy and enable ref clock */
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR1,
				   IMX6Q_GPR1_PCIE_TEST_PD, 0 << 18);
		/*
		 * the async reset input need ref clock to sync internally,
		 * when the ref clock comes after reset, internal synced
		 * reset time is too short, cannot meet the requirement.
		 * add one ~10us delay here.
		 */
		udelay(10);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR1,
				   IMX6Q_GPR1_PCIE_REF_CLK_EN, 1 << 16);
		break;
	case IMX7D:
		break;
	}

	return ret;
}