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
struct rockchip_pcie {int lanes; int link_gen; void* clk_pcie_pm; void* hclk_pcie; void* aclk_perf_pcie; void* aclk_pcie; void* ep_gpio; scalar_t__ is_rc; void* aclk_rst; void* pclk_rst; void* pm_rst; void* pipe_rst; void* mgmt_sticky_rst; void* mgmt_rst; void* core_rst; void* apb_base; void* mem_res; void* reg_base; struct device* dev; } ;
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_pci_remap_cfg_resource (struct device*,struct resource*) ; 
 void* devm_reset_control_get_exclusive (struct device*,char*) ; 
 int of_pci_get_max_link_speed (struct device_node*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 void* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int rockchip_pcie_get_phys (struct rockchip_pcie*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

int rockchip_pcie_parse_dt(struct rockchip_pcie *rockchip)
{
	struct device *dev = rockchip->dev;
	struct platform_device *pdev = to_platform_device(dev);
	struct device_node *node = dev->of_node;
	struct resource *regs;
	int err;

	if (rockchip->is_rc) {
		regs = platform_get_resource_byname(pdev,
						    IORESOURCE_MEM,
						    "axi-base");
		rockchip->reg_base = devm_pci_remap_cfg_resource(dev, regs);
		if (IS_ERR(rockchip->reg_base))
			return PTR_ERR(rockchip->reg_base);
	} else {
		rockchip->mem_res =
			platform_get_resource_byname(pdev, IORESOURCE_MEM,
						     "mem-base");
		if (!rockchip->mem_res)
			return -EINVAL;
	}

	regs = platform_get_resource_byname(pdev, IORESOURCE_MEM,
					    "apb-base");
	rockchip->apb_base = devm_ioremap_resource(dev, regs);
	if (IS_ERR(rockchip->apb_base))
		return PTR_ERR(rockchip->apb_base);

	err = rockchip_pcie_get_phys(rockchip);
	if (err)
		return err;

	rockchip->lanes = 1;
	err = of_property_read_u32(node, "num-lanes", &rockchip->lanes);
	if (!err && (rockchip->lanes == 0 ||
		     rockchip->lanes == 3 ||
		     rockchip->lanes > 4)) {
		dev_warn(dev, "invalid num-lanes, default to use one lane\n");
		rockchip->lanes = 1;
	}

	rockchip->link_gen = of_pci_get_max_link_speed(node);
	if (rockchip->link_gen < 0 || rockchip->link_gen > 2)
		rockchip->link_gen = 2;

	rockchip->core_rst = devm_reset_control_get_exclusive(dev, "core");
	if (IS_ERR(rockchip->core_rst)) {
		if (PTR_ERR(rockchip->core_rst) != -EPROBE_DEFER)
			dev_err(dev, "missing core reset property in node\n");
		return PTR_ERR(rockchip->core_rst);
	}

	rockchip->mgmt_rst = devm_reset_control_get_exclusive(dev, "mgmt");
	if (IS_ERR(rockchip->mgmt_rst)) {
		if (PTR_ERR(rockchip->mgmt_rst) != -EPROBE_DEFER)
			dev_err(dev, "missing mgmt reset property in node\n");
		return PTR_ERR(rockchip->mgmt_rst);
	}

	rockchip->mgmt_sticky_rst = devm_reset_control_get_exclusive(dev,
								     "mgmt-sticky");
	if (IS_ERR(rockchip->mgmt_sticky_rst)) {
		if (PTR_ERR(rockchip->mgmt_sticky_rst) != -EPROBE_DEFER)
			dev_err(dev, "missing mgmt-sticky reset property in node\n");
		return PTR_ERR(rockchip->mgmt_sticky_rst);
	}

	rockchip->pipe_rst = devm_reset_control_get_exclusive(dev, "pipe");
	if (IS_ERR(rockchip->pipe_rst)) {
		if (PTR_ERR(rockchip->pipe_rst) != -EPROBE_DEFER)
			dev_err(dev, "missing pipe reset property in node\n");
		return PTR_ERR(rockchip->pipe_rst);
	}

	rockchip->pm_rst = devm_reset_control_get_exclusive(dev, "pm");
	if (IS_ERR(rockchip->pm_rst)) {
		if (PTR_ERR(rockchip->pm_rst) != -EPROBE_DEFER)
			dev_err(dev, "missing pm reset property in node\n");
		return PTR_ERR(rockchip->pm_rst);
	}

	rockchip->pclk_rst = devm_reset_control_get_exclusive(dev, "pclk");
	if (IS_ERR(rockchip->pclk_rst)) {
		if (PTR_ERR(rockchip->pclk_rst) != -EPROBE_DEFER)
			dev_err(dev, "missing pclk reset property in node\n");
		return PTR_ERR(rockchip->pclk_rst);
	}

	rockchip->aclk_rst = devm_reset_control_get_exclusive(dev, "aclk");
	if (IS_ERR(rockchip->aclk_rst)) {
		if (PTR_ERR(rockchip->aclk_rst) != -EPROBE_DEFER)
			dev_err(dev, "missing aclk reset property in node\n");
		return PTR_ERR(rockchip->aclk_rst);
	}

	if (rockchip->is_rc) {
		rockchip->ep_gpio = devm_gpiod_get(dev, "ep", GPIOD_OUT_HIGH);
		if (IS_ERR(rockchip->ep_gpio)) {
			dev_err(dev, "missing ep-gpios property in node\n");
			return PTR_ERR(rockchip->ep_gpio);
		}
	}

	rockchip->aclk_pcie = devm_clk_get(dev, "aclk");
	if (IS_ERR(rockchip->aclk_pcie)) {
		dev_err(dev, "aclk clock not found\n");
		return PTR_ERR(rockchip->aclk_pcie);
	}

	rockchip->aclk_perf_pcie = devm_clk_get(dev, "aclk-perf");
	if (IS_ERR(rockchip->aclk_perf_pcie)) {
		dev_err(dev, "aclk_perf clock not found\n");
		return PTR_ERR(rockchip->aclk_perf_pcie);
	}

	rockchip->hclk_pcie = devm_clk_get(dev, "hclk");
	if (IS_ERR(rockchip->hclk_pcie)) {
		dev_err(dev, "hclk clock not found\n");
		return PTR_ERR(rockchip->hclk_pcie);
	}

	rockchip->clk_pcie_pm = devm_clk_get(dev, "pm");
	if (IS_ERR(rockchip->clk_pcie_pm)) {
		dev_err(dev, "pm clock not found\n");
		return PTR_ERR(rockchip->clk_pcie_pm);
	}

	return 0;
}