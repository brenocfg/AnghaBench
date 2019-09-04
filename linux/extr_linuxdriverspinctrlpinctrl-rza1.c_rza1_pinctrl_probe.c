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
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/ * pmxops; int /*<<< orphan*/ * pctlops; int /*<<< orphan*/  name; } ;
struct rza1_pinctrl {int /*<<< orphan*/  data; TYPE_1__ desc; int /*<<< orphan*/  mutex; int /*<<< orphan*/  base; int /*<<< orphan*/ * dev; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct rza1_pinctrl* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_device_get_match_data (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rza1_pinctrl*) ; 
 int /*<<< orphan*/  rza1_pinctrl_ops ; 
 int rza1_pinctrl_register (struct rza1_pinctrl*) ; 
 int /*<<< orphan*/  rza1_pinmux_ops ; 

__attribute__((used)) static int rza1_pinctrl_probe(struct platform_device *pdev)
{
	struct rza1_pinctrl *rza1_pctl;
	struct resource *res;
	int ret;

	rza1_pctl = devm_kzalloc(&pdev->dev, sizeof(*rza1_pctl), GFP_KERNEL);
	if (!rza1_pctl)
		return -ENOMEM;

	rza1_pctl->dev = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rza1_pctl->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(rza1_pctl->base))
		return PTR_ERR(rza1_pctl->base);

	mutex_init(&rza1_pctl->mutex);

	platform_set_drvdata(pdev, rza1_pctl);

	rza1_pctl->desc.name	= DRIVER_NAME;
	rza1_pctl->desc.pctlops	= &rza1_pinctrl_ops;
	rza1_pctl->desc.pmxops	= &rza1_pinmux_ops;
	rza1_pctl->desc.owner	= THIS_MODULE;
	rza1_pctl->data		= of_device_get_match_data(&pdev->dev);

	ret = rza1_pinctrl_register(rza1_pctl);
	if (ret)
		return ret;

	dev_info(&pdev->dev,
		 "RZ/A1 pin controller and gpio successfully registered\n");

	return 0;
}