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
struct dw_pcie {struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_LINK_WIDTH_SPEED_CONTROL ; 
 int /*<<< orphan*/  PCIE_PORT_LINK_CONTROL ; 
 int PORT_LINK_MODE_1_LANES ; 
 int PORT_LINK_MODE_2_LANES ; 
 int PORT_LINK_MODE_4_LANES ; 
 int PORT_LINK_MODE_8_LANES ; 
 int PORT_LINK_MODE_MASK ; 
 int PORT_LOGIC_LINK_WIDTH_1_LANES ; 
 int PORT_LOGIC_LINK_WIDTH_2_LANES ; 
 int PORT_LOGIC_LINK_WIDTH_4_LANES ; 
 int PORT_LOGIC_LINK_WIDTH_8_LANES ; 
 int PORT_LOGIC_LINK_WIDTH_MASK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int dw_pcie_readl_dbi (struct dw_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_pcie_writel_dbi (struct dw_pcie*,int /*<<< orphan*/ ,int) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 

void dw_pcie_setup(struct dw_pcie *pci)
{
	int ret;
	u32 val;
	u32 lanes;
	struct device *dev = pci->dev;
	struct device_node *np = dev->of_node;

	ret = of_property_read_u32(np, "num-lanes", &lanes);
	if (ret)
		lanes = 0;

	/* Set the number of lanes */
	val = dw_pcie_readl_dbi(pci, PCIE_PORT_LINK_CONTROL);
	val &= ~PORT_LINK_MODE_MASK;
	switch (lanes) {
	case 1:
		val |= PORT_LINK_MODE_1_LANES;
		break;
	case 2:
		val |= PORT_LINK_MODE_2_LANES;
		break;
	case 4:
		val |= PORT_LINK_MODE_4_LANES;
		break;
	case 8:
		val |= PORT_LINK_MODE_8_LANES;
		break;
	default:
		dev_err(pci->dev, "num-lanes %u: invalid value\n", lanes);
		return;
	}
	dw_pcie_writel_dbi(pci, PCIE_PORT_LINK_CONTROL, val);

	/* Set link width speed control register */
	val = dw_pcie_readl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL);
	val &= ~PORT_LOGIC_LINK_WIDTH_MASK;
	switch (lanes) {
	case 1:
		val |= PORT_LOGIC_LINK_WIDTH_1_LANES;
		break;
	case 2:
		val |= PORT_LOGIC_LINK_WIDTH_2_LANES;
		break;
	case 4:
		val |= PORT_LOGIC_LINK_WIDTH_4_LANES;
		break;
	case 8:
		val |= PORT_LOGIC_LINK_WIDTH_8_LANES;
		break;
	}
	dw_pcie_writel_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL, val);
}