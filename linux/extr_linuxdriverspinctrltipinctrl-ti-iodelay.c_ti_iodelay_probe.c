#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  name; int /*<<< orphan*/ * confops; int /*<<< orphan*/ * pctlops; } ;
struct ti_iodelay_device {int /*<<< orphan*/  pctl; TYPE_2__ desc; int /*<<< orphan*/  regmap; TYPE_1__* reg_data; int /*<<< orphan*/  reg_base; int /*<<< orphan*/  phys_base; struct device* dev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {TYPE_1__* data; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  regmap_config; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct ti_iodelay_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_mmio (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 struct device_node* of_node_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int pinctrl_enable (int /*<<< orphan*/ ) ; 
 int pinctrl_register_and_init (TYPE_2__*,struct device*,struct ti_iodelay_device*,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ti_iodelay_device*) ; 
 int ti_iodelay_alloc_pins (struct device*,struct ti_iodelay_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_iodelay_of_match ; 
 scalar_t__ ti_iodelay_pinconf_init_dev (struct ti_iodelay_device*) ; 
 int /*<<< orphan*/  ti_iodelay_pinctrl_ops ; 
 int /*<<< orphan*/  ti_iodelay_pinctrl_pinconf_ops ; 

__attribute__((used)) static int ti_iodelay_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = of_node_get(dev->of_node);
	const struct of_device_id *match;
	struct resource *res;
	struct ti_iodelay_device *iod;
	int ret = 0;

	if (!np) {
		ret = -EINVAL;
		dev_err(dev, "No OF node\n");
		goto exit_out;
	}

	match = of_match_device(ti_iodelay_of_match, dev);
	if (!match) {
		ret = -EINVAL;
		dev_err(dev, "No DATA match\n");
		goto exit_out;
	}

	iod = devm_kzalloc(dev, sizeof(*iod), GFP_KERNEL);
	if (!iod) {
		ret = -ENOMEM;
		goto exit_out;
	}
	iod->dev = dev;
	iod->reg_data = match->data;

	/* So far We can assume there is only 1 bank of registers */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(dev, "Missing MEM resource\n");
		ret = -ENODEV;
		goto exit_out;
	}

	iod->phys_base = res->start;
	iod->reg_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(iod->reg_base)) {
		ret = PTR_ERR(iod->reg_base);
		goto exit_out;
	}

	iod->regmap = devm_regmap_init_mmio(dev, iod->reg_base,
					    iod->reg_data->regmap_config);
	if (IS_ERR(iod->regmap)) {
		dev_err(dev, "Regmap MMIO init failed.\n");
		ret = PTR_ERR(iod->regmap);
		goto exit_out;
	}

	if (ti_iodelay_pinconf_init_dev(iod))
		goto exit_out;

	ret = ti_iodelay_alloc_pins(dev, iod, res->start);
	if (ret)
		goto exit_out;

	iod->desc.pctlops = &ti_iodelay_pinctrl_ops;
	/* no pinmux ops - we are pinconf */
	iod->desc.confops = &ti_iodelay_pinctrl_pinconf_ops;
	iod->desc.name = dev_name(dev);
	iod->desc.owner = THIS_MODULE;

	ret = pinctrl_register_and_init(&iod->desc, dev, iod, &iod->pctl);
	if (ret) {
		dev_err(dev, "Failed to register pinctrl\n");
		goto exit_out;
	}

	platform_set_drvdata(pdev, iod);

	return pinctrl_enable(iod->pctl);

exit_out:
	of_node_put(np);
	return ret;
}