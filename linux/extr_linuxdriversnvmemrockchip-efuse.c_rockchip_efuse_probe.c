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
struct rockchip_efuse_chip {struct device* dev; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; } ;
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct nvmem_device {int dummy; } ;
struct TYPE_3__ {struct device* dev; struct rockchip_efuse_chip* priv; void const* reg_read; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (struct nvmem_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct rockchip_efuse_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct nvmem_device* devm_nvmem_register (struct device*,TYPE_1__*) ; 
 TYPE_1__ econfig ; 
 void* of_device_get_match_data (struct device*) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int rockchip_efuse_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct nvmem_device *nvmem;
	struct rockchip_efuse_chip *efuse;
	const void *data;
	struct device *dev = &pdev->dev;

	data = of_device_get_match_data(dev);
	if (!data) {
		dev_err(dev, "failed to get match data\n");
		return -EINVAL;
	}

	efuse = devm_kzalloc(dev, sizeof(struct rockchip_efuse_chip),
			     GFP_KERNEL);
	if (!efuse)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	efuse->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(efuse->base))
		return PTR_ERR(efuse->base);

	efuse->clk = devm_clk_get(dev, "pclk_efuse");
	if (IS_ERR(efuse->clk))
		return PTR_ERR(efuse->clk);

	efuse->dev = dev;
	if (of_property_read_u32(dev->of_node, "rockchip,efuse-size",
				 &econfig.size))
		econfig.size = resource_size(res);
	econfig.reg_read = data;
	econfig.priv = efuse;
	econfig.dev = efuse->dev;
	nvmem = devm_nvmem_register(dev, &econfig);

	return PTR_ERR_OR_ZERO(nvmem);
}