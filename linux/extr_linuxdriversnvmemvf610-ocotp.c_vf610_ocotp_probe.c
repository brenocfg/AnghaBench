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
struct vf610_ocotp {int /*<<< orphan*/  nvmem; int /*<<< orphan*/  timing; struct device* dev; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_3__ {struct device* dev; struct vf610_ocotp* priv; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct vf610_ocotp* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_nvmem_register (struct device*,TYPE_1__*) ; 
 TYPE_1__ ocotp_config ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  vf610_ocotp_calculate_timing (struct vf610_ocotp*) ; 

__attribute__((used)) static int vf610_ocotp_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct vf610_ocotp *ocotp_dev;

	ocotp_dev = devm_kzalloc(dev, sizeof(struct vf610_ocotp), GFP_KERNEL);
	if (!ocotp_dev)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ocotp_dev->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(ocotp_dev->base))
		return PTR_ERR(ocotp_dev->base);

	ocotp_dev->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(ocotp_dev->clk)) {
		dev_err(dev, "failed getting clock, err = %ld\n",
			PTR_ERR(ocotp_dev->clk));
		return PTR_ERR(ocotp_dev->clk);
	}
	ocotp_dev->dev = dev;
	ocotp_dev->timing = vf610_ocotp_calculate_timing(ocotp_dev);

	ocotp_config.size = resource_size(res);
	ocotp_config.priv = ocotp_dev;
	ocotp_config.dev = dev;

	ocotp_dev->nvmem = devm_nvmem_register(dev, &ocotp_config);

	return PTR_ERR_OR_ZERO(ocotp_dev->nvmem);
}